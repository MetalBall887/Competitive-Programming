#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//There is a identity for fibonacci sequence that gcd(F_a, F_b) = F_gcd(a, b), so we need find such x, such that gcd(x, y) <= 2 for y < x. It can be solved with
//a sieve. Numbers can be big but we always keep some of the first digits and the overall number of digits (something similar to how floating-point numbers are
//stored). It's not perfect and may have precision errors but it showed itself to be stable.
 
using namespace __gnu_pbds;
 
#define N 2000001

using namespace std;


typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int p[N], n, x, a[N], ptr;

struct fib {
	ll man;
	int exp;

	fib (double man, int exp) : man (man), exp (exp) {}
	fib () : man (0), exp (0) {}

	fib operator + (fib b) {
		fib c;
		
		if (b.exp > exp) {
			c = fib (man, exp);
			while (c.exp < b.exp) {
				c.exp++;
				c.man /= 10;
			}
			c.man += b.man;
		} else {
			c = fib (b.man, b.exp);
			while (c.exp < exp) {
				c.exp++;
				c.man /= 10;
			}
			c.man += man;
		}

		while (c.man >= 1e18) {
			c.exp++;
			c.man /= 10;
		}

		return c;
	}
} f[N];

int main () {

	for (int i = 3; i < N; i++) {
		if (p[i]) continue;
		for (int j = 2 * i; j < N; j += i)
			p[j] = 1;
	}

	for (int i = 1; i < N; i++) {
		if (p[i]) continue;
		a[ptr++] = i;
	}

	f[1] = f[2] = fib ({1, 0});

	for (int i = 3; i < N; i++) {
		f[i] = f[i-2] + f[i-1];
	}

	while (cin >> x) {
		string ans = to_string(f[a[x+1]].man);
		for (int i = 0; i < min (9, (int) ans.size ()); i++)
			cout << ans[i];
		cout << endl;
	}
}
