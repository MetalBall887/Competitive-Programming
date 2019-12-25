#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//We build a graph G, where there is an edge (u, v) when elevators u and v can be on the same floor. Then for the starting
//and destination floors determine the elevator stopping on it. The hardest part is determining if elevators' paths intersect
//We can represent the floors they stay on as y = k*i + b, where b <= y <= f - 1. So we want to find all such pairs, for which
//k1*x+b1=k2*y+b2, which is a diophantine equation you have to solve. Possible approach is, find approximate max and min x and
//y, for which there is a solution meeting the restraints. Then, in one of those four points there will be a pair of solutions
//eitherway there is none
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const ll N = 1e6, Z = 1e6;

ll f, a, b, n;
vector <ll> g[N];
ll u[100], p[100], sz[100];

ll find (ll x) {
	if (x == p[x]) return x;
	else return p[x] = find (p[x]);
}

void unite (ll a, ll b) {
	a = find (a), b = find (b);
	if (a == b) return;
	if (sz[a] < sz[b]) swap (a, b);
	sz[a] += sz[b];
	p[b] = a;
}

struct Elevator {
	ll a, b;
} v[N];

ll gcd (ll a, ll b, ll & x, ll & y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	ll x1, y1;
	ll d = gcd (b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}
 
bool find_any_solution (ll a, ll b, ll c, ll & x0, ll & y0, ll & g) {
	g = gcd (abs(a), abs(b), x0, y0);
	if (c % g != 0)
		return false;
	x0 *= c / g;
	y0 *= c / g;
	if (a < 0) x0 *= -1;
	if (b < 0) y0 *= -1;
	return true;
}

void shift_solution (ll & x, ll & y, ll a, ll b, ll cnt) {
	x += cnt * b;
	y -= cnt * a;
}
 
ll find_all_solutions (ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy) {
	ll x, y, g;
	if (! find_any_solution (a, b, c, x, y, g))
		return 0;
	a /= g;  b /= g;
 
	ll sign_a = a>0 ? +1 : -1;
	ll sign_b = b>0 ? +1 : -1;
 
	shift_solution (x, y, a, b, (minx - x) / b);
	if (x < minx)
		shift_solution (x, y, a, b, sign_b);
	if (x > maxx)
		return 0;
	ll lx1 = x;
 
	shift_solution (x, y, a, b, (maxx - x) / b);
	if (x > maxx)
		shift_solution (x, y, a, b, -sign_b);
	ll rx1 = x;
 
	shift_solution (x, y, a, b, - (miny - y) / a);
	if (y < miny)
		shift_solution (x, y, a, b, -sign_a);
	if (y > maxy)
		return 0;
	ll lx2 = x;
 
	shift_solution (x, y, a, b, - (maxy - y) / a);
	if (y > maxy)
		shift_solution (x, y, a, b, sign_a);
	ll rx2 = x;
 
	if (lx2 > rx2)
		swap (lx2, rx2);
	ll lx = max (lx1, lx2);
	ll rx = min (rx1, rx2);
 
	return (rx - lx) / abs(b) + 1;
}

bool intersect (Elevator x, Elevator y) {
	//a1x+b1=a2y+b2
	//a1x-a2y=b2-b1
	ll a = x.a, b = -y.a, c = y.b - x.b, x0, y0, g;
	//x.a*x+x.b=f
	//x = (f-x.b)/x.a
	ll rx = (f - x.b) / x.a, ry = (f - y.b) / y.a;
	return find_all_solutions (a, b, c, 0, rx, 0, ry) > 0;
}

int main () {
	ll t;
	cin >> t;
	while (t--) {
		cin >> f >> n >> a >> b;
		for (ll i = 0; i < n; i++) {
			p[i] = i;
			sz[i] = 1;
		}

		for (ll i = 0; i < n; i++) {
			cin >> v[i].a >> v[i].b;
		}

		for (ll i = 0; i < n; i++)
			for (ll j = i + 1; j < n; j++)
				if (intersect (v[i], v[j])) {
					unite (i, j);
				}

		ll st = -1, ed = -1;

		for (ll i = 0; i < n; i++) {
			if (a >= v[i].b && (a - v[i].b) % v[i].a == 0) {
				st = i;
				break;
			}
		}

		bool s = false;

		for (ll i = 0; i < n; i++) {
			if (b >= v[i].b && (b - v[i].b) % v[i].a == 0) {
				ed = i;
				break;
			}
		}

		if (st >= 0 && ed >= 0 && find (st) == find (ed)) cout << "It is possible to move the furniture.";
		else cout << "The furniture cannot be moved.";
		cout << '\n';
	}
}
