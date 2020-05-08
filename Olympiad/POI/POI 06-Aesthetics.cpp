#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//d[i][j] - the minimal difference for a text if the last row is from i-th to j-th word and w[i][j] - the length of the row
//from i-th to j-th word. d[i][j] = min (d[k][i-1] + |w[k][i-1] - w[i][j]|) where w[k][i-1] <= m and w[i][j] <= m. We can
// process two possibilities: w[k][i-1] <= w[i][j] and w[k][i-1] > w[i][j]. For the first one it will be 
//d[i][j] = min(d[k][i-1] - w[k][i-1]) + w[i][j], similarly for the second possibility. So for a fixed i let l be the rightmost
//index such that w[l][i-1] > w[i][r]. While r is moving to the right, l will be moving only to the left. For all k from 0 to l
//we will keep min (d[k][i-1] + w[k][i-1]) in minimal stack or amortized queue and for k from l + 1 to i we will keep 
//min (d[k][i-1] - w[k][i-1]) in a variable. With such two pointer method the overall complexity will be O(n^2).
 
using namespace __gnu_pbds;
 
#define N 1000003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

struct MinQueue {
	deque < pair <int, ll> > d;

	void push (int x, ll v) {
		while (!d.empty () && d.back ().second >= v) {
			d.pop_back ();
		}
		d.push_back ({x, v});
	}

	ll front () {
		if (d.empty ()) return INF;
		return d.front ().second;
	}

	void pop (int x) {
		if (!d.empty () && d.front ().first == x) d.pop_front ();
	}

	void clear () { d.clear (); }
} q;

ll d[2000][2000], w[2000][2000], n, m;

int main () {
	cin >> m >> n;

	for (int i = 0; i < n; i++) {
		cin >> w[i][i];
		w[i][i]++;
	}
	m++;

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++) {
			w[i][j] = w[i][j-1] + w[j][j];
		}

	ll ans = INF;

	for (int i = 1; i < n; i++) {
		int l = i - 1, r = i - 1;
		while (l >= 0 && w[l][r] <= m) l--;
		q.clear ();
		for (int j = r; j > l; j--) {
			q.push (j, d[j][r] + w[j][r]);
		}

		int p = r;
		ll mn = INF;

		for (int j = i; j < n; j++) {
			while (p > l && w[p][r] <= w[i][j]) {
				mn = min (mn, d[p][r] - w[p][r]);
				q.pop (p);
				p--;
			}

			d[i][j] = min (q.front () - w[i][j], mn + w[i][j]);
		}

		if (w[i][n-1] <= m) ans = min (d[i][n-1], ans);
	}

	if (w[0][n-1] <= m) cout << 0;
	else cout << ans << endl;
}
