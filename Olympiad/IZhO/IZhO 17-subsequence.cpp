#include <bits/stdc++.h>
//A suboptimal approach is, for every element keep the table d[x] - the length of the maximal valid subsequence, ending on
//x. Then there is a trivial solution with O(maxA*n). Next solution is an optimised meet-in-the-middle version of this.
//d[i][j][l] - the length of the maximal subsequence that ends with the number, which higher 10 bits correspond to i, 
//(lower 10 bits) AND j has l bits in it. That way, when searching for the previous element for i, 
//we have to only iterate through highest bits, because we know our j (which is lowest 10 bits of the current last) and from 
//every i we can deduce our needed l. Simlarly, when adding the new last element to the table, we have to only iterate
//through all possible j and from j deduce l. Thus, solution works in O(2^(m/2)*n), where m is the logarithm of the maximal 
//value
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int d[1 << 10][1 << 10][11], p[1 << 10][1 << 10][11], pc[1 << 20];
int a[N], k[N], n, bm = (1 << 10) - 1, ans, par[N], ind;

int main () {
	cin >> n;

	for (int i = 0; i < (1 << 10); i++)
		pc[i] = __builtin_popcount (i);

	memset (p, -1, sizeof (p));

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	for (int i = 0; i < n; i++) {
		cin >> k[i];
	}

	for (int i = 0; i < n; i++) {
		int x = 0;
		par[i] = -1;

		for (int j = 0; j < (1 << 10); j++) {
			int l = k[i] - pc[j & (a[i] >> 10)];
			if (l < 0 || l > 10) continue;
			if (x < d[j][a[i] & bm][l]) {
				par[i] = p[j][a[i] & bm][l];
				x = d[j][a[i] & bm][l];
			}
		}

		x++;

		for (int j = 0; j < (1 << 10); j++) {
			int& c = d[a[i] >> 10][j][pc[j & a[i]]];
			if (x > c) {
				c = x;
				p[a[i] >> 10][j][pc[j & a[i]]] = i;
			}
		}

		if (x > ans) {
			ans = x;
			ind = i;
		}
	}

	vector <int> v;

	cout << ans << endl;

	while (ind != -1) {
		v.push_back (ind + 1);
		ind = par[ind];
	}

	reverse (v.begin(), v.end());

	for (int i : v)
		cout << i << ' ';
}
