#include <bits/stdc++.h>
//When considering all of the possibilities, it's enough to consider only the set of the worst ones. For example, if we
//already have some set of colors from the left shelf, the worst case is, in the right shelf we took all of them but not
//with colors from the set. So we need to take all with colors not from set + 1 to secure at least one pair. Now we can solve
//this problem for each possible set of colors from the left shelf. For each set we know the smallest and the biggest number
//of gloves we can this set from: [the size of the set; the sum of numbers of gloves colored in one of the set colors].
//That way we have 2^n ranges and we can do a scanning line on these ranges and for each starting/after ending state (it's
//not optimal to consider others because we don't change the set of colors but only increase the number of gloves taken)
//from all possible color sets consider the worst. We can keep the color set by a segment tree.
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll a[20], b[20], n, sa[1 << 20], sb[1 << 20];
bitset <2 * N> isz;
 
vector< pair <ll, ll> > ad, rm, q;
 
vector <ll> sorted;
 
struct SegTree {
	ll t[(1 << 22)], start;
 
	void build (int n) {
		start = n;
 
		fill (t, t + 2 * start, INF);
	}
 
	void update (int x, ll d) {
		x += start;
 
		t[x] = d;
		x >>= 1;
 
		while (x) {
			t[x] = min (t[2 * x], t[2 * x + 1]);
			x >>= 1;
		}
	}
} t;
 
int main () {
	cin >> n;
 
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
		sa[1 << i] = a[i];
	}
 
	for (ll i = 0; i < n; i++) {
		cin >> b[i];
		sb[1 << i] = b[i];
	}
 
	for (ll i = 1; i < (1 << n); i++) {
		if (i == (i & -i) && !sa[i]) isz[i] = 1;
		else if (isz[i & -i] || isz[i - (i & -i)]) isz[i] = 1;
		sa[i] = sa[i - (i & -i)] + sa[i & -i];
		sb[i] = sb[i - (i & -i)] + sb[i & -i];
		if (!isz[i]) {
			q.push_back ({__builtin_popcount (i), -i});
			q.push_back ({sa[i] + 1, i});
		}
	}
 
	t.build (1 << n);
 
	pair <ll, ll> ans = {INF, INF};
 
	sort (q.begin(), q.end());
 
	for (ll i = 0; i < q.size (); i++) {
		if (q[i].second < 0)  {
			t.update (-q[i].second, sb[-q[i].second]);
		}
		else t.update (q[i].second, INF);
 
		if (i < q.size () - 1 && q[i].first < q[i+1].first) {
			pair <ll, ll> x = {q[i].first, sb[(1 << n) - 1] - t.t[1] + 1};
			if (x.second > sb[(1 << n) - 1]) continue;
			if (ans.first + ans.second > x.first + x.second)
				ans = x;
		}
	}
 
	cout << ans.first << endl << ans.second;
}
