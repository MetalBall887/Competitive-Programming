#include <bits/stdc++.h>
//https://codeforces.com/blog/entry/68534
using namespace std;
 
typedef long long ll;
 
const ll N = 1e6, MOD = 998244353;
 
ll d[1000][1000], n, m;
vector <int> v, e[1000];
 
int main () {
	cin >> n >> m;
	int p = 0, x;
	for (int i = 0; i < m; i++) {
		cin >> x;
		if (x != p) {
			v.push_back (x);
			p = x;
		}
	}
 
	if (v.size () >= 2 * n) {
		cout << 0 << endl;
		return 0;
	}
 
	int m = v.size ();
 
	for (int i = 0; i < m; i++) {
		e[v[i]].push_back (i);
	}
 
	for (int i = 0; i < m; i++)
		if (e[v[i]].size () == 1) d[i][i] = 1;
	
	for (int k = 1; k < m; k++)
		for (int i = 0; i + k < m; i++) {
			int mn = *min_element (v.begin () + i, v.begin () + i + k + 1);
 
			int l = e[mn][0], r = e[mn].back ();
 
			if (l < i || i + k < r) continue;
 
			d[i][i+k] = 1;
			ll sum_l = (i < l ? 2 * d[i][l-1] % MOD : 1);
			ll sum_r = (r < i + k ? 2 * d[r+1][i+k] % MOD : 1);
			
			int p = -1;
			for (int x : e[mn]) {
				if (p != -1 && x - p > 1) d[i][i+k] = d[i][i+k] * d[p+1][x-1] % MOD;
				p = x;
			}
 
			for (int j = i; j < l - 1; j++) {
				sum_l += d[i][j] * d[j+1][l-1] % MOD;
				if (sum_l >= MOD) sum_l -= MOD;
			}
 
			for (int j = r + 1; j < i + k; j++) {
				sum_r += d[r+1][j] * d[j+1][i+k] % MOD;
				if (sum_r >= MOD) sum_r -= MOD;
			}
 
			d[i][i+k] = d[i][i+k] * sum_l % MOD * sum_r % MOD;
		}
 
	cout << d[0][m-1];
	return 0;
}
