#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 501;

int n, a[MAXN][MAXN], prefS[MAXN][MAXN], s[MAXN], minRect[MAXN];

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		prefS[i][0] = a[i][0];
		for (int j = 1; j < n; j++) {
			prefS[i][j] = prefS[i][j - 1] + a[i][j];
		}
	}
	int maxSum = -1;
	for (int lx = 0; lx < n; lx++) {
		for (int rx = lx; rx < n; rx++) {
			s[0] = lx == 0 ? prefS[0][rx] : prefS[0][rx] - prefS[0][lx - 1];
			for (int i = 1; i < n; i++) {
				s[i] = s[i - 1] + (lx == 0 ? prefS[i][rx] : prefS[i][rx] - prefS[i][lx - 1]);
			}
			minRect[0] = s[0];
			for (int i = 1; i < n; i++) {
				if (s[i] < minRect[i - 1]) {
					minRect[i] = s[i];
				} else {
					minRect[i] = minRect[i - 1];
				}
			}
			maxSum = max(maxSum, s[0]);
			for (int i = 1; i < n; i++) {
				maxSum = max(maxSum, s[i] - min(minRect[i - 1], 0));
			}
		}
	}
	cout << maxSum << endl;
}
