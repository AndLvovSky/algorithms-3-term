#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 10;

int n1, n2, m[MAXN];
bool t2m[MAXN][MAXN], tch1m[MAXN][MAXN], tch2m[MAXN][MAXN], used[MAXN], found;
vector <int> t1[MAXN], t2[MAXN];
vector <int> iso, p;

void transform(vector <int> *g, bool m[MAXN][MAXN], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			m[i][j] = false;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < g[i].size(); j++) {
			int next = g[i][j];
			m[i][next] = m[next][i] = true;
		}
	}
}

void dfs2(int cur) {
	used[cur] = true;
	p.push_back(cur);
	for (int i = 0; i < t1[cur].size(); i++) {
		int next = t1[cur][i];
		if (!used[next]) {
			dfs2(next);
		}
	}
}

bool check2() {
	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < n2; j++) {
			tch2m[i][j] = tch1m[m[i]][m[j]];
		}
	}
	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < n2; j++) {
			if (tch2m[i][j] != t2m[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void generate(int pos) {
	if (pos == n2) {
		if (check2()) {
			found = true;	
		}
		return;
	}
	for (int i = 0; i < n2 && !found; i++) {
		if (!used[i]) {
			used[i] = true;
			m[pos] = i;
			generate(pos + 1);
			used[i] = false;
		}
	}
}

bool check1(int cur, int prev) {
	p.clear();
	p.push_back(cur);
	for (int i = 0; i < n1; i++) {
		used[i] = false;
	}
	used[cur] = true;
	for (int i = 0; i < t1[cur].size(); i++) {
		int next = t1[cur][i];
		if (next != prev) {
			dfs2(next);
		}
	} 
	if (p.size() != n2) {
		return false;
	}
	int id[MAXN];
	for (int i = 0; i < n2; i++) {
		id[p[i]] = i;
	}
	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < n2; j++) {
			tch1m[i][j] = false;
		}
	} 
	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < t1[p[i]].size(); j++) {
			int next = t1[p[i]][j];
			if (next != prev) {
				tch1m[i][id[next]] = tch1m[id[next]][i] = true;
			}
		}
	}
	for (int i = 0; i < n2; i++) {
		used[i] = false;
	}
	found = false;
	generate(0);
	return found;
}

void dfs1(int cur, int prev) {
	if (check1(cur, prev)) {
		iso.push_back(cur);
		return;	
	}
	for (int i = 0; i < t1[cur].size(); i++) {
		if (t1[cur][i] != prev) {
			dfs1(t1[cur][i], cur);
		}
	}
}

int main() {
	cin >> n1;
	int u, v;
	for (int i = 0; i < n1 - 1; i++) {
		cin >> u >> v;
		t1[u].push_back(v);
		t1[v].push_back(u);
	}
	cin >> n2;
	for (int i = 0; i < n2 - 1; i++) {
		cin >> u >> v;
		t2[u].push_back(v);
		t2[v].push_back(u);
	}
	transform(t2, t2m, n2);
	for (int i = 0; i < t1[0].size(); i++) {
		dfs1(t1[0][i], 0);
	}
	for (int i = 0; i < iso.size(); i++) {
		cout << iso[i] << " ";
	}
	cout << endl;
}
