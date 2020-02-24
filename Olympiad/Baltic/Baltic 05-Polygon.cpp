#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//One of the solutions is, given the segments, we can try to place polygon's vertices on a circle. We can binsearch the radius of this
//circle with the record of how many degrees we "rotated" while constructing the polygon. It's not clear about what the R should be, so
//from a fixed l we start checking all [l; 2l], [2l; 4l], [4l;8l] ... until we find the right bound in logarithmic time
 
using namespace __gnu_pbds;
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const double pi = acos (-1);
 
double ang (double a, double c) {
	return acos (1 - c * c / (2 * a * a));
}
 
int n, a[N], sum;
pair <double, double> ans[N];
 
double construct (double r, bool dw) {
	double deg = (dw ? 2 * pi - ang (r, a[0]) : ang (r, a[0]));
	ans[0] = {r * cos (deg), r * sin (deg)};
	for (int i = 1; i < n; i++) {
		deg += ang (r, a[i]);
		ans[i] = {r * cos (deg), r * sin (deg)};
	}
 
	return deg;
}
 
int main () {
	cin >> n;
 
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		sum += a[i];
	}
 
	sort (a, a + n);
	reverse (a, a + n);
	if (sum <= 2 * a[0]) {
		cout << "NO SOLUTION\n";
		return 0;
	}
 
	double l = a[0] / 2.0, r = a[0];
	int dw = 0;
 
	if (construct (l, 0) < 2 * pi) dw = 1;
 
	while (dw ^ (construct (r, dw) > 2 * pi)) {
		l = r, r = 2 * r;
	}
 
	for (int i = 0; i < 70; i++) {
		double mid = (l + r) / 2;
		double deg = construct (mid, dw);
 
		if ((deg > 2 * pi) ^ dw) l = mid;
		else r = mid;
	}
 
	for (int i = 0; i < n; i++) {
		printf ("%.9lf %.9lf\n", ans[i].first, ans[i].second);
	}
}
