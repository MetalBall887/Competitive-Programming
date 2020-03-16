
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
//Let d[i] be the answer tp the problem for a prefix of size i. Obviously d[i-1] <= d[i]. We can find d[i] by the reccurence
//d[i] = d[x] + 1 for such x that the last leap of d[x] will be smaller than the leap (x;i). Of course this relation is not
//complete because we don't know he last leap of d[x]. Now the greedy observation is, by taking x as close as possible you're
//BOTH minimizing the length of the new leap and maximizing d[i], because d[x] <= d[x+1]. That means, we can for each position
//greedily find the optimal start of the last leap by assuming that for all x < i last leaps are optimal (we can keep each
//start of the optimal leap in d_m[x]) and find with binary search the first position we can leap to from this one.
 
using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll d_m[N], d[N], p[N], a[N], n;
 
int main () {
	cin >> n;
 
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		p[i] = a[i] + (i ? p[i-1] : 0);
	}
 
	memset (d_m, -1, sizeof (d_m));
 
	for (int i = 0; i < n; i++) {
		if (i) d_m[i] = max (d_m[i], d_m[i-1]);
		d[i] = (d_m[i] >= 0 ? d[d_m[i]] : 0) + 1;
 
		int l = i + 1, r = n;
 
		while (l < r) {
			int mid = (l + r) / 2;
			if (p[i] - p[d_m[i]] <= p[mid] - p[i]) r = mid;
			else l = mid + 1;
		}
 
		d_m[l] = max (d_m[l], (ll)i);
	}
 
	cout << d[n-1];
}
