#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//First observation is, the best way to do this is to choose a segment of restaurants and use each ticket in the restaurant in this segment with the best del.level
//To find out the maximum for each segment let's for each restaurant and ticket find what is the maximal segment where this restaurant offers the best del.level for
//this ticket. It can be done with several techniques basically by finding for this ticket/restaurant combination the closest restaurant with bigger del.level for
//this ticket from left and from right. Suppose it's [L; R] for restaurant X. Then, for all segments [l;r] L <= l <= x and x <= r <= R this will be the choice
//for this ticket. Let d[l][r] be the maximum total deliciousness level for a segment [l;r]. Note that on d[][] this set of segments forms a rectangular subarray, 
//so we can use prefix sum technique to increase total value on all segments [l;r] L <= l <= x and x <= r <= R by the corresponding value Bx,j.
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll p[5001][5001];
ll a[5001], b[5001][200], n, m;

void solve (int t) {
	vector < pair <ll, int> > v;

	for (int i = 0; i < n; i++)
		v.push_back ({-b[i][t], i});

	sort (v.begin(), v.end());

	set <int> s;

	for (auto a : v) {
		ll v = -a.first, l, r, x = a.second;

		auto it = s.upper_bound (x);

		if (it == s.end ()) r = n - 1;
		else r = *it - 1;

		if (it == s.begin ()) l = 0;
		else l = *(--it) + 1;
		p[l][x] += v;
		p[l][r+1] -= v;
		p[x+1][x] -= v;
		p[x+1][r+1] += v;

		s.insert (a.second);
	}
}

int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;

	for (int i = 1; i < n; i++) {
		cin >> a[i];
		a[i] += a[i-1];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) 
			cin >> b[i][j];
	}

	for (int i = 0; i < m; i++) {
		solve (i);
	}

	for (int i = 1; i < n; i++) {
		p[0][i] += p[0][i-1];
		p[i][0] += p[i-1][0];
	}

	for (int i = 1; i < n; i++)
		for (int j = 1; j < n; j++)
			p[i][j] += p[i-1][j] + p[i][j-1] - p[i-1][j-1];

	ll ans = 0;

	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++) {
			ans = max (ans, p[i][j] - a[j] + a[i]);
		}

	ll ans2 = 0;

	cout << ans << endl;
}
