#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Process usual dp sorted by time. If j < i and x[i] < x[j] holds for all j: d[i] = min(d[j] - U(x[j] - x[i])) + m[i] = min(d[j] - Ux[j]) + m[i] - Ux[i].
//Otherwise we can construct a similar formula for x[i] > x[j]. Maintain two segment trees, for the "lower" one in poistion x[j] save d[j] - Ux[j], same for the
//"upper" one. Now we can solve the problem in O(NlogMaxX), except for occasions when several fairs occur at the same time. In this case we know that if there is
//a set of such fairs at a given moment of time, we start from a left(right)most one and visit all fairs till the right(left)most one. Note that the optimal set
//will always be a segment and in this case the benefit from appending a new fair to the sides of our segment doesn't depend on other fairs and in fact can be
//represented as a number, thus we can find a max sum subsegment on the array.
 
using namespace __gnu_pbds;
 
 
using namespace std;
 
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

const int N = 2000001;
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n, U, D, s, maxx;

struct SegTree {
	vector<int> t;
	int start;

	void build (int n) {
		start = 1;
		while (start < n) start <<= 1;
		t = vector <int> (2 * start, -2e9);
	}

	void update (int x, int d) {
		x += start;

		t[x] = d;
		x >>= 1;

		while (x) {
			t[x] = max (t[2 * x], t[2 * x + 1]);
			x >>= 1;
		}
	}

	int get (int l, int r) {
		l += start, r += start + 1;

		int mx = -2e9;

		while (l < r) {
			if (l & 1) mx = max (mx, t[l++]);
			if (r & 1) mx = max (mx, t[--r]);
			l >>= 1, r >>= 1;
		}

		return mx;
	}
} t_left, t_right;

struct shop {
	int x, t, m;

	bool operator< (shop& b) {
		return t < b.t;
	}
} a[N];

void process (int l, int r) {

	vector <shop> v (a + l, a + r);
	vector <int> ans (r - l), ans_l (r - l), ans_r (r - l);

	sort (v.begin(), v.end(), [&](shop a, shop b) { return a.x < b.x; });

	for (int i = 0; i < v.size (); i++) {
		ans[i] = t_left.get (0, v[i].x) - D * v[i].x + v[i].m;
		ans[i] = max (ans[i], t_right.get (v[i].x, maxx) + U * v[i].x + v[i].m);
	}

	ans_l[0] = ans[0], ans_r.back() = ans.back();

	for (int i = 1; i < v.size (); i++) {
		ans_l[i] = max (ans[i], ans_l[i-1] - D * (v[i].x - v[i-1].x) + v[i].m);
	}

	for (int i = v.size () - 2; i >= 0; i--) {
		ans_r[i] = max (ans[i], ans_r[i+1] - U * (v[i+1].x - v[i].x) + v[i].m);
	}

	for (int i = 0; i < v.size (); i++) {
		ans[i] = max (ans_l[i], ans[i]);
		ans[i] = max (ans_r[i], ans[i]);

		//cout << v[i].x << ' ' << v[i].t << ' ' << ans[i] << endl;

		t_left.update (v[i].x, ans[i] + v[i].x * D);
		t_right.update (v[i].x, ans[i] - v[i].x * U);
	}
}

int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> U >> D >> s;

	for (int i = 0; i < n; i++) {
		cin >> a[i].t >> a[i].x >> a[i].m;
		maxx = max (maxx, a[i].x);
	}

	maxx = max (maxx, s);

	t_left.build (maxx + 1);
	t_right.build (maxx + 1);

	t_right.update (s, -s * U);
	t_left.update (s, s * D);

	sort (a, a + n);

	int last = 0;

	for (int i = 0; i < n; i++) {
		if (a[i].t != a[last].t) {
			process (last, i);
			last = i;
		}
	}

	process (last, n);

	int ans = t_right.get (s, maxx) + U * s;
	ans = max (ans, t_left.get (0, s) - D * s);
	assert (ans >= 0);
	cout << ans;
}
