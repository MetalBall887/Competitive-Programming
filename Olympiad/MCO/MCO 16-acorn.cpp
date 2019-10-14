#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//We simply build an upper envelope of these functions with Convex Hull Trick and add x-axis into it to reject all negative 
//maximals. For every line in this envelope check if lies on some integer x and if integer x is one of its endpoints, check
//if it is actually maximal there because it also depends on k.
#include <fstream>
#include <set>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll n, good[1000000];

struct line {
	ll k, b, id;
	bool operator < (const line& a) {
		if (k == a.k) return b < a.b;
		else return k < a.k;
	}
} cht[1000000];

ll ptr;

bool bad (line a, line b, line c) {
	return (a.b - c.b) * (b.k - a.k) < (a.b - b.b) * (c.k - a.k);
}

void add (line x) {
	while (ptr >= 2 && bad (cht[ptr-2], cht[ptr-1], x))
		ptr--;
	cht[ptr++] = x;
}
 
int main () {
	cin >> n;

	vector <line> v;

	for (ll i = 0; i < n; i++) {
		ll a, b;
		scanf ("%lld%lld", &a, &b);
		v.push_back ({b, -b * a, i});
	}

	v.push_back ({0, 0, -1});

	sort (v.begin(), v.end());

	for (ll i = 0; i <= n; i++)
		add (v[i]);

	ll ans = 0;

	for (ll i = 0; i < ptr; i++) {

		if (!i || i == ptr - 1) continue;

		ll l = (cht[i-1].b - cht[i].b) / (cht[i].k - cht[i-1].k); 
		if ((cht[i-1].b - cht[i].b) % (cht[i].k - cht[i-1].k)) l++;
		else if (cht[i-1].k > cht[i].k) l++;
		ll r = (cht[i+1].b - cht[i].b) / (cht[i].k - cht[i+1].k);
		if ((cht[i+1].b - cht[i].b) % (cht[i].k - cht[i+1].k) == 0) {
			if (cht[i+1].k > cht[i].k) r--;
		}

		if (l > r) ans++;
	}

	cout << ans + n - ptr + 1;
}
