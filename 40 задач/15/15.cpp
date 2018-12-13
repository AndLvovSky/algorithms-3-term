#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100000;

vector <int> g[MAXN], d(MAXN);
vector <bool> used(MAXN, false);
int n, m, st;

void bfs() {
	vector <int> v[2];
	v[0].push_back(st);
	used[st] = true;
	for (int i = 0; i < n; i++) {
		int vi = i % 2;
		for (auto cur : v[vi]) {
			d[cur] = i;
			for (auto next : g[cur]) {
				if (!used[next]) {
					v[!vi].push_back(next);
					used[next] = true;
				}
			}
		}
		v[vi].clear();
	}
}

int main() {
	cin >> n >> m >> st;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	bfs();
	d.resize(n);
	for (auto v : d) {
		cout << v << " "; 
	}
	cout << endl;
}
