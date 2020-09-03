#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//Since the size is fixed, we can identify each rectangle with a left upper corner (just "corner" further). Calculate the cost of each rectangle with usual
//instruments (sliding windows, prefix sums) and sort all rectangles by the priority. Then try to put each rectangle in this order but check if it doesn't
//intersect with already placed ones. We can do this be containning d[i][j] - the number of rectangles intersecting one with corner in (i, j). We can use some
//data structure there and can update this array after placing each rectangle. We can do this because all placed rectangles are already disjunct and at most
//4 of the will overlap with the new one so each d[i][j] will be updated at most 4 times


//using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll A[1001][1001], mn[1001][1001], sum[1001][1001], sum2[1001][1001];
ll n, m, a, b, sm, p[1000][1000];
 
 
void update (ll x1, ll y1, ll x2, ll y2) {
	for (int i = max (0LL, x1); i <= min (n - 1, x2); i++)
		for (int j = max (0LL, y1); j <= min (m - 1, y2); j++)
			p[i][j] = 1;
}
 
ll get (ll x, ll y) {
	return p[x][y];
}
 
struct window {
	deque <pair <ll, ll>> d;
 
	ll peek () {
		assert (!d.empty ());
		return d.front().first;
	}
 
	void push (ll x, ll i) {
		while (d.size () && d.back ().first >= x) d.pop_back ();
		d.push_back ({x, i});
	}
 
	void pop (ll i) {
		if (i == d.front ().second) d.pop_front ();
	}
 
	void clear () {
		while (!d.empty ()) d.pop_back ();
	}
} d;
 
struct place {
	ll x, i, j;
 
	bool operator < (const place& b) {
		return tie (x, i, j) < tie (b.x, b.i, b.j);
	}
};
 
int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> a >> b;
 
	for (ll i = 0; i < n; i++) {
		ll sm = 0;
		d.clear ();
		for (ll j = 0; j < m; j++) {
			cin >> A[i][j];
			d.push (A[i][j], j);
			sm += A[i][j];
			if (j >= b) {
				d.pop (j - b);
				sm -= A[i][j-b];
			}
			sum[i][j] = sm;
			mn[i][j] = d.peek ();
		}
	}
 
	for (ll j = b - 1; j < m; j++) {
		sm = 0;
		d.clear ();
		for (ll i = 0; i < n; i++) {
			d.push (mn[i][j], i);
			sm += sum[i][j];
			if (i >= a) {
				d.pop (i - a);
				sm -= sum[i-a][j];
			}
			sum2[i][j] = sm;
			mn[i][j] = d.peek ();
		}
	}
 
	vector <place> v;
 
	for (ll i = a - 1; i < n; i++)
		for (ll j = b - 1; j < m; j++) {
			v.push_back ({sum2[i][j] - a * b * mn[i][j], i, j});
		}
 
	sort (v.begin (), v.end ());
 
	vector <place> ans;
 
	for (auto x : v) {
		if (get (x.i, x.j)) continue;
		ans.push_back (x);
		update (x.i - a + 1, x.j - b + 1, x.i + a - 1, x.j + b - 1);
	}
 
	cout << ans.size () << '\n';
 
	for (auto x : ans) {
		cout << x.i - a + 2 << ' ' << x.j - b + 2 << ' ' << x.x << '\n';
	}
}
