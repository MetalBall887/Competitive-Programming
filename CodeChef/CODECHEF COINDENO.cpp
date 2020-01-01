#include <bits/stdc++.h>
//First subtask can be solved with knapsack dp. To solve all of them, we should add one greedy insight: if we take a coin
//with the best weight/denomination ratio, if it's possible to cover the sum with only this coin, this coverage will be 
//optimal. Proof is easy: since for all coverages the cost is the same, one with the smaller "density" (total weight/cost)
//will be the lightest. Now, we should find such combination of coins, so that it will be optimal, smaller than the query
//value and the difference will be the factor of the "sparse" coin's denomination, so that we will be able to complement it
//with coins of this type. That being said, they should have the same modulo. Now for each coins' combination we can 
//modulate the number of coins of each type, so we would need at most c coins of any type, nc coins overall, so the overall 
//maximum denomination to achieve the needed modulo (if possible) is nc^2. Now calculate a dp table to nc^2 and everytimr the
//query value is big, take any optimal combination so that the remaining cost will be the factor of the efficient coin.
 
typedef long long ll;
 
const ll N = 1e6, MOD = 1e9 + 7, INF = 1e18;
 
using namespace std;
 
ll n, c, m;
ll d[1000001];

struct coin {
	ll a, w;
	bool operator < (const coin& b) {
		return w * b.a < b.w * a;
	}
} a[100];

int main () {
	ios::sync_with_stdio (0);
	cin >> n >> c >> m;
	for (ll i = 0; i < n; i++) {
		cin >> a[i].a >> a[i].w;
	}

	sort (a, a + n);

	ll R = n * c * c;

	fill (d, d + R + 1, INF);

	d[0] = 0;

	for (int i = 0; i <= R; i++) {
		for (int j = 0; j < n; j++) {
			if (i + a[j].a <= R) {
				d[i + a[j].a] = min (d[i + a[j].a], d[i] + a[j].w);
			}
		}
	}

	for (ll i = 0; i < m; i++) {
		ll q;
		cin >> q;

		if (q <= R) cout << (d[q] == INF ? -1 : d[q] % MOD) << '\n';
		else {
			ll last = R - R % a[0].a + q % a[0].a;
			while (last > R) last -= a[0].a;
			ll it = (q - last) / a[0].a % MOD;
			assert (q % a[0].a == last % a[0].a);
			if (d[last] == INF) cout << -1 << '\n';
			else cout << (d[last] + a[0].w * it % MOD) % MOD << '\n';
		}
	}
}
