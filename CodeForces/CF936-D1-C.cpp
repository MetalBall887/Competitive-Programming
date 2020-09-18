#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//.....d|.....abc| -> |cba.....|.....d
//cba..........|d| -> |d|cba..........
//|dcba..........| -> |..........abcd|


//using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, len;
 
string s, t;
vector <int> v;
 
string shift (string s, int x) {
	x = (int) s.length () - x;
 
	reverse (s.begin () + x, s.end ());
	return s.substr (x) + s.substr (0, x);
}
 
bool add (char c) {
	int j = 0;
 
	while (j < n - len && s[j] != c) j++;
 
 	if (j == n - len) {
		return false;
	}
 
	v.push_back (n - j - 1);
	v.push_back (1);
	v.push_back (n);
 
	s = shift (s, n - j - 1);
	s = shift (s, 1);
	reverse (s.begin(), s.end());
	len++;
	return true;
}
 
int main () {
	cin >> n;
	cin >> s >> t;
 
	bool ok = true;
 
	for (int i = 0; i < n; i++) {
		ok &= add (t[i]);
	}
 
	if (!ok) {
		cout << -1;
		return 0;
	}
 
	cout << v.size () << endl;
 
	for (auto a : v) {
		cout << a << ' ';
	}
}
