#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//Count the number of such subsequences with the principle of inclusion-exclusion where we include-exclude the sets of subsequences where each element of the
//subsequence has some mask as a submask. With this, we will find the size of the union of these sets i.e. the set of subsequences where there is at least some
//non-zero common mask - the complementary to what we look for. To solve this, we need to find for each x the number of elements that contain x as a submask.
//The obvious algorithm works in O(3^m) ai <= 2^m. To make it faster, we can use meet-in-the-middle. 
//Find d[l*(1 << 10) + r] - the number of elements first 10 bits of which are exactly l and second 10 bits contain r as a submask. It can be counted in O(6^(n/2)). 
//From this we can for each higher bits traverse all submasks and in O(6^(n/2)) get the answer as well.
 
//using namespace __gnu_pbds;
 
#define N 1000000
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int M = 1e6;
 
int cnt[1 << 20], cnt_r[1 << 20], n, d[1 << 20];
 
int bin[N];
 
int main () {
	cin >> n;
 
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
 
		d[a]++;
	}
 
	bin[0] = 1;
 
	for (int i = 1; i <= n; i++) {
		bin[i] = bin[i-1] + bin[i-1];
		if (bin[i] >= MOD) bin[i] -= MOD;
	}
 
	int m = 20;
 
	for (int i = 0; i < (1 << m); i++) {
		if (!d[i]) continue;
 
		for (int j = i; j & ((1 << 10) - 1); j = (i & (j - 1))) {
			cnt_r[j] += d[i];
		}
 
		cnt_r[(i >> 10) << 10] += d[i];
	}
 
	for (int i = 0; i < (1 << 20); i++) {
		if (!cnt_r[i]) continue;
		int hi = (i >> 10), lo = (i & ((1 << 10) - 1));
 
		for (int j = hi; j; j = (hi & (j - 1)))
			cnt[(j << 10) + lo] += cnt_r[i];
 
		cnt[lo] += cnt_r[i];
	}
 
	ll ans = bin[n] - 1;
 
	for (int i = 1; i < (1 << 20); i++) {
		if (!cnt[i]) continue;
 
		if (__builtin_popcount(i) & 1) ans += MOD - bin[cnt[i]] + 1;
		else ans += bin[cnt[i]] - 1;
 
		if (ans >= MOD) ans -= MOD;
	}
 
	cout << ans;
}
