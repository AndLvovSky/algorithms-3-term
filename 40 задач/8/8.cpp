//Cubic spline interpolation program
//when we have two columns of data x and y in input file:
//
//x0 y0
//x1 y1
//...
//xn yn
//
//and we want to find such function f(x)  
//where f(xi) = yi
//and f(x) is cubic function on every [x_k-1, x_k] segment
//and f(x), f'(x), f''(x) are continual
//the result is four columns of cubic polinom coefficients

#include <math.h>
#include <stdio.h>
#include <process.h>
float *x, *y, *h, *l, *delta, *lambda, *c, *d, *b;
int N;
char filename[256];
FILE* InFile=NULL;
void count_num_lines(){
   //count number of lines in input file - number of equations
   int nelf=0;       //non empty line flag
   do{
       nelf = 0;
       while(fgetc(InFile)!='\n' && !feof(InFile)) nelf=1;
       if(nelf) N++;
   }while(!feof(InFile));
   N--;
}
void readmatrix(){
   int i=0;
   //read matrixes a and b from input file
   for(i=0; i<N+1; i++){
       fscanf(InFile, "%f", &x[i]);
       fscanf(InFile, "%f", &y[i]);
   }
}

void allocmatrix(){
   //allocate memory for matrixes
   x = new float[N+1];
   y = new float[N+1];
   h = new float[N+1];
   l = new float[N+1];
   delta = new float[N+1];
   lambda = new float[N+1];
   c = new float[N+1];
   d = new float[N+1];
   b = new float[N+1];
}
void freematrix(){
   delete [] x;
   delete [] y;
   delete [] h;
   delete [] l;
   delete [] delta;
   delete [] lambda;
   delete [] c;
   delete [] d;
   delete [] b;
}

void printresult(){
   int k=0;
   printf("\nA[k]\tB[k]\tC[k]\tD[k]\n");
   for(k=1; k<=N; k++){
       printf("%f\t%f\t%f\t%f\n", y[k], b[k], c[k], d[k]);
   }
   float x0 = 2.5;
   float f = y[3] + b[3] * (x0 - x[2]) + c[3] * pow(x0 - x[2], 2) 
		+ d[3] * pow(x0 - x[2], 3);
   printf("\nf(2.5) = %f\n", f);
}

int main(){
   int k=0;
   do{
       printf("Input filename: ");
       scanf("%s", filename);
       InFile = fopen(filename, "rt");
   }while(InFile==NULL);
   count_num_lines();
   rewind(InFile);
   allocmatrix();
   readmatrix();
   for(k=1; k<=N; k++){
       h[k] = x[k] - x[k-1];
       if(h[k]==0){
	   printf("\nError, x[%d]=x[%d]\n", k, k-1);
	   return 0;
       }
       l[k] = (y[k] - y[k-1])/h[k];
   }
   delta[1] = - h[2]/(2*(h[1]+h[2]));
   lambda[1] = 1.5*(l[2] - l[1])/(h[1]+h[2]);
   for(k=3; k<=N; k++){
      delta[k-1] = - h[k]/(2*h[k-1] + 2*h[k] + h[k-1]*delta[k-2]);
      lambda[k-1] = (3*l[k] - 3*l[k-1] - h[k-1]*lambda[k-2]) /
		    (2*h[k-1] + 2*h[k] + h[k-1]*delta[k-2]);
   }
   c[0] = 0;
   c[N] = 0;
   for(k=N; k>=2; k--){
      c[k-1] = delta[k-1]*c[k] + lambda[k-1];
   }
   for(k=1; k<=N; k++){
      d[k] = (c[k] - c[k-1])/(3*h[k]);
      b[k] = l[k] + (2*c[k]*h[k] + h[k]*c[k-1])/3;
   }
   printresult();
   freematrix();
}
