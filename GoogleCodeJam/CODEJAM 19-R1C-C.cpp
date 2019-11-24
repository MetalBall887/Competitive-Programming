#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
//Every valid move divides a current rectangle to two independent subrectangle. We can use Sprague-Grundy division into
//two independent subgames.
#include <set>
#include <math.h>
#include <cstdio>
#include <cstring>
#include <map>
 
#define N 1000000
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int c[100][100], n, m, u[20][20][20][20];
int g[20][20][20][20], op[20][20];

string s[100];

int calc_mex (vector <int>& v) {
	sort (v.begin(), v.end());
	if (v.empty () || v[0]) return 0;

	for (int i = 1; i < v.size (); i++) {
		if (v[i-1] + 1 < v[i]) return v[i-1] + 1;
	}

	return v.back () + 1;
}

int sum (int r1, int c1, int r2, int c2) {
	int s = c[r2][c2];

	if (r1) s -= c[r1 - 1][c2];
	if (c1) s -= c[r2][c1 - 1];
	if (r1 && c1) s += c[r1 - 1][c1 - 1];

	return s;
}

bool clear_x (int r, int c1, int c2) {
	return (sum (r, c1, r, c2) == 0);
}
bool clear_y (int r1, int r2, int c) {
	return (sum (r1, c, r2, c) == 0);
}

int grundy (int r1, int c1, int r2, int c2) {
	if (r1 > r2 || c1 > c2) return 0;
	if (u[r1][c1][r2][c2]) return g[r1][c1][r2][c2];
	u[r1][c1][r2][c2] = 1;
	vector <int> v;

	for (int r = r1; r <= r2; r++) {
		if (clear_x (r, c1, c2)) {
			v.push_back (grundy (r1, c1, r - 1, c2) ^ grundy (r + 1, c1, r2, c2));
		}
	}

	for (int c = c1; c <= c2; c++) {
		if (clear_y (r1, r2, c)) {
			v.push_back (grundy (r1, c1, r2, c - 1) ^ grundy (r1, c + 1, r2, c2));
		}
	}

	return g[r1][c1][r2][c2] = calc_mex (v);
}

int main () {
	ios::sync_with_stdio (0);
	int t;
	cin >> t;

	for (int k = 1; k <= t; k++) {
		cin >> n >> m;

		memset (u, 0, sizeof (u));

		for (int i = 0; i < n; i++) {
			cin >> s[i];

			for (int j = 0; j < m; j++)
				c[i][j] = (s[i][j] == '#');
		}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				if (i) c[i][j] += c[i-1][j];
				if (j) c[i][j] += c[i][j-1];
				if (i && j) c[i][j] -= c[i-1][j-1];
			}

		int ans = 0;

		for (int i = 0; i < n; i++)
			if (grundy (0, 0, i - 1, m - 1) == grundy (i + 1, 0, n - 1, m - 1) &&
				clear_x (i, 0, m - 1)) {
				ans += m;
			}

		for (int i = 0; i < m; i++)
			if (grundy (0, 0, n - 1, i - 1) == grundy (0, i + 1, n - 1, m - 1) &&
				clear_y (0, n - 1, i)) {
				ans += n;
			}

		cout << "Case #" << k << ": " << ans << '\n';
	}
}
