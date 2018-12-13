#include <iostream>

using namespace std;

const int MAXN = 30;

int n;
bool a[MAXN][MAXN], set[MAXN];

bool check() {
	bool is1 = false, is2 = false;
	for (int i = 0; i < n; i++) {
		if (set[i]) {
			is1 = true;
		} else {
			is2 = true;
		}
	}
	if (!is1 || !is2) {
		return false;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j && set[i] == set[j] && a[i][j] == 1) {
				return false;
			}
		}
	}
	return true;
}

void generateSet(int pos) {
	if (pos == n) {
		if (check()) {
			cout << "YES" << endl;
			cout << "First group: ";
			for (int i = 0; i < n; i++) {
				if (set[i]) {
					cout << i << " ";
				}
			}
			cout << endl;
			cout << "Second group: ";
			for (int i = 0; i < n; i++) {
				if (!set[i]) {
					cout << i << " ";
				}
			}
			cout << endl;
			exit(0);
		}
		return;
	} 
	set[pos] = false;
	generateSet(pos + 1);
	set[pos] = true;
	generateSet(pos + 1);
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}
	generateSet(0);
	cout << "NO" << endl;
}
