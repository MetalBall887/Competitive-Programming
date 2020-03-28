#include <bits/stdc++.h>
//K = 1 is a classical problem, where we can view each segment as a function f_k(x) that returns the length of the path between
//work and home if the bridge is at x. when x < l_k the derivative of this function is -1, when l_k <= x < r_k, it's 0, when
//r_k <= x, it's 1. The derivative of the sum over all f_i(x) will be the ((#endpoints <= x)  - (#endpoints > x)) / 2. So the 
//minimum is when it's 0 -> is on the median.
//Let's say S1 and S2 are sets of people for which the first or the second bridge is closer correspondingly, F1(S) - the 
//answer for the set of segments S with one bridge (which is computed just like above), F2(S) - the same with two bridges.
//For K = 2 the second observation is, it's enough for every person to choose the bridge the middle between his path from 
//work to home is closer to. That means we can sort paths by those middles and then on this sequence S1 and S2 will be a 
//prefix/suffix. Now let the minimal answer be some setup, for which the bridges are not the medians of S1 and S2 accordignly.
//Consider these two steps: 1) for S1 with left bridge and S2 with right bridge independently improve the solution with K = 1
//algorithm. The sum of closest distances of S1 and S2 decreased, thus the overall distance sum decreased. 2) Reassign S1 and 
//S2. This will surely decrease the answer as well. Hence, we found a way to optimize the answer and the setup is not minimal.
//That means, the minimal solution will have the left bridge as the median of S1, the same for S2 and the right bridge. Note
//that there are O(N) such arrangements (the number of prefix/suffix S1 and S2 divisions). We can for each prefix and suffix
//compute the running median and try O(N) combinations.
#define N 1000001
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll n, k, median;

ll side = 0, lsum = 0, rsum = 0;
ll pr[N];

priority_queue <ll> l, r;

struct seg {
	ll l, r;

	bool operator < (const seg& b) {
		return l + r < b.l + b.r;
	}
};

vector <seg> v;

void insert (ll x) {
	if (!l.size ()) {
		median = x;
		l.push (x);
		lsum += x;

		return;
	}

	if (x <= median) { l.push (x), lsum += x; }
	else { r.push (-x), rsum += x; }

	ll len = (l.size () + r.size () + 1) / 2;

	if (l.size () > len) {
		ll k = l.top ();
		l.pop ();
		r.push (-k);
		lsum -= k, rsum += k;
	}

	if (l.size () < len) {
		ll k = -r.top ();
		r.pop ();
		l.push (k);	
		lsum += k, rsum -= k;
	}

	median = l.top ();
}

int main () {
	cin >> k >> n;

	for (ll i = 0; i < n; i++) {
		string a, b;
		ll la, lb;
		cin >> a >> la >> b >> lb;
		if (a == b) side += abs (la - lb);
		else v.push_back ({la, lb});
	}

	sort (v.begin (), v.end ());


	for (ll i = 0; i < v.size (); i++) {
		insert (v[i].l), insert (v[i].r);
		pr[i] = rsum - lsum;
	}

	ll n = v.size ();


	if (k == 2) {
		lsum = 0, rsum = 0;
		
		while (!l.empty ()) l.pop ();
		while (!r.empty ()) r.pop ();

		ll mx = pr[n-1];

		for (ll i = n - 1; i >= 0; i--) {
			insert (v[i].l), insert (v[i].r);
			mx = min (mx, rsum - lsum + (i ? pr[i-1] : 0));
		}

		cout << mx + side + n;
	}
	else cout << pr[n-1] + side + n;
}
