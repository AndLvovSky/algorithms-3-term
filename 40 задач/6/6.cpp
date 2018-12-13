#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void term() {
	cout << -1 << endl;
	exit(0);
}

int n, m, s, k, l, c, f, d;
vector <bool> isFlipped, blazon;
vector <int> flipped, notFlipped;

void findFlipped() {
	isFlipped.resize(c);
	for (int i = 0; i < c; i++) {
		isFlipped[i] = false;
	}
	for (int i = 0, p = 0; i < k; i++, p = (p + s) % c) {
		isFlipped[p] = !isFlipped[p];
	}
	for (int i = 0; i < c; i++) {
		if (isFlipped[i]) {
			flipped.push_back(i);
		} else {
			notFlipped.push_back(i);
		}
	}
	f = flipped.size();
}

void generate(bool t) {
	for (int i = f - 1; i >= f - d; i--) {
		blazon[flipped[i]] = !t;
		flipped.pop_back();
	}
	f -= d;
	if (t) {
		m -= d;
	} else {
		n -= d;
	}
 	if (f % 2 == 1 || min(n, m) < f / 2) {
		term();
	}
	for (int i = 0; i < f; i++) {
		blazon[flipped[i]] = i % 2;
	}
	n -= f / 2;
	m -= f / 2;
	for (int i = 0; i < n; i++) {
		blazon[notFlipped[i]] = true;
	}
	for (int i = n; i < n + m; i++) {
		blazon[notFlipped[i]] = false;
	}
}

int main() {
	cin >> n >> m >> s >> k >> l;
	c = n + m;
	if (l > c) {
		term();
	}
	findFlipped();
	d = abs(l - n);
	if (d > f) {
		term();
	}
	blazon.resize(c);
	generate(l > n);
	for (int i = 0; i < c; i++) {
		cout << blazon[i] << " ";
	}
	cout << endl;
}
