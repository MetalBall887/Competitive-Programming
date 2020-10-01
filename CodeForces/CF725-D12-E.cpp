#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let X be a set of proposed coins, S the sum of their values. First, remove the coins that we don't expect to be taken. Now exactly before taking the largest
//of coins from X we expect that we need at least S more coins so all of our coins will be taken. If this request is satisfied at this point, it is satisfied
//any moment before, so if we replace X with one coin of value S, it will appear earlier and will be taken as well. Thus, if there is a soluion for S, using one
//coin of size S will work as well. Now try all values of a coin from 1 to C and simulate the process. But it will be slow in case there are many coins of small
//value. The trick is to process all coins of the same values in O(1). If there are n different values, the sum of them is at least n(n+1)/2, so the simulation
//works in O(sqrt(C))
 
using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
 
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, c, a[N], w[N], nx[N];
 
bool check (int x) {
 
	int price = c, r = c;
 
	while (price) {
		if (!nx[min (price, r)]) return false;
		int v = min (nx[price], nx[r]);
		if (x <= price && x >= v) {
			price -= x;
			x = N;
		}
		else {
			r = v - 1;
			price -= v * min (w[v], price / v);
		}
	}
 
	if (x < 0) w[x]--;
 
	return true;
}
 
int main () {
	cin >> c >> n;
 
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		w[a[i]]++;
		nx[a[i]] = a[i];
	}
 
	for (int i = 0; i <= c; i++) {
		if (!nx[i]) nx[i] = (i ? nx[i-1] : 0);
	}
 
	for (int i = 1; i <= c; i++) {
		if (!check (i)) {
			cout << i;
			return 0;
		}
	}
 
	cout << "Greed is good";
}
