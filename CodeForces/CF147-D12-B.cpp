#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let M(x) be the matrix, where M(x)ij is the length of the longest path between i and j consisting of at most x edges or -INF if there is none.
//Knowing M(x) and M(y) let's calculate M(x+y). M(x+y)ij = max(M(x)ik + M(y)kj) over all k. This reminds of matrix multiplication and also is
//associative, so if * is this operation M(x) = M(1)*M(1)*...*M(1). Now we can check if M(x) has Mii > 0 for any i and that would mean positive
//cycles. So if we do a binary search on x and calculate the power always from the scratch, we get a O(n^3log^2n) algorithm which can be optimised
//by precalculating binary powers and parallel binsearch
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n, m;

struct Matrix {
	int a[300][300];

	Matrix () {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				a[i][j] = -1e9;
			a[i][i] = 0;
		}

	}

	int* operator[] (int x) {
		return a[x];
	}

	Matrix operator* (Matrix b) {
		Matrix c;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++)
					c[i][j] = max (c[i][j], a[i][k] + b[k][j]);

		return c;
	}

	void print () {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				cout << a[i][j] << ' ';
			cout << endl;
		}

		cout << endl;
	}
} d[10];

bool has_cycles (Matrix a) {
	for (int i = 0; i < n; i++)
		if (a[i][i] > 0) return true;
	return false;
}

int main () {
	cin >> n >> m;

	d[0] = Matrix ();

	for (int i = 0; i < m; i++) {
		int a, b, c, c2;
		cin >> a >> b >> c >> c2;
		a--, b--;
		d[0][a][b] = c;
		d[0][b][a] = c2;
	}

	int r = 1, l = 1, bin;

	for (bin = 1; r <= n; bin++) {
		d[bin] = d[bin-1] * d[bin-1];
		r <<= 1;
	}

	r <<= 1;

	bin--;

	if (!has_cycles (d[bin])) {
		cout << 0;
		return 0;
	}

	Matrix a;

	while (l < r) {
		int mid = (l + r) / 2;
		if (!has_cycles (a * d[bin])) {
			a = a * d[bin];
			l = mid + 1;
		}
		else r = mid;

		bin--;
	}

	cout << l << endl;
}
