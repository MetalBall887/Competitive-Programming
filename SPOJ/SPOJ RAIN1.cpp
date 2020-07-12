#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Note that if the flows betwee roofs form a DAG in which for every vertex there is at most 1 edge going out of it, so the size of the graph is O(n).
//We can find those connections by running a vertical sweepline on rooftops maintaining a set of segments intersecting the sweeping line in BBST like std::set
//Be careful of the order of adding/deleting operations
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll n, a[N], u[N], cur;

vector <ll> g[N];

struct Line {
	ll x1, y1, x2, y2, id;
	ll A, B, C;

	Line () {}
	Line (ll x1, ll y1, ll x2, ll y2, ll id) : id (id) {
		this -> x1 = x1, this -> x2 = x2;
		this -> y1 = y1, this -> y2 = y2;

		ll dx = x2 - x1;
		ll dy = y2 - y1;

		A = -dy;
		B = dx;
		C = -A * x1 - B * y1;
		assert (C == -A * x2 - B * y2);
	}

	bool operator < (const Line& b) const {
		return (C + A * cur) * b.B < (b.C + b.A * cur) * B;
	}
};

set <Line> s;

struct query {
	ll t, x, y;
	Line l;

	query (ll t, ll x, ll y, Line l) : t (t), x (x), y (y), l (l) {
		if (t) this -> y = -y;
	}

	bool operator < (const query& b) {
		return tie (x, t, y) < tie (b.x, b.t, b.y);
	}
};

vector <query> v;

ll count_volume (ll x) {
	if (u[x]) return a[x];
	u[x] = 1;

	for (ll to : g[x]) {
		a[x] += count_volume (to);
	}

	return a[x];
}

int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);

	ll t;
	cin >> t;

	while (t--) {
		cin >> n;

		assert (s.empty ());
		v.clear ();

		fill (g, g + n, vector <ll> ());
		fill (a, a + n, 0);
		fill (u, u + n, 0);

		for (ll i = 0; i < n; i++) {
			ll x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			Line s (x1, y1, x2, y2, i);
			v.push_back (query (0, x1, y1, s));
			v.push_back (query (1, x2, y2, s));
		}

		sort (v.begin(), v.end());

		for (ll i = 0; i < v.size (); i++) {
			query q = v[i];
			cur = q.x;
			if (i && !s.empty ()) {
				auto it = s.begin ();
				a[it -> id] += v[i].x - v[i-1].x;
			}

			if (q.t == 0) {
				auto it = s.insert (q.l).first;
				it++;
				if (it != s.end () && q.l.y1 < q.l.y2) {
					g[it -> id].push_back (q.l.id);
				}
			} else {
				s.erase (q.l);
				auto it = s.lower_bound (q.l);

				if (it != s.end () && q.l.y1 > q.l.y2) {
					g[it -> id].push_back (q.l.id);
				}
			}
		}

		for (ll i = 0; i < n; i++) {
			cout << count_volume (i) << '\n';
		}
	}
}
