#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Build a convex hull on the set of white points and on the set of black points and check if it intersects. There is a O(n) scanning line algorithm for it but 
//it's not necessary as we could check in O(n^2) if any of segments of convex hulls intersect. If no, either one of them lies inside another or they both are
//disjunct. It's enough to check if any point from white convex hull lies inside of the black convex hull and vice versa. As there are O(n + m) edges in both
//hulls, the overall algorithm is O((n+m)^2)

using namespace __gnu_pbds;
 
#define N 2000003
#define all(x) begin(x), end(x)
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};
 
template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
 
template<class P> vector<P> segInter(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b),
	     oc = a.cross(b, c), od = a.cross(b, d);
	// Checks if intersection is single non-endpoint point.
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
		return {(a * ob - b * oa) / (ob - oa)};
	set<P> s;
	if (onSegment(c, d, a)) s.insert(a);
	if (onSegment(c, d, b)) s.insert(b);
	if (onSegment(a, b, c)) s.insert(c);
	if (onSegment(a, b, d)) s.insert(d);
	return {all(s)};
}
 
template<class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
	int cnt = 0, n = p.size ();
	for (int i = 0; i < n; i++) {
		P q = p[(i + 1) % n];
		if (onSegment(p[i], q, a)) return !strict;
		//or: if (segDist(p[i], q, a) <= eps) return !strict;
		cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * a.cross(p[i], q) > 0;
	}
	return cnt;
}
 
typedef Point<long double> Pt;
typedef pair <Pt, Pt> Line;
 
int n, m;
 
vector <Pt> convex_hull (vector <Pt> a) {
	int ptr = 0;
	sort (a.begin(), a.end());
 
	vector<Pt> lower, upper;
 
	for (Pt p : a) {
		while (ptr > 1 && lower[ptr-2].cross(lower[ptr-1], p) < 0) {
			lower.pop_back ();
			ptr--;
		}
		lower.push_back (p);
		ptr++;
	}
 
	reverse (a.begin(), a.end());
	ptr = 0;
 
	for (Pt p : a) {
		while (ptr > 1 && upper[ptr-2].cross(upper[ptr-1], p) < 0) {
			upper.pop_back ();
			ptr--;
		}
 
		upper.push_back (p);
		ptr++;
	}
 
	for (int i = 1; i < upper.size () - 1; i++) {
		lower.push_back (upper[i]);
	}
 
	return lower;
}
 
int main () {
 
	while (cin >> n >> m) {
		if (!n && !m) break;
		bool yes = true;
		vector <Pt> a (n), b (m);
 
		for (int i = 0; i < n; i++) {
			cin >> a[i].x >> a[i].y;
		}
 
		for (int i = 0; i < m; i++) {
			cin >> b[i].x >> b[i].y;
		}
 
		a = convex_hull (a);
		b = convex_hull (b);
 
		for (int i = 0; i < a.size (); i++) {
			if (!yes) break;
			for (int j = 0; j < b.size (); j++) {
				auto k = segInter(a[i], a[(i+1) % a.size ()], b[j], b[(j+1) % b.size ()]);
				if (!k.empty ()) {
					yes = false;
					break;
				}
			}
		}
 
		long double S = 0;
 
		if (inPolygon(a, b[0]) || inPolygon(b, a[0])) yes = false;
 
		if (yes) cout << "YES\n";
		else cout << "NO\n";
	}
} 
