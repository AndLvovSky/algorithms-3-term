#include <iostream>
#include <utility>
#include <vector>

using namespace std;

const int MAXN = 1000, MAXM = 100000;

pair <int, int> e[MAXM];
vector <int> g[MAXN];
int n, m;
bool used[MAXN][MAXN];
vector <int> elrPath;

void readGraph() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		e[i].first = -1;
		e[i].second = -1;
	}
	for (int i = 0; i < m; i++) {
		int curE, curV;
		cin >> curE >> curV;
		if (e[curE].first == -1) {
			e[curE].first = curV;
		} else {
			e[curE].second = curV;
		}
	}
	for (int i = 0; i < m / 2; i++) {
		int a = e[i].first, b = e[i].second;
		g[a].push_back(b);
		g[b].push_back(a);
	}
}

void printGraph() {
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		for (auto v : g[i]) {
			cout << v << " ";
		}
		cout << endl;
	}
}

void dfs(int cur) {
	elrPath.push_back(cur);
	for (int i = 0; i < g[cur].size(); i++) {
		int next = g[cur][i];
		if (!used[cur][next]) {
			used[cur][next] = used[next][cur] = true;
			dfs(next);
			break;
		}
	}
}

int main() {
	readGraph();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			used[i][j] = false;
		}
	}
	dfs(0);
	if (elrPath.size() != m / 2 + 1) {
		cout << "Eulerian path doesn't exist" << endl;
	} else {
		cout << "Eulerian path: ";
		for (int i = 0; i < elrPath.size() - 1; i++) {
			cout << elrPath[i] << " -> ";
		}
		cout << elrPath[elrPath.size() - 1] << endl;
	}
}
