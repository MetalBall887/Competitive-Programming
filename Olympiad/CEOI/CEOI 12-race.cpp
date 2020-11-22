
#include <bits/stdc++.h>
 
//For the case with one self-intersection let's say segments AB and CD intersect. That means, there will be a first segment to be AB, then there will be a path
//from B to C, segment CD intersecting AB and the last path from D inside of either arc AD or DB that can finish in any point of the arc. Now note that A serves
//almost no purpose, other than a limit on an arc AD, which means we can move A as far from D as possible. After choosing such A, we can count answer as
//1 + path[B][C][dir] + 1 + max(dp_max[D][A][!dir], dp_max[D][C][dir]). We can iterate over B, choose D such that there is a
//BD segment and choose C freely. This makes O(N(N+M)) complexity. 
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const int N = 2000000;
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int path[500][500][2], dp[500][500][2], dp_max[500][500][2];
 
int g[500][500], k;
int ans[500], n, m, nx[500][2];
 
 
void f_edge (int l, int r, int dir) {
	path[l][r][dir] = 1;
	dp[l][r][dir] = 1 + dp_max[r][nx[l][dir]][!dir];
}
 
void f (int l, int r, int dir) {
	for (int k = nx[l][dir]; k != r; k = nx[k][dir]) {
		path[l][r][dir] = max (path[l][r][dir], path[l][k][dir] + path[k][r][dir]);
		dp[l][r][dir] = max (dp[l][r][dir], path[l][k][dir] + dp[k][r][dir]);
	}
 
	dp_max[l][r][dir] = max (dp[l][r][dir], dp_max[l][nx[r][!dir]][dir]);
}
 
int main () {
	cin >> n >> k;
 
	for (int i = 0; i < n; i++) {
		int x;
		while (cin >> x && x) {
			g[i][x-1] = 1;
		}
 
		nx[i][0] = (i + 1) % n;
		nx[i][1] = i ? i - 1 : n - 1;
	}
 
	for (int k = 1; k < n; k++)
		for (int i = 0; i < n; i++) {
			int l = i, r = (i + k) % n;
			dp[l][r][0] = path[l][r][0] = -1e9;
			dp[r][l][1] = path[r][l][1] = -1e9;
			if (g[l][r]) f_edge (l, r, 0);
			if (g[r][l]) f_edge (r, l, 1);
			f (l, r, 0);
			f (r, l, 1);
		}
 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int dir = 0; dir < 2; dir++)
				ans[i] = max (ans[i], dp[i][j][dir]);
 
	if (!k) {
		int ind = max_element(ans, ans + n) - ans;
		cout << ans[ind] << '\n' << ind + 1 << endl;
		return 0;
	}
 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int dir = 0; dir < 2; dir++) {
				int k = nx[j][dir];
 
				if (path[i][j][dir] <= 0) continue;
 
				while (k != i && !g[k][i]) k = nx[k][dir];
 
				if (k == i) continue;
 
				for (int l = nx[k][dir]; l != i; l = nx[l][dir]) {
					int ans_l = max(dp_max[l][nx[k][dir]][!dir], dp_max[l][nx[i][!dir]][dir]);
					if (g[j][l]) ans[k] = max (ans[k], 2 + path[i][j][dir] + ans_l);
				}
 
			}
 
	int ind = max_element(ans, ans + n) - ans;
	cout << ans[ind] << '\n' << ind + 1 << endl;
}
