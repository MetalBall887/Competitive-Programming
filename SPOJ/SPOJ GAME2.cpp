#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Note that whenever someone moves, the number of heaps with maximal value decreases exactly by 1. That means, if you're a second player and the number of max.
//heaps if even, you'll end up decreasing the last maximal heap. Your task then is to make the number of heaps with second maximal value even as well. It's simply
//achievable by first making it even if it's not, then mirroring every opponent's move to keep it even.
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int MAXN = 1e8;

ll cnt[N], mx, smx, n, t;

int main () {
	cin >> t;

	while (t--) {
		cin >> n;
		memset (cnt, 0, sizeof (cnt));
		smx = mx = 0;

		for (int i = 0; i < n; i++) {
			ll a;
			cin >> a;
			cnt[a]++;

			if (mx < a) {
				smx = mx;
				mx = a;
			} else smx = max (smx, a);
		}

		if (cnt[mx] % 2 == 0 || !mx) { cout << 0 << '\n'; continue; }
		if (!smx && cnt[mx] == 1) { cout << 1 << '\n'; continue; }
		if (cnt[mx] > 1) { cout << cnt[mx] * mx << '\n'; continue; }

		if (cnt[smx] & 1) cout << 1 << '\n';
		else cout << smx << '\n';
	}
}
