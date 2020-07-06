#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Mainly is done by logaritmization by the fact  that log n! = log 1 + log 2 + ... + log n. Knowing log n! it's not hard to count combinations logaritmized
//and the whole formula

using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e18 + 7, MOD2 = 1e6 + 3;

long double logfact[N];

struct LargeSignTest {
	string pvalue (int n, int k) {
		if (n == 2 * k) return "100.0%";
		for (int i = 1; i <= n; i++) {
			logfact[i] = log2 ((double) i) + logfact[i-1];
			//cout << i << ' ' << logfact[i] << ' ' << pow (2, logfact[i]) << endl;
		}

		long double ans = 0;

		for (int i = 0; i <= min (k, n - k); i++) {
			//cout << i << ' ' << pow (2, logfact[n] - logfact[i] - logfact[n-i] - (n - 1)) << endl;
			ans += pow (2, logfact[n] - logfact[i] - logfact[n-i] - (n - 1));
		}

		ll ans_i = ll (ans * 1000.0 + 0.5);

		string s;
		if (ans_i >= 1000) s += char (ans_i / 1000 + '0');
		if (ans_i >= 100) s += char (ans_i / 100 % 10 + '0');
		s += char (ans_i / 10 % 10 + '0');
		s += '.';
		s += char (ans_i % 10 + '0');
		s += '%';

		return s;
	}
};
