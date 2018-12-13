#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

float f1(float y) {
	return y; 
}

float f2(float y) {
	return sqrt(1 - y * y);
}

float f3(float y) {
	return -y;
}

float f4(float y) {
	return -sqrt(1 - y * y);
}

float fact(float n) {
	return n == 1 ? 1 : n * fact(n - 1);
}

float taylorCos(float x, float e) {
	float a = -M_PI / 4, b = 7 * M_PI / 4;
	const float T = 2 * M_PI;
	int cycles = (int)fabs(x / T);
	if (x < 0) {
		x += cycles * T;
		if (x < a) {
			x += T;
		} 
	} else {
		x -= cycles * T;
		if (x > b) {
			x -= T;
		}
	}
	float (*f)(float);
	if (x <= M_PI / 4) {
		f = f1;
	} else if (x <= M_PI / 2) {
		f = f2;
		x -= M_PI / 2;
	} else if (x <= 3 * M_PI / 4) {
		f = f4;
		x -= M_PI / 2;
	} else if (x <= M_PI)  {
		f = f3;
		x -= M_PI;
	} else if (x <= 5 * M_PI / 4) {
		f = f3;
		x -= M_PI;
	} else if (x <= 3 * M_PI / 2){
		f = f4;
		x -= 3 * M_PI / 2;
	} else if (x <= 7 * M_PI / 4) {
		f = f2;
		x -= 3 * M_PI / 2;
	} else {
		f = f4;
		x -= 3 * M_PI / 2;
	}
	float prevSum, sum = 1;
	int n = 1;
	do {
		prevSum = sum;
		sum += (n % 2 ? -1 : 1) * pow(x, (float)(2 * n)) / fact(2 * n);
		n++;
	} while (fabs(f(sum) - f(prevSum)) >= e);
	return f(sum);
}

int main() {
	float x, e;
	cin >> x >> e;
	float pseudoReal = cos(x);
	float seriesSum = taylorCos(x, e);
	cout << "Calculated value = " << seriesSum << endl;
	cout << "Real value = " << pseudoReal << endl;
	cout << "Absolute deviation = " << fabs(seriesSum - pseudoReal) << endl;
}
