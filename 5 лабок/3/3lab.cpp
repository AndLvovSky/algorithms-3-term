#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <ctime>
#include <ratio>
#include <utility>

using namespace std;
using namespace std::chrono;

typedef long double ld;
typedef vector <ld> vf;
typedef pair <int, int> pii;

const int P = 6, MAXN = 66666, IT = 100;

int n, l1[P], l2[P], r;
vf b, c, d, e,
	bcp, dcp;
ld h[P][MAXN / P], q[P][MAXN / P], w[P][2],
	hcp[P][MAXN / P], qcp[P][MAXN / P]; 
	
bool solvable(vf c, vf d, vf e) {
	int n = d.size();
	c[0] = e[n - 1] = 0;
	bool found = false;
	for (int i = 0; i < n; i++) {
		if (fabs(d[i]) < fabs(c[i]) + fabs(e[i])) {
			return false;
		}
		if (fabs(d[i]) > fabs(c[i]) + fabs(e[i])) {
			found = true;
		}
	}
	return found;
}

vf tridiagonalMatrixAlgorithm(vf& b, vf& c, vf& d, vf& e) {
	int n = d.size();
	vf f(n), g(n);
	f[1] = -e[0] / d[0];
	g[1] = b[0] / d[0];
	for (int i = 1; i < n - 1; i++) {
		f[i + 1] = -e[i] / (d[i] + c[i] * f[i]);
		g[i + 1] = (-c[i] * g[i] + b[i]) / (d[i] + c[i] * f[i]);
	}
	vf x(n);
	x[n - 1] = (-c[n - 1] * g[n - 1] + b[n - 1]) / 
		       (d[n - 1] + c[n - 1] * f[n - 1]);
	for (int i = n - 2; i >= 0; i--) {
		x[i] = f[i + 1] * x[i + 1] + g[i + 1];
	}
	return x;
}

void transformPart(int t) {
	int l1 = ::l1[t], l2 = ::l2[t];
	int rc = l2 - l1 + 1;
	if (t != 0) {
		h[t][0] = c[l1];
		for (int i = l1 + 1; i <= l2; i++) {
			ld cf = -c[i] / d[i - 1];
			h[t][i - l1] =  cf * h[t][i - l1 - 1];
			d[i] += e[i - 1] * cf;
			b[i] += b[i - 1] * cf;
		}	
	} else {
		for (int i = l1 + 1; i <= l2; i++) {
			ld cf = -c[i] / d[i - 1];
			d[i] += e[i - 1] * cf;
			b[i] += b[i - 1] * cf;
		}	
	}
	if (t != P - 1) {
		q[t][rc - 1] = e[l2];
		for (int i = l2 - 1; i >= l1; i--) {
			ld cf = -e[i] / d[i + 1];
			q[t][i - l1] = cf * q[t][i - l1 + 1];
			b[i] += cf * b[i + 1];
		}
	} else {
		for (int i = l2 - 1; i >= l1; i--) {
			ld cf = -e[i] / d[i + 1];
			b[i] += cf * b[i + 1];
		}
	}
	for (int i = l1; i <= l2; i++) {
		bcp[i] = b[i];
		dcp[i] = d[i];
	}
	for (int i = 0; i < rc; i++) {
		hcp[t][i] = h[t][i];
		qcp[t][i] = q[t][i];
	}
	if (t == 0) {
		ld cf = -q[0][0] / q[0][l2];
		w[0][0] = cf * d[l2];
		b[0] += cf * b[l2];
	} else if (t == P - 1) {
		ld cf = -h[P - 1][rc - 1] / h[P - 1][0];
		w[P - 1][1] = cf * d[l1];
	} else {
		ld cf = -q[t][0] / q[t][rc - 1];
		w[t][0] = cf * d[l2];
		h[t][0] += cf * h[t][rc - 1];
		b[l1] += cf * b[l2];
		cf = -h[t][rc - 1] / h[t][0];
		w[t][1] = cf * d[l1];
		d[l2] += cf * w[t][0];
		b[l2] += cf * b[l1]; 
	}
}

vf parallelTridiagonalMatrixAlgorithm() { 
	if (n % P == 0) {
		r = n / P;
	} else {
		r = n / P + 1;
	}
	for (int i = 0; i < P; i++) {
		if (n % P == 0) {
			l1[i] = i * r;
			l2[i] = (i + 1) * r - 1;
		} else {
			l1[i] = i * r;
			l2[i] = min((i + 1) * r - 1, n - 1);
		}
	}
	n = d.size();
	bcp.resize(n);
	dcp.resize(n);
	thread* threads[P];
	for (int i = 0; i < P; i++) {
		threads[i] = new thread(transformPart, i);
	}
	for (int i = 0; i < P; i++) {
		threads[i]->join();
	}
	vf bs(2 * P), cs(2 * P), ds(2 * P), es(2 * P);
	for (int i = 0; i < P; i++) {
		bs[2 * i] = b[l1[i]];
		bs[2 * i + 1] = b[l2[i]]; 
		ds[2 * i] = d[l1[i]];
		ds[2 * i + 1] = d[l2[i]];
	}
	cs[1] = 0;
	for (int i = 1; i < P; i++) {
		cs[2 * i] = h[i][0];
		cs[2 * i + 1] = w[i][1];
	}
	for (int i = 0; i < P - 1; i++) {
		es[2 * i] = w[i][0];
		es[2 * i + 1] = q[i][r - 1];
	}
	es[2 * P - 2] = 0;
	vf vxp = tridiagonalMatrixAlgorithm(bs, cs, ds, es);
	vf vx(n);
	for (int i = 0; i < P; i++) {
		vx[l1[i]] = vxp[2 * i];
		vx[l2[i]] = vxp[2 * i + 1];
	}
	for (int i = 0; i < P; i++) {
		if (i == 0) {
			for (int j = 1; j < l2[0]; j++) {
				vx[j] = (bcp[j] - qcp[0][j] * vx[l1[1]]) / dcp[j];
			}
		} else if (i == P - 1) {
			for (int j = l1[P - 1] + 1; j < l2[P - 1]; j++) {
				vx[j] = (bcp[j] - hcp[P - 1][j - l1[P - 1]] * 
					vx[l2[P - 2]]) / dcp[j];
			}
		} else {
			for (int j = l1[i] + 1; j < l2[i]; j++) {
				vx[j] = (bcp[j] - qcp[i][j - l1[i]] * vx[l1[i + 1]] - 
					hcp[i][j - l1[i]] * vx[l2[i - 1]]) / dcp[j];
			}
		}
	}
	return vx;
}

void simpleSequentTest() {
	int n;
	cin >> n;
	vf b(n), c(n), d(n), e(n);
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
	for (int i = 1; i < n; i++) {
		cin >> c[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> d[i];
	}
	for (int i = 0; i < n - 1; i++) {
		cin >> e[i];
	}
	vf vx = tridiagonalMatrixAlgorithm(b, c, d, e);
	for (auto x : vx) {
		cout << x << " ";
	}
	cout << endl;
}

void simpleParallelTest() {
	cin >> n;
	b.resize(n);
	c.resize(n);
	d.resize(n);
	e.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
	for (int i = 1; i < n; i++) {
		cin >> c[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> d[i];
	}
	for (int i = 0; i < n - 1; i++) {
		cin >> e[i];
	}
	vf vx = parallelTridiagonalMatrixAlgorithm();
	for (auto x : vx) {
		cout << x << " ";
	}
	cout << endl;
}

void generateMatrix() {
	n = MAXN;
	b.resize(n);
	c.resize(n);
	d.resize(n);
	e.resize(n);
	for (int i = 0; i < n; i++) {
		b[i] = rand() - RAND_MAX / 2; 
	}
	for (int i = 0; i < n; i++) {
		c[i] = (rand() % 2 ? 1 : -1) * (rand() + 1); 
		e[i] = (rand() % 2 ? 1 : -1) * (rand() + 1);
		d[i] = (rand() % 2 ? 1 : -1) * 
			(fabs(c[i]) + fabs(e[i]) + rand() + 1);
	}
}

void timeTest() {
	generateMatrix();
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int i = 0; i < IT; i++) {
		tridiagonalMatrixAlgorithm(b, c, d, e);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration <ld> dur1 = duration_cast < duration <ld> >(t2 - t1);
	ld dt1 = dur1.count();
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	for (int i = 0; i < IT; i++) {
		parallelTridiagonalMatrixAlgorithm();
	}
	high_resolution_clock::time_point t4 = high_resolution_clock::now();
	duration <ld> dur2 = duration_cast < duration <ld> >(t4 - t3);
	ld dt2 = dur2.count();
	cout << "N = " << MAXN << endl;
	cout << "P = " << P << endl;
	cout << "Iterations = " << IT << endl;
	cout << "Sequent time = " << dt1 << " s" << endl;
	cout << "Parallel time = " << dt2 << " s" << endl;
}

int main() {
	//simpleSequentTest();
	//simpleParallelTest();
	srand((long long)time(NULL));
	timeTest();
}
