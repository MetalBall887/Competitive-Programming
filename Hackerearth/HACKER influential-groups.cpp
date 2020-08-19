#include <iostream>
#include <algorithm>
//#include <ext/pb_ds/assoc_container.hpp>
//Let's put all people with less influential value in set A, all other people in set B. A group G is considered good if the number of elements from A is not less
//than from B. So if there are j elements from B in G, there will be j + s for some nonnegative s j + s <= |A|. For each such good group G we can construct a 
//unique group G', where people from B in G and people from A not in G appear. If there are j people from B in G', there are |A| - (j+s) of them from A for some s.
//Now notice that for the fixed s the number of people in G' is always |A| - s. It can be shown that any combination of |A| - s people from the original set of people
//appears as a group G', so the number of all possible G' groups with given A and B is Comb(n, |A| - s), where s is a difference between the number of people from 
//B and A and can't be < 0. Iterate over all possible s and add all possible distributions, in the end it will be the sum of first |A| binomial numbers on the
//n-th row. Also count that the person itself is included in the group and is in the set B, so the set B always has at least one element in thre group.
//using namespace __gnu_pbds;
 
#define N 1000000
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int M = 1e6;

ll qpow (ll a, ll b) {
	ll s = 1;

	while (b) {
		if (b & 1) s = s * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}

	return s;
}

ll a[N], d[N], s[N], n, q;

int main () {
	cin >> n >> q;

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	sort (a, a + n);
	s[0] = d[0] = 1;
	for (int i = 1; i < n; i++) {
		d[i] = d[i-1] * qpow (i, MOD - 2) % MOD * (n - i) % MOD;
		s[i] = s[i-1] + d[i];
		if (s[i] >= MOD) s[i] -= MOD;
	}

	for (int i = 0; i < q; i++) {
		int x;
		cin >> x;
		int k = lower_bound(a, a + n, x) - a;
		cout << s[k] << endl;
	}
}
