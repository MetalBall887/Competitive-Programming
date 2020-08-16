#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//First assume we fly all the time. Of course we will not have enough stamina, so everytime we need some, we can do two things: walk/swim instead of flying on some
//and if we already walk/swim everywhere we can, we can walk back an forth on one meter to regain energy. Changing flying to not flying costs less time, doing
//anything on water cost less time, so everytime we choose the cheapest way to regain energy (only when we need it, otherwise fly as long as you can).
 
using namespace __gnu_pbds;
 
#define N 1000000
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int M = 1e6;
 
ll n, a[N];
 
string s;
 
ll st, ans;
 
int main () {
	cin >> n;
 
	for (int i = 0; i < n; i++)
		cin >> a[i];
 
	cin >> s;
 
	ll g = 0, w = 0;
	bool bg = false, bw = false;
 
	for (int i = 0; i < n; i++) {
		st -= a[i]; ans += a[i];
		if (s[i] == 'G') { bg = true; g += 2 * a[i]; }
		if (s[i] == 'W') { bw = true; w += 2 * a[i]; }
		
		ll c = min (w, -st);
		st += c;
		w -= c;
		ans += c;
 
		c = min (g, -st);
		st += c;
		g -= c;
		ans += 2 * c;
 
		if (bw) ans += 3 * (-st);
		else if (bg) ans += 5 * (-st);
		else assert (0);
		st = 0;
	}
 
	cout << ans;
}
