#include <iostream>
#include <cmath>
#include <windows.h>

using namespace std;

int gcdExt(int a, int b, int& x, int& y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}
	int xNext, yNext, gcdNext = gcdExt(b % a, a, xNext, yNext);
	x = yNext - b / a * xNext;
	y = xNext;
	return gcdNext;
}

int main() {
	SetConsoleOutputCP(1251);
	int a, b, c;
	cin >> a >> b >> c;
	if (!a && !b) {
		if (c) {
			cout << "No answers" << endl;
		} else {
			cout << "(x, y) º Z^2" << endl;
		}
		return 0;
	}
	int x, y, g = gcdExt(abs(a), abs(b), x, y);
	if (c % g) {
		cout << "No answers" << endl;
		return 0;
	}
	int x0 = x * c / g * (a < 0 ? -1 : 1), y0 = y * c / g * (b < 0 ? -1 : 1);
	cout << "Answers:" << endl;
	cout << "(" << x0 << " + " << b / g << " * k, " <<
		y0 << " - " << a / g << " * k), k º Z";
}
