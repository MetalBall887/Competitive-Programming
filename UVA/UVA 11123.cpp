#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

//First we take each segment and group by the "direction" of the vector of this segment: the vector scaled such way x is 1 or
//if it's vertical, y should be 1. Then we group vectors of each direction by b: the y of a point where the vector crosses
//y-axis or, if it's vertical, by x. Every pair of segments with the same direction but with different b form a trapezoid or
//a parallelogram. Note that each parallelogram is counted twice, so it should be subtracted also twice. To find the number
//of parallelograms there is a technique, where we perceive segments as diagonals and two segments are diagonals of the same
//parallelogram if their middles coincide, because in parallelogram diagonlas intersect in the middle point of each of them.

using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n;

ll ans;

template <class T>
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
};

typedef Point<long double> Pt;
typedef pair <Pt, Pt> Line;

map <Pt, vector <Line> > m;

vector <Pt> v, a;

int cs = 1;

int main () {
	while (cin >> n) {
		if (!n) return 0;

		a.resize (n);
		ans = 0;

		m.clear (), v.clear (), a.clear ();

		for (int i = 0; i < n; i++) {
			cin >> a[i].x >> a[i].y;
		}

		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				auto p = (a[i] - a[j]) / (a[i].x - a[j].x);
				if (a[i].x == a[j].x) p = (a[i] - a[j]) / (a[i].y - a[j].y);
				m[p].push_back ({a[i], a[j]});
			}
		}

		for (auto v : m) {
			int sum = 0;
			map <double, int> cnt;
			for (auto l : v.second) {
				Pt a = l.first, b = l.second;
				if (a.x == b.x) {
					sum++, cnt[a.x]++;
					continue;
				}

				if (a.x > b.x) swap (a, b);
				Pt vec = (b - a) / (b.x - a.x) * -a.x;

				cnt[(a + vec).y]++;
				sum++;
			}

			for (auto x : cnt) {
				ans += (ll) x.second * (sum - x.second);
			}
		}

		map <Pt, vector<Line> > diag;

		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++) {
				diag[a[i] + a[j]].push_back({a[i], a[j]});
			}

		for (auto v : diag) {
			map <Pt, int> cnt;
			int sum = 0;
			for (auto l : v.second) {
				Pt a = l.first, b = l.second;

				auto p = (b - a) / (b.x - a.x);
				if (b.x == a.x) p = (b - a) / (b.y - a.y);
				cnt[p]++;
				sum++;
			}

			for (auto x : cnt) {
				ans -= 2 * (ll) x.second * (sum - x.second);
			}
		}

		cout << "Case " << cs++ << ": " << ans / 2 << endl;
	}
	
}
