#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//First, substract i from a[i] to get a not strict increasing version. Let f_i(x) be the cost for prefix of size i to become non-decreasing so that i-th element is
//x. Let d_i(x) be the same but i-th element <= x. f_i+1(x) =|x - a[i+1]| + d_i(x). Observe: f_0(x) = |x - a[0]| thus is piecewise linear, if f_i is piecewise
//linear then d_i is as well and the set of breaking points in d_i is a subset of this set of f_i, if d_i is piecewise linear, f_i+1 is as well and the set of
//breaking points is either the same or can differ by {a[i+1]}. Thus, all these functions are piecewise linear, the set of breaking point is a subset of numbers
//in a, so in search for minimum we have to check only them. And just like that we made this coordinate compression.
 
//using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll d[2][3000], n, a[3000], s[3000];
 
int main () {
	cin >> n;
 
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i] -= i;
		s[i] = a[i];
	}
 
	sort (s, s + n);
 
	for (int i = 0; i < n; i++) {
		int k = i % 2;
 
		for (int j = 0; j < n; j++) {
			d[k][j] = d[!k][j] + abs (s[j] - a[i]);
			if (j) d[k][j] = min (d[k][j], d[k][j-1]);
		}
	}
 
	cout << d[1 - n % 2][n-1];
}
