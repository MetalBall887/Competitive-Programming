#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Subproblem of this problem is, find the number of connected graphs where the number of edges and vertices is the same
//(thus there is only one cycle) and the length of the cycle is k and the number of vertices is n. First let's take k vertices
//from n to be in the cycle and find the number of cycles of n vertices. 
//Let's try to make cycles from permutations by connecting nodes that are adjacent in permutation + the first with the last. 
//Note that for each permutation there will be n-1 cycle shifts of it that will create the same cycle and each permutation 
//has its reverse clone that will also create the same cycle. After eliminating all cycleshifts and mirror clone (say, 
//leaving only lexicographically minimal ones) we will have n!/2n permutations that will generate different cycles.
//After we found for a fixed combination of k vertices the number of cycles it can create we have to find the number of ways
//to construct a forest where each cycle node is a root of a different tree. Luckily, there is a Cayley's formula generalization
//that says the number of such forest with k components and n vertices is k*n^(n-k-1). Combined, we get the formula
//cyc[i][j] ...the number of connected graphs with i vertices, i edges and a cycle of length j.
//cyc[i][j] = C(i, j) * (j-1)!/2 * j*n^(n-j-1)
//Now we can find the d[i] - the answer for n = i with reccurence formula (for each j) d[i] += C(i-1, j-1) * comp[j] * d[i-j].
//We chose C(i-1,j-1), because the i-th element has to be in the last component to avoid overcounting.

using namespace __gnu_pbds;

#define N 2000001

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const ll INF = 1e18, MOD = 30011, MOD2 = 1e6 + 3;

ll d[500], comp[500], n, k, c[500][500], fact[N];

ll qpow (ll a, ll b) {
	if (b == -1) b = MOD - 2;
	ll s = 1;

	while (b) {
		if (b & 1) s = s * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}

	return s;
}

ll C (ll n, ll k) {
	return fact[n] * qpow (fact[k] * fact[n-k] % MOD, MOD - 2) % MOD;
}

int main () {
	freopen ("shgraf.in", "r", stdin);
	freopen ("shgraf.out", "w", stdout);
	cin >> n >> k;

	memset (c, -1, sizeof (c));

	fact[0] = 1;

	for (ll i = 1; i <= n; i++) {
		fact[i] = i * fact[i-1] % MOD;
	}

	ll inv_2 = qpow (2, MOD - 2);

	for (ll i = k; i <= n; i++) {
		for (ll j = k; j <= i; j++) {
			comp[i] += j * qpow (i, i - j - 1) % MOD * C (i, j) % MOD * (fact[j - 1] * inv_2 % MOD) % MOD;
			comp[i] %= MOD;
		}
	}

	d[0] = 1;

	for (ll i = 1; i <= n; i++) {
		for(ll j = k; j <= i; j++) {
			d[i] += d[i-j] * C (i - 1, j - 1) % MOD * comp[j] % MOD;
		}
		d[i] %= MOD;
	}

	cout << d[n];
}
