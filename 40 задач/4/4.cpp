#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

const int N = 10;
const float A = 0.5f, B = 1, C = 0, D = 1, I = (float)7 / 32;

float f(float x, float y) {
	return x * x + y * y;
}

float g(float x) {
	return 2 * x - 1;
}

float randFloat(float a, float b) {
	return a + (float)rand() / RAND_MAX * (b - a);
}

float doubleIntegral() {
	
	float sum = 0;
	int in = 0;
	for (int i = 0; i < N; i++) {
		float x = randFloat(A, B), y = randFloat(C, D);
		in += y <= g(x);
		sum += f(x, y);
	}
			
	return (sum / N) * ((float)in / N) * (D - C) * (B - A);
}

int main() {
	srand(time(NULL));
	float integral = doubleIntegral();
	cout << "Double integral of function: f(x, y) = x^2 + y^2 with " <<
		N << " random sampling equals " << integral << endl;
	cout << "Relative deviation = " << fabs(I - integral) / fabs(I) << endl;
}
