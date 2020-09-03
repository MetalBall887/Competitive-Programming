#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>

//Let d[i] be the number of distinct subsequences whaere the last character is i. Note that if you add c to the end of the string, d[c] will become the number
//of all distinct subsequences before +1. So regardless of the character we add d[c] wil become the asme, so it's optimal to always put the character with the
//lowest d[c]. Apparently, this character is the one that has the soonest last occurence in the string because if i < j, then sll subsequences ending in j will
//contain all subsequences ending in i with a[j] appended. Therefore, it's optimal to always append a character with the soonest last occurence in the string.

//using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll sum, a[N], d[100], n, m, k, last[200];
 
string s;
 
int main () {
	cin >> m >> k;
 
	cin >> s;
 
	n = s.length ();
 
	fill(last, last + k, -1);
 
	for (int i = 0; i < n; i++) {
		a[i] = s[i] - 'a';
		last[a[i]] = i;
	}
 
	for (int i = 0; i < k; i++)
		a[n + i] = i;
 
	sort (a + n, a + n + k, [&](int a, int b) { return last[a] < last[b]; });
 
	for (int i = n + k; i < n + m; i++)
		a[i] = a[i-k];
 
	for (int i = 0; i < n + m; i++) {
		ll nw = sum + 1;
		if (nw == MOD) nw -= MOD;
 
		sum += MOD + nw - d[a[i]];
		if (sum >= MOD) sum -= MOD;
		if (sum >= MOD) sum -= MOD;
 
		d[a[i]] = nw;
	}
 
	cout << (sum + 1) % MOD << endl;
}
