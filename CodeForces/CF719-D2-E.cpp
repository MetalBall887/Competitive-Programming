#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let's say x_i is a vector (f(i), f(i+1)). Then there is a matrix A such that A(x_i)=x_(i+1), so x_i = A^i(x_0). And increasing a on a segment by x means
//multiplying every corresponding vector by A^x. And now based on this we can build a segment tree with lazy updates.

using namespace __gnu_pbds;
 
#define N 2000003
#define all(x) begin(x), end(x)
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
struct Matrix {
	ll a[2][2];
 
	Matrix (ll x = 0) {
		for (ll i = 0; i < 2; i++)
			for (ll j = 0; j < 2; j++) {
				if (i == j) a[i][j] = x;
				else a[i][j] = 0;
			}
	}
 
	ll* operator[](ll x) {
		return a[x];
	}
 
	Matrix operator* (Matrix b) {
		Matrix c;
 
		for (ll i = 0; i < 2; i++)
			for (ll j = 0; j < 2; j++) {
				for (ll k = 0; k < 2; k++)
					c[i][j] += a[i][k] * b[k][j] % MOD;
				c[i][j] %= MOD;
			}
 
		return c;
	}
 
	vector<ll> operator* (const vector <ll>& v) {
		return {(a[0][0] * v[0] + a[0][1] * v[1]) % MOD, 
				(a[1][0] * v[0] + a[1][1] * v[1]) % MOD};
	}
} fib;
 
Matrix qpow (Matrix a, ll b) {
	Matrix s (1);
 
	while (b) {
		if (b & 1) s = s * a;
		a = a * a;
		b >>= 1;
	}
 
	return s;
}
 
ll a[N], n, m;
 
struct SegTree {
	vector <ll> t[N];
	Matrix t_lazy[N];
	ll start;
 
	vector <ll> merge (vector<ll> a, vector<ll> b) {
		return {(a[0] + b[0]) % MOD, (a[1] + b[1]) % MOD};
	}
 
	void push (ll node) {
		t[node] = t_lazy[node] * t[node];
 
		if (node < start) {
			t_lazy[2 * node] = t_lazy[node] * t_lazy[2 * node];
			t_lazy[2 * node + 1] = t_lazy[node] * t_lazy[2 * node + 1];
		}
 
		t_lazy[node] = Matrix (1);
	}
 
	void build (ll n) {
		start = 1;
		while (start < n) start <<= 1;
 
		fill(t_lazy, t_lazy + 2 * start, Matrix (1));
 
		for (ll i = start; i < 2 * start; i++)
			t[i] = qpow(fib, a[i - start]) * vector <ll> ({0, 1});
 
		for (ll i = start - 1; i; i--) {
			t[i] = merge (t[2 * i], t[2 * i + 1]);
		}
	}
 
	void update (ll node, ll tl, ll tr, ll l, ll r, Matrix x) {
		push (node);
		if (r < tl || tr < l) return;
 
		if (l <= tl && tr <= r) {
			t_lazy[node] = x * t_lazy[node];
			push(node);
			return;
		}
 
		ll tm = (tl + tr) / 2;
 
		update (2 * node, tl, tm, l, r, x);
		update (2 * node + 1, tm + 1, tr, l, r, x);
 
		t[node] = merge (t[2 * node], t[2 * node + 1]);
	}
 
	vector <ll> get (ll node, ll tl, ll tr, ll l, ll r) {
		push (node);
 
		if (r < tl || tr < l) return {0, 0};
 
		if (l <= tl && tr <= r) {
			return t[node];
		}
 
		ll tm = (tl + tr) / 2;
 
		return merge (get (2 * node, tl, tm, l, r), get (2 * node + 1, tm + 1, tr, l, r));
	}
} t;
 
int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
 
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
 
	fib[0][0] = 0, fib[0][1] = 1;
	fib[1][0] = 1, fib[1][1] = 1;
 
	t.build (n);
 
	for (ll i = 0; i < m; i++) {
		ll tp, l, r, x;
		cin >> tp;
 
		if (tp == 1) {
			cin >> l >> r >> x;
			t.update(1, 0, t.start - 1, l - 1, r - 1, qpow (fib, x));
		} else {
			cin >> l >> r;
			cout << t.get(1, 0, t.start - 1, l - 1, r - 1)[0] << endl;
		}
	}
}
