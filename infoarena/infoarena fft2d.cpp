#include <bits/stdc++.h>
//d[i][j] - the number of ways from the top to the bottom, where the last black point you go trough is v[i][j]. Observe that
//there is at most one way between any pair of points and each edge on the i-th level "corrects" the i-th bit of the number
//to be closed to the destination number. That means, there is a path between a pair of nodes on layers a and be only if
//differences in "column" numbers are only in bits a to b-1. All such paths can be found via bitmask map.
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, m;
vector <int> h[N];
vector <ll> d[N];
map <int, ll> s[31][31];
 
int calc (int x, int l, int r) {
	x |= ((1 << (r - l)) - 1) << l;
	return x;
}
 
int main () {
	freopen ("fft2d.in", "r", stdin);
	freopen ("fft2d.out", "w", stdout);
 
	cin >> n >> m;
 
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		h[a].push_back (b);
		d[a].push_back (0);
	}
 
	ll ans = (1LL << (2 * n - 2));
 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < h[i].size (); j++) {
			d[i][j] = (1 << i);
			for (int k = 0; k < i; k++) {
				int x = calc (h[i][j], n - i - 1, n - k - 1);
				d[i][j] -= s[k][i][x];
			}
 
			ans -= d[i][j] * (1LL << (n - i - 1));
 
			for (int k = i + 1; k < n; k++) {
				int x = calc (h[i][j], n - k - 1, n - i - 1);
				s[i][k][x] += d[i][j];
			}
		}
	}
 
	cout << ans;
}
