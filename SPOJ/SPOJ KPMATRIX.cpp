#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let's solve only for sums <= S.
//There is a general way to find the sum on subrectangle with 2d prefix sums. Let p[i][j] be the sum on (0, 0, i, j). 
//Them sum on (i, j, k, l) will be p[i][j] - p[i][l-1] - p[k-1][j] + p[k-1][l-1]. Let A = p[i][l-1], B = p[k-1][j], A&B = p[k-1][l-1], X = p[i][j].
//X - A - B + A&B <= S
//-(A - A&B) <= S - (X - B)
//For every X there are O(n) different k's. For each such k let's store in BIT all -(A - A&B) for every l and do a scanline on columns where we simultaneously
//add -(A - A&B) to the structure and finding the number of these elements <= S - (X - B).
 
using namespace __gnu_pbds;
 
#define N 800003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, m, A, B;
 
struct BIT {
	int t[252];
 
	void update (int x, int d) {
		for (; x <= m + 1; x = (x | (x + 1)))
			t[x] += d;
	}
 
	int get (int r) {
		int sum = 0;
 
		for (; r >= 0; r = (r & (r + 1)) - 1)
			sum += t[r];
 
		return sum;
	}
 
	void clear () { memset (t, 0, sizeof (t)); }
} t;
 
int a[250][250], sum, p[250][250];
 
ll calc (int S) {
	ll sum = 0;
 
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= i; j++) {
			
			vector <int> a;
 
			vector <int> v (m);
 
			for (int k = 0; k < m; k++) {
				v[k] = p[i][k] - (j ? p[j-1][k] : 0);
 
				a.push_back (-v[k]);
			}
 
			a.push_back (0);
 
			sort (a.begin(), a.end());
 
			t.update (lower_bound (a.begin(), a.end(), 0) - a.begin(), 1);
 
			for (int k = 0; k < m; k++) {
				int x = upper_bound (a.begin(), a.end(), S - v[k]) - a.begin () - 1;
 
				sum += (ll) t.get (x);
 
				x = lower_bound (a.begin(), a.end(), -v[k]) - a.begin ();
				t.update (x, 1);
			}
 
			t.clear ();
		}
		
	return sum;
}
 
int main () {
	cin >> n >> m;
 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
			p[i][j] = a[i][j];
			if (i) p[i][j] += p[i-1][j];
			if (j) p[i][j] += p[i][j-1];
			if (i && j) p[i][j] -= p[i-1][j-1];
		}
 
	cin >> A >> B;
 
 
 
	cout << calc (B) - calc (A - 1);
} 
