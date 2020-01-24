#include <bits/stdc++.h>
//d[mask][x] - the expected number score if you start with a table where all tile sizes are bits in the mask and length of
//the table is x. The fact that the tiles moving by 1 is the same as moving to the beginning. Also when the sequence on the
//table is not monotonous (it can be only xxx24xxx here) the left part will not be engaged in any merges, so we can forget 
//it and pretend table just shortened.
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
double d[N][17], p;
int n, t, it;
int u[17][300000];
 
double evl (int mask, int x) {
	double sum = 0;
	for (int i = x; i < 20; i++) {
		if (mask & (1 << i)) sum += (1 << i);
		else break;
	}
 
	return 2.0 * sum;
}
 
double Rec (int mask, int x) {
	int b = __builtin_popcount (mask);
	if (b >= x) return 0;
 
	if (u[x][mask] == it) return d[mask][x];
	u[x][mask] = it;
 
	if (mask & 2) {
		d[mask][x] = p * Rec (4, x - b);
	} else {
		d[mask][x] = p * (evl (mask, 2) + Rec (mask + 4, x));
	}
 
	d[mask][x] += (1.0 - p) * (evl (mask, 1) + Rec (mask + 2, x));
 
	return d[mask][x];
}
 
int main () {
	cin >> t;
 
	while (t--) {
		it++;
		cin >> n >> p;
		p /= 100.0;
		printf ("%.9lf\n", Rec (0, n));
	}
}
