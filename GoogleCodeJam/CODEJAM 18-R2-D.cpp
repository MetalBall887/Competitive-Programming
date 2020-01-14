#include <bits/stdc++.h>
//Note, that after increasing enough times, on block of cells (that originated from one cell) are bigger than our pattern. That means,
//the pattern can be inside of the block, on the side of it or in the corner, so it will touch one, two or four blocks. For each situation
//we can iterate through the possible sides/corners and colors of the blocks engaged and for every such variant find the biggest connected
//pattern that will have have colors, corresponding to the position relatively corner/side.

using namespace std;

typedef long long ll;
 
const ll N = 1e6, MOD = 998244353;

string s[20];
int d[20], c[20][20], n, m, u[20][20];
int cx, cy, mask, t;

int col (int x, int y) {
	int t = mask;
	if (y <= cy) t >>= 1;
	if (x <= cx) t >>= 2;
	return (t & 1);
}

bool ok (int x, int y) {
	if (x < 0 || x == n) return false;
	if (y < 0 || y == m) return false;
	if (u[x][y]) return false;
	if (col (x, y) != c[x][y]) return false;
	return true;
}

int dfs (int x, int y) {
	u[x][y] = 1;
	int s = 1;
	if (ok (x - 1, y)) s += dfs (x - 1, y);
	if (ok (x + 1, y)) s += dfs (x + 1, y);
	if (ok (x, y - 1)) s += dfs (x, y - 1);
	if (ok (x, y + 1)) s += dfs (x, y + 1);
	return s;
}

int main () {
	cin >> t;
	for (int k = 0; k < t; k++) {
		cin >> n >> m;

		for (int i = 0; i < n; i++) {
			cin >> s[i];

			for (int j = 0; j < m; j++)
				c[i][j] = (s[i][j] == 'B');
		}

		memset (d, 0, sizeof (d));

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				d[15 * c[i][j]] = 1;
				if (j != m - 1) d[10 * c[i][j] + 5 * c[i][j+1]] = 1;
				if (i != n - 1) d[12 * c[i][j] + 3 * c[i+1][j]] = 1;
				if (i != n - 1 && j != m - 1) {
					d[8 * c[i][j] + 4 * c[i][j+1] + 2 * c[i+1][j] + c[i+1][j+1]] = 1;
				}
			}

		int ans = 0;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				for (int x = 0; x < 16; x++) {
					if (!d[x]) continue;
					memset (u, 0, sizeof (u));
					cx = i, cy = j, mask = x;
					for (int i = 0; i < n; i++)
						for (int j = 0; j < m; j++) {
							if (ok (i, j)) ans = max (ans, dfs (i, j));
						}
				}
			}

		cout << "Case #" << k + 1 << ": " << ans << '\n';
	}
	return 0;
}
