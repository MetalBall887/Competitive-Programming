#include <ext/pb_ds/assoc_container.hpp>

//It can be shown that it's optimal to take a clique in the graph and translate all liquid to it. Indeed, if there is a pair of unconnected vertices with both
//of them having liquid A and B. If we pour liquid from A to B the total value will either increase or will not. If it won't increase, then pour from B to A.
//This way we can pour all the liquid from one of the vertices in any unconnected pair of vertices, leaving only connected ones i.e. clique.  Since the sum of
//volumes of the liquid is constant, the total value is inversely correlated with the sum of squares of volumes in each vertex in the clique (since all vertices
//are connected we can transform the formula to the square of sums minus sum of squares). Sum of squares with the fixed sum is minimized when the sum is distributed
//evenly, so find a max. clique and distribute the liquid evenly between all vertices in the clique.

using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
const int LIM = 20;
 
int d[1 << 20], g_low[40], k;
int g_up[40];
int n, m;
 
void add (int a, int b) {
	g_up[a] |= (1 << (a - LIM));
	if (b >= LIM) g_up[a] |= (1 << (b - LIM));
	else g_low[a] |= (1 << b);
}
 
int main () {
	cin >> n >> m;
	m *= m;
 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			int c;
			cin >> c;
			if (c) add (i, j);
		}
 
	int ans = 1;
 
	int low = min (LIM, n);
 
	for (int i = 0; i < (1 << low); i++) {
		for (int j = 0; j < low; j++) {
			if ((i >> j) & 1) {
				d[i] = max (d[i], d[i & g_low[j]] + 1);
			}
		}
	}
 
	int high = n - low;
 
	for (int i = 0; i < (1 << high); i++) {
		bool b = true;
		int mask = (1 << low) - 1;
		for (int j = 0; j < high; j++) {
			if ((i >> j) & 1) {
				mask &= g_low[j + low];
				if ((g_up[j + low] & i) < i) {
					b = false;
					break;
				}
			}
		}
 
		if (b) ans = max (ans, __builtin_popcount(i) + d[mask]);
	}
 
	printf("%.10Lf\n", (long double) m * (ans - 1) / (2 * ans));
}
