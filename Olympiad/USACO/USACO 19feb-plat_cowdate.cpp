#include <bits/stdc++.h>
//Let's solve the problem for prefixes. Pi is the needed probability for a prefix of length i. Since it's the sum over
//(1-x1)(1-x2)...xk...(1-xi) for each k, which can be written as (1-x1)(1-x2)...(1-xi) times (x1/(1-x1)+x2/(1-x2)+...+xi/(1-xi)),
//which can be grouped to Mi and Si. After solving the equation Pi <= Pi+1 we can find out that it's equivalent to Si <= 1.
//Since Si is increasing, the "optimality" is decreasing monotonically. Moreover, we can add numbers in any order, so it's
//monotonic in both ways. With that we can use a two pointer solution
 
using namespace std;
 
typedef long long ll;

const int N = 1e6 + 1, inf = 1e9;
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n;
long double p[N];

int main () {
	freopen ("cowdate.in", "r", stdin);
	freopen ("cowdate.out", "w", stdout);
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> p[i];
		p[i] /= 1e6;
		p[i] = (1 - p[i]);
	}

	int r = 0;
	long double ans = 0;
	long double m = 1, s = 0;

	for (int l = 0; l < n; l++) {
		if (l) {m /= p[l-1], s -= (1 - p[l-1]) / p[l-1];}

		ans = max (ans, m * s);

		while (r < n && s <= 1.0) {
			m *= p[r], s += (1.0 - p[r]) / p[r];
			r++;
			ans = max (ans, m * s);
		}

		if (r < n) ans = max (ans, p[r] * m * (s + (1.0 - p[r]) / p[r]));
	}

	int d = (ans * 1e6);
	cout << d;
}
