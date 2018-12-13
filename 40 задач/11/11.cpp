#include <iostream>
#include <cmath>

using namespace std;

struct Coord {
	float x, y;
};

const int MAXN = 100000;
const float INF = 1e18;

int n;
Coord c[MAXN];
float d[MAXN], sp, snp, mp = -INF, mnp = -INF;

float distance(float xa, float ya, float xb, float yb) {
	return sqrt((xb - xa) * (xb - xa) + (yb - ya) * (yb - ya));
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> c[i].x >> c[i].y;
	}
	for (int i = 0; i < n; i++) {
		d[i] = distance(c[i].x, c[i].y, c[(i + 2) % n].x, c[(i + 2) % n].y);
	}
	for (int i = 0; i < n - 1; i += 2) {
		sp += d[i];
		mp = max(mp, d[i]);
	}
	for (int i = 1; i < n; i += 2) {
		snp += d[i];
		mnp = max(mnp, d[i]);
	}
	if (mp <= mnp) {
		cout << "sum = " << sp << " max = " << mp << endl;
		for (int i = 0; i < n - 1; i += 2) {
			cout << i << " " << (i + 2) % n << endl;
		}
	} else {
		cout << "sum = " << snp << " max = " << mnp << endl;
		for (int i = 1; i < n; i += 2) {
			cout << i << " " << (i + 2) % n << endl;
		}
	}
}
