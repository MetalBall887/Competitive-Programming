#include <bits/stdc++.h>
//Two containers can't be placed in one port if one is not strictly inside of the other but still they overlap. Let's 
//represent it in graph form, where there is an edge between two containers f they can't be place in one port. Then we have
//to check if graph is bipartite by attempting to color containers in two and check if there are edges in any of two 
//same-colored container sets and find the number of possible colorings, that is 2^the number of components. We can do dfs
//if we could have a structure where for each container we could find one container accessible by an edge unless there is 
//one, add a container and delete a container. Then we could first add all containers and start dfs from any container, delet
//ing it after visiting, since we don't have to visit it again. Now how do we find such structure? if we represent a container
//as a range, all containers directly connected with the edge either have left ends in range and right ends out of it or the
//opposite. That's where we use segment trees to find maximum/minimum on range, so if there are, for example left ends on the
//range of the current container, if some of those exceed the bound, one with the rightmost right end will do it. 
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, l[N], r[N];
int ind[2 * N];
bitset<2*N> u, col;
 
struct SegTree {
	ll t[8 * N], start;
	bool mx;
	void build (ll n, bool mx) {
		this -> mx = mx;
		start = 1;
		while (start < n) start <<= 1;
		if (mx) fill (t, t + 2 * start, -INF);
		else fill (t, t + 2 * start, INF);
	}
 
	void update (ll x, ll d) {
		x += start;
		t[x] = d;
		x >>= 1;
 
		while (x) {
			if (mx) t[x] = max (t[2 * x], t[2 * x + 1]);
			else t[x] = min (t[2 * x], t[2 * x + 1]);
			x >>= 1;
		}
	}
 
	ll get_max (ll l, ll r) {
		l += start, r += start + 1;
		ll mx = -INF;
 
		while (l < r) {
			if (l & 1) mx = max (mx, t[l++]);
			if (r & 1) mx = max (mx, t[--r]);
			l >>= 1, r >>= 1;
		}
 
		return mx;
	}
 
	ll get_min (ll l, ll r) {
		l += start, r += start + 1;
		ll mn = INF;
 
		while (l < r) {
			if (l & 1) mn = min (mn, t[l++]);
			if (r & 1) mn = min (mn, t[--r]);
			l >>= 1, r >>= 1;
		}
 
		return mn;
	}
} t_l, t_r;
 
bool check (vector <pair <int, int> > v){
	sort (v.begin(), v.end());
	stack < pair <int, int> > st;
	for(ll i = 0; i < v.size (); i++){
		while(!st.empty () && st.top ().second < v[i].first)
			st.pop ();
 
		if(!st.empty () && st.top().second < v[i].second)
			return 0;
 
		st.push (v[i]);
	}
	return 1;
}
 
 
void dfs (ll x, ll c) {
	col[x] = c, u[x] = 1;
	t_l.update (r[x], INF);
	t_r.update (l[x], -INF);
 
	while (true) {
		ll t = t_r.get_max (l[x] + 1, r[x] - 1);
		if(t <= r[x]) break;
		ll to = ind[t];
		dfs (to, !c);
	}
 
	while (true) {
		ll t = t_l.get_min (l[x] + 1, r[x] - 1);
		if(l[x] <= t) break;
		ll to = ind[t];
		dfs (to, !c);
	}
}
 
int main () {
	ios::sync_with_stdio (false);
	cin.tie (NULL);
	cin >> n;
 
	t_l.build (2 * n, false);
	t_r.build (2 * n, true);
	memset (ind, -1, sizeof (ind));
	for (ll i = 0; i < n; i++) {
		cin >> l[i] >> r[i];
		l[i]--, r[i]--;
		ind[l[i]] = ind[r[i]] = i;
		t_l.update (r[i], l[i]);
		t_r.update (l[i], r[i]);
	}
 
	ll ans = 1;
 
	for (ll i = 0; i < 2 * n; i++) {
		if (ind[i] >= 0 && !u[ind[i]]) {
			ans = 2 * ans % MOD;
			dfs (ind[i], 0);
		}
	}
 
	vector < pair <int, int> > a, b;
 
	for (ll i = 0; i < n; i++) {
		if (col[i]) a.push_back ({l[i], r[i]});
		else b.push_back ({l[i], r[i]});
	}
 
	if (!check (a) || !check (b)) {
		cout << 0;
		return 0;
	}
 
	cout << ans << endl;
}
