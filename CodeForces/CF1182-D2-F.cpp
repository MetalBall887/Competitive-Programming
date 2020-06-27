#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Note that this problem is equivalent to finding such x, that px/q the closest to 1/2 + k for every k or 2px mod 2q is the closest to q.
//Let g(x) = 2px mod 2q. Note that g(x+y) = g(x) + g(y) mod 2q. If the number of possible x wasn't big, we could sort them by g(x) and try to find the closest
//by binary search. No let's take first t elements and find the closest for them. Then for next t elements we don't have to sort elements again as they will have
//the same "offset" g(x+t) = g(x) + g(t), so all keys will be changed by the same value. Now find the closest to q - g(t). If we take efficient t = sqrt(b-a),
//The whole solution works in O(sqrt(b-a)log(b-a))

using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll p, q, a, b;
 
pair <ll, ll> mn;
 
ll g (ll x) {
	return 2 * p * x % (2 * q);
}
 
int main () {
	ll t;
 
	cin >> t;
 
	while (t--) {
		cin >> a >> b >> p >> q;
		mn = make_pair (INF, INF);
		ll len = 1;
		
		while ((len + 1) * (len + 1) < b - a + 1) len++;
 
		vector < pair <ll, ll> > v;
 
		for (ll i = a; i < a + len; i++) {
			v.push_back ({g(i), i});
		}
 
		sort (v.begin(), v.end());
 
		vector < pair <ll, ll> > w;
 
		w.push_back (v[0]);
		for (ll i = 1; i < v.size (); i++) {
			if (v[i-1].first != v[i].first) w.push_back (v[i]);
		}
 
		v = move (w);
 
		for (int ptr = 0; ptr < len; ptr++) {
			ll l = (q + 2 * q - g(ptr * len)) % (2 * q);
			
			ll k = lower_bound (v.begin(), v.end(), make_pair (l, -1LL)) - v.begin ();
 
			mn = min (mn, make_pair (abs (v[0].first + 2 * q - l), v[0].second + ptr * len));
			mn = min (mn, make_pair (abs (v.back().first - 2 * q - l), v.back().second + ptr * len));
 
			if (k != v.size ()) mn = min (mn, make_pair (abs (v[k].first - l), v[k].second + ptr * len));
 
			if (k) {
				k--;
				mn = min (mn, make_pair (abs (v[k].first - l), v[k].second + ptr * len));
			}
		}
 
		for (ll i = a + len * len; i <= b; i++) {
			mn = min (mn, {abs (g(i) - q), i});
		}
 
		cout << mn.second << endl;
	}
}
