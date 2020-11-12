#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//We can choose a letter alpha and denote each letter < alpha as 0, = alpha as 1 and > alpha as 2. For each such alpha we need tp find the number of rectangles
//such that all symbols in it are 0, except top right corner and low bottom corner are either 1 or 2 and at least one of them is 1 (to avoid repetitions).
//This can be done simlarly to counting the number of rectangles of 0, except each place where our non-decreasing subhistogram changes height corresponds to some 
//non-zero symbol that isn't covered with other non-zero symbols.
 
using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
 
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int h[1000][1000], a[1000][1000];
 
int s[1000], eq[1000], eq_ptr, ptr, n;
 
ll ans;
 
int main () {
	freopen ("ssdj.in", "r", stdin);
	freopen ("ssdj.out", "w", stdout);
 
	cin >> n;
 
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < n; j++) {
			a[i][j] = s[j] - 'a';
		}
	}
 
	for (int x = 0; x < 26; x++) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				if (a[i][j] >= x) {
					h[i][j] = 0;
				}
				else {
					if (!i || h[i-1][j] == -1) h[i][j] = -1;
					else h[i][j] = 1 + (i ? h[i-1][j] : 0);
				}
			}
 
		for (int i = 1; i < n; i++) {
			eq_ptr = ptr = 0;
			for (int j = 0; j < n; j++) {
				if (h[i-1][j] != -1) {
					while (ptr && s[ptr-1] >= h[i-1][j]) {
						if (eq[ptr-1]) eq_ptr--;
						ptr--;
					}
				}
				if (a[i][j] > x) ans += eq_ptr;
				if (a[i][j] == x) ans += ptr;
 
				if (h[i-1][j] != -1) {
					s[ptr] = h[i-1][j];
					eq[ptr] = (a[i-h[i-1][j]-1][j] == x);
					eq_ptr += eq[ptr];
					ptr++;
				}
 
				if (!h[i][j]) eq_ptr = ptr = 0;
			}
		}
	}
 
	cout << ans << endl;
}
