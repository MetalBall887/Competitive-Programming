#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//d[i][j] - the number of ways to add n numbers to the sequence that has maximum j. Observation is, the only rule is we can't
//assign j+1 to the element if there was no j in the prefix before it. So we either add an element 1...j and add others as in
//d[i-1][j] or add j+1 and continue as d[i-1][j+1]. Hence, d[i][j] = j*d[i-1][j] + d[i-1][j+1]. For a seqence lexicographically
//smaller there is a common prefix with the given sequence, than an element smaller than the i-th one and after that any of 
//correct sequences with respect to the maximum in the prefix (the number of which we can quickly find by our dp). So let's
//iterate through prefixes, say, a[1]...a[i-1], next element will be < a[i] and then it will be d[n-i][max(a[1]...a[i-1])], so
//the number of sequences smaller than a with first i-1 elements same is (a[i] - 1)*d[n-i][max(a[1]...a[i-1])]. We can optimize
//one dimension by going from the end and calculating dp synchronically with queries.
 
using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e6 + 7, MOD2 = 1e6 + 3;
 
ll ans = 1, d[10001][2], a[N], n, mx[N];
 
int main () {
	cin >> n;
 
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		mx[i] = a[i];
		if (i) mx[i] = max (mx[i], mx[i-1]);
	}
 
	for (int i = 0; i < n; i++) {
		d[i][0] = 1;
	}
 
	for (int i = n - 1; i >= 0; i--) {
		int k = ((n - i) & 1);
		
		for (int j = 0; j <= n; j++) {
			d[j][k] = (j * d[j][!k] + d[j+1][!k]) % MOD;
		}
		
		ans = (ans + (a[i] - 1) * d[i ? mx[i-1] : 0LL][!k]) % MOD;
	}
 
	cout << ans;
}
