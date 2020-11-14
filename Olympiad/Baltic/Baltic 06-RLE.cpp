#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//First decode the sequence and simultaneously compress it in blocks of the same size (char, size of block), because the length of the decoded string can be big. 
//Then d[j] - the length of the code for the compressed sequence, where the current repetition mark is j. Note that if the i-th block is not equal to the repetition
//mark, it's optimal to leave the repition mark as is and for such that rep. mark the cost of coding the block will be the same. That means. all d[*] except
//one d[x] will be increased by the same value when adding a new block to the sequence where x is the character of the new block. for d[x] we can either 
//assume the rep. mark was x when encoding the block (which will lead to the higher cost) or use some other rep. mark and change it to x in the end. if
//all other d[*] the cost will increase by C1 and for d[x] it will increase by C2, we can increase a global margin by C1 and change d[x] by C2 - C1. We can show
//that the minimum will not decrease i.e. C2 > C1. d_new[x] = min(d_new[*]) + 3 or d_new[x] = d[x] + (cost for char = rep. mark). In first case it automatically
//stops being a minimum, so a minimum is raised by C1, in the second one C2 is directly the cost and for x will cost more. Mens if minimum is O(m) (bounded by
//the input code), is integer and only increases, the whole algorithm works in O(n + m)
using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll n, m, a[N], s[N], sz[N], ptr, cur_min;
ll rev[N];
vector <ll> cnt[7 * N];
multiset <pair <ll, ll>> st;
 
ll d[N], glob, offset = 1000000;
 
ll f_e (ll sz) {
	return (sz + n - 1) / n * 3;
}
 
ll f_k (ll sz) {
	ll block = n + 2;
	return sz / block * 3 + min (3LL, sz % block);
}
 
ll get_min () {
	cur_min = max (cur_min - 3, 0LL);
	while (true) {
		auto& v = cnt[cur_min];
 
		while (!v.empty () && d[v.back ()] + offset != cur_min) v.pop_back ();
		if (v.size ()) return v.back ();
		cur_min++;
	}
}
 
void update (ll x, ll v) {
	v -= glob;
	d[x] = v;
	cnt[v + offset].push_back (x);
}
 
void add (ll x, ll y) {
	if (ptr && s[ptr-1] == x) sz[ptr-1] += y;
	else s[ptr] = x, sz[ptr] = y, ptr++;
}
 
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cin >> n >> m;
 
	cur_min = offset;
 
	ll e = 0, x;
 
	while (cin >> x) {
		if (x == e) {
			ll a, b;
			cin >> a >> b;
 
			if (a == e) add (a, b + 1);
			else if (b == 0) e = a;
			else add (a, b + 3);
		} else add (x, 1);
	}
 
	fill (d + 1, d + n, 3);
 
	for (ll i = 0; i < n; i++) {
		update (i, d[i]);
	}
 
	for (ll i = 0; i < ptr; i++) {
		ll shift = f_k (sz[i]), old = d[s[i]] + glob;
		glob += shift;
 
		update (s[i], old + f_e (sz[i]));
 
		if (d[get_min ()] + glob + 3 < old + f_e (sz[i])) {
			update (s[i], d[get_min ()] + glob + 3);
			rev[i] = get_min ();
		} else {
			update (s[i], old + f_e (sz[i]));
			rev[i] = s[i];
		}
		//cout << s[i] << ' ' << sz[i] << ' ' << d[0] + glob << ' ' << f_e(sz[i]) << ' ' << old << endl;
		//cout << s[i] << ' ' << sz[i];
		//for (ll i = 0; i < n; i++)
		//	cout << d[i] + glob << ' ';
		//cout << endl;
	}
 
	ll y = get_min ();
 
	vector <ll> ans;
 
	for (ll i = ptr - 1; i >= 0; i--) {
		if (s[i] != y) ans.push_back (y);
		else {
			ans.push_back (rev[i]);
			y = rev[i];
		}
	}
 
	reverse (ans.begin(), ans.end());
 
	cout << d[get_min ()] + glob << endl;
 
	e = 0;
 
	for (ll i = 0; i < ptr; i++) {
		//cout << s[i] << ' ' << sz[i] << endl;
		if (e != ans[i]) {
			cout << e << ' ' << ans[i] << ' ' << 0 << ' ';
			e = ans[i];
		}
		if (s[i] == e) {
			while (sz[i]) {
				ll block = min (n, sz[i]);
				cout << e << ' ' << s[i] << ' ' << block - 1 << ' ';
				sz[i] -= block;
			}
		} else {
			while (sz[i] >= 3) {
				ll block = min (n + 2, sz[i]);
				cout << e << ' ' << s[i] << ' ' << block - 3 << ' ';
				sz[i] -= block;
			}
 
			while (sz[i]--) {
				cout << s[i] << ' ';
			}
		}
		
		//cout << endl;
	}
}
