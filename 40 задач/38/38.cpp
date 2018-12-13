#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1000;

int n, m, s, f, p[MAXN];
vector <int> g[MAXN];
vector <bool> used(MAXN, false);
vector < vector <int> > we, wv;
bool found, usedE[MAXN][MAXN], usedV[MAXN];

int bfs() {
	vector <int> v[2];
	v[0].push_back(s);
	used[s] = true;
	for (int d = 0; d < n; d++) {
		int vi = d % 2;
		for (int i = 0; i < v[vi].size(); i++) {
			int cur = v[vi][i];
			if (cur == f) {
				return d;
			}
			for (int j = 0; j < g[cur].size(); j++) {
				int next = g[cur][j];
				if (!used[next]) {
					used[next] = true;
					v[!vi].push_back(next);
				}
			}
		}
		v[vi].clear();
	}
	return -1;
}

void dfsE(int cur, int prev) {
	if (cur == f) {
		vector <int> w;
		w.push_back(f);
		int v = p[cur];
		while (v != s) {
			w.push_back(v);
			v = p[v];
		}
		w.push_back(s);
		reverse(w.begin(), w.end());
		we.push_back(w);
		for (int i = 0; i < w.size() - 1; i++) {
			usedE[w[i]][w[i + 1]] = usedE[w[i + 1]][w[i]] = true;
		}
		found = true;
		return;
	}
	used[cur] = true;
	for (int i = 0; i < g[cur].size() && !found; i++) {
		int next = g[cur][i];
		if (!used[next] && !usedE[cur][next]) {
			p[next] = cur;
			dfsE(next, cur);
		}
	}
	used[cur] = false;
}

void dfsV(int cur, int prev) {
	if (cur == f) {
		vector <int> w;
		w.push_back(f);
		int v = p[cur];
		while (v != s) {
			w.push_back(v);
			v = p[v];
		}
		w.push_back(s);
		reverse(w.begin(), w.end());
		wv.push_back(w);
		for (int i = 1; i < w.size() - 1; i++) {
			usedV[w[i]] = true;
		}
		found = true;
		return;
	}
	used[cur] = true;
	for (int i = 0; i < g[cur].size() && !found; i++) {
		int next = g[cur][i];
		if (!used[next] && !usedV[next]) {
			p[next] = cur;
			dfsV(next, cur);
		}
	}
	used[cur] = false;
}

int main() {
	cin >> n >> m >> s >> f;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int d = bfs();
	cout << "Distance beetween " << s << " and " << f << " = " << d << endl;
	found = true;
	for (int i = 0 ; i < n; i++) {
		for (int j = 0; j < n; j++) {
			usedE[i][j] = false;
		}
	}
	while (found) {
		found = false;
		for (int i = 0; i < n; i++) {
			used[i] = false;
		}
		dfsE(s, -1);
	}
	cout << "Different edges ways:" << endl;
	for (int i = 0; i < we.size(); i++) {
		for (int j = 0; j < we[i].size(); j++) {
			cout << we[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < n; i++) {
		usedV[i] = used[i] = false;
	}
	found = true;
	while (found) {
		found = false;
		for (int i = 0; i < n; i++) {
			used[i] = false;
		}
		dfsV(s, -1);
	}
	cout << "Different vertices ways:" << endl;
	for (int i = 0; i < wv.size(); i++) {
		for (int j = 0; j < wv[i].size(); j++) {
			cout << wv[i][j] << " ";
		}
		cout << endl;
	}
}
