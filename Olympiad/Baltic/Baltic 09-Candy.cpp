#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//To check if from stand i a wagon can travel to stand j: let ti < tj. Then
//tj - ti > |sj - si|
//tj - ti > sj - si and tj - ti > si - sj
//                  or
//tj - sj > ti - si and tj + sj > ti + si
//means (ti - si, ti + si) < (tj - sj, tj + sj).
//Rotate for each i (ti, si) to (ti - si, ti + si) and apply greedy algorithm.
//Sort by first coordinate and keep track of all wagon trajectories. Greedy part is, when we need to choose the trajectory, we choose 
//the "worst" fitting chain (the one with the highest y axis of the end that is still lower than the current one).
 
using namespace __gnu_pbds;
 
using namespace std;
 
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
 
const ll N = 2000001;
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
struct candy {
	ll x, y, i;
 
	bool operator<(candy a) {
		return tie(x, y) < tie(a.x, a.y);
	}
} d[N];
 
ll n, ans[N], s[N], t[N], ptr;
 
multiset<pair<ll, int>> ds;
 
int main() {
	cin >> n;
 
	for (int i = 0; i < n; i++) {
		cin >> s[i] >> t[i];
		d[i] = {t[i] + s[i], t[i] - s[i], i};
	}
 
	sort(d, d + n);
 
	for (int i = 0; i < n; i++) {
 
		if (ds.upper_bound({d[i].y, n}) == ds.begin()) {
			++ptr;
			ds.insert({d[i].y, ptr});
			ans[d[i].i] = ptr;
		} else {
			auto x = prev(ds.upper_bound({d[i].y, n}));
 
			ans[d[i].i] = x->second;
			ds.insert({d[i].y, x->second});
			ds.erase(x);
		}
	}
 
	cout << ptr << endl;
 
	for (int i = 0; i < n; i++) {
		cout << s[i] << ' ' << t[i] << ' ' << ans[i] << '\n';
	}
}
