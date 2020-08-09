#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//d[i][j][mask] - is it possible to divide a (i,j) bar and share it between a subset of friends that is defined by a mask. It's possible only when sum of
//requirements of the subset equals i*j. That means, for each mask there is O(x) rectangles that can be divided for this mask: for each i <= x it will be
//(i, sum[mask] / j), there are O(n2^n) states that we actually have to visit. For each such state let's try to do the first cut: iterate all submasks of the
//mask and try to cut vertically/horizontally and divide the left/upper part for a subset defined by a submask. For a cut there is one fixed dimension and the
//second one can be determined as sum[submask] / (fixed dimension). This whole leaves us with O(n3^n) complexity.
 
//using namespace __gnu_pbds;
 
#define N 100000
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int M = 1e6;

int n, x, y, a[15], sum[1 << 15], t;

bitset <1 << 15> d[101][101];
vector <int> s[101][101];

int main () {

	while (cin >> n && n) {
		cin >> x >> y;

		for (int i = 1; i <= x; i++)
			for (int j = 1; j <= y; j++) {
				d[i][j].reset();
				s[i][j].clear();
			}

		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}

		for (int i = 1; i < (1 << n); i++) {
			sum[i] = 0;
			for (int j = 0; j < n; j++) {
				if ((i >> j) & 1) sum[i] += a[j];
			}

			for (int j = 1; j <= x; j++) {
				if (sum[i] % j == 0 && sum[i] / j <= y) 
					s[j][sum[i] / j].push_back (i);
			}
		}

		for (int i = 1; i <= x; i++) {
			for (int j = 1; j <= y; j++) {
				for (int mask : s[i][j]) {
					if (__builtin_popcount (mask) == 1) {
						d[i][j][mask] = 1;
						continue;
					}
					for (int k = mask; k > 0; k = (k - 1) & mask) {
						if (sum[k] % i == 0 && d[i][sum[k] / i][k])
							d[i][j][mask] = d[i][j][mask] | d[i][j - sum[k] / i][mask ^ k];

						if (sum[k] % j == 0 && d[sum[k] / j][j][k])
							d[i][j][mask] = d[i][j][mask] | d[i - sum[k] / j][j][mask ^ k];
					}
				}
			}
		}
		cout << "Case " << ++t << ": ";
		if (d[x][y][(1 << n) - 1]) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
}
