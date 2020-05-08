	
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Each tower i sees all towers to the left until the first to the left higher then the i-th one. If we remove this higher tower
//i-th tower will see more until the next higher tower. So for each tower we have to find the rightmost and the second rightmost
//from the left. Let's do this with scanning line. in d we will keep towers that are the highest on their suffix, in d_sec - 
//that are the second highest on their current suffix. After we remove the tower x, sum will lose all towers that tower x sees,
//every tower that sees x-th tower will lose one tower in sight and for every tower for which tower x is the rightmost higher 
//to the left will start seeing more depending on the second rightmost highest to the left.
 
using namespace __gnu_pbds;
 
#define N 1000003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll dc[N], inc[N], a[N], see[N], sum, n;
ll f[N], s[N], k;
 
int main () {
	freopen ("turnuri.in", "r", stdin);
	freopen ("turnuri.out", "w", stdout);
	ios::sync_with_stdio (0), cin.tie (0);
	
	cin >> n;
 
	for (int i = 0; i < n; i++)
		cin >> a[i];
 
	vector < pair <ll, ll> > d, d_sec;
	d.push_back ({2e9 + 1, 0});
	d_sec.push_back ({2e9 + 1, 0});
		
	for (int i = 0; i < n; i++) {
		vector < pair <ll, ll> > t;
		while (d.back ().first <= a[i]) {
			t.push_back (d.back ());
			d.pop_back ();
		}
 
		while (d_sec.back ().first <= a[i]) {
			d_sec.pop_back ();
		}
 
		f[i] = d.back ().second;
		s[i] = d_sec.back ().second;
		if (d.size () > 1) s[i] = max (s[i], d[d.size () - 2].second);
 
		while (t.size ()) {
			d_sec.push_back (t.back ());
			t.pop_back ();
		}
		d.push_back ({a[i], i});
	}
 
	for (int i = 0; i < n; i++) {
		inc[i] = 0;
		dc[f[i]]++;
		dc[i]--;
		see[i] = i - f[i];
		inc[f[i]] += f[i] - s[i];
		sum += see[i];
	}
 
	ll ans = 0;
 
	for (int i = 0; i < n; i++) {
		if (i) dc[i] += dc[i-1];
		ans += sum - see[i] + inc[i] - dc[i];
	}
 
	cout << ans << '\n';
}
