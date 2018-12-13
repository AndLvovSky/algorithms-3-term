#include <iostream>
#include <vector>

using namespace std;

struct Rect {
	int xl, yl, xr, yr;
};

const int MAXN = 100, MAXA = 1000;

Rect rects[MAXN];
vector <int> colors[2 * MAXA + 1][2 * MAXA + 1];
vector < vector <int> > diffSets;

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		cin >> rects[i].xl >> rects[i].yl >>
			   rects[i].xr >> rects[i].yr;
		rects[i].xl += MAXA;
		rects[i].xr += MAXA - 1;
		rects[i].yl += MAXA;
		rects[i].yr += MAXA - 1;
	}
	for (int i = 0; i < n; i++) {
		for (int x = rects[i].xl; x <= rects[i].xr; x++) {
			for (int y = rects[i].yl; y <= rects[i].yr; y++) {
				colors[x][y].push_back(i);
			}
		}
	}
	vector <int> emptySet;
	diffSets.push_back(emptySet);
	for (int x = 0; x <= 2 * MAXA; x++) {
		for (int y = 0; y <= 2 * MAXA; y++) {
			vector <int> colSet = colors[x][y];
			bool find = false;
			for (int i = 0; i < diffSets.size(); i++) {
				if (diffSets[i] == colSet) {
					find = true;
					break;
				}
			}
			if (!find) {
				diffSets.push_back(colSet);
			}
		}
	}
	cout << diffSets.size() << endl;
}
