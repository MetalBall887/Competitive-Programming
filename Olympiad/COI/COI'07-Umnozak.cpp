#include <bits/stdc++.h>
//First, let's bound the number of digit-products. The main part here is, it can have only 4 prime divizors: 2,3,5,7. Also,
//it can't be bigger than the number itself. Since we need self-products < 1e18, the product of digits is at most root of it,
//so at most 1e9. 2 can appear at most 3 times in each digit, 3 - only twice, 5 and 7 - once. That means, for a max. 10-digit
//numbers we can bound the number of products as 30*20*10*10=60000. In reality, this number is even lower. Now we can for each
//such digit-product apply digit dp, where the state is the digit length of the number and the product of its digits.
 
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

map <ll, ll> d[20], sum; 

ll A, B;

ll get_max (ll pref, ll p, ll len) {

	for (ll i = 0; i < len; i++) {
		for (ll j = 9; j > 0; j--) {
			if (p % j == 0) {
				pref = pref * 10 + j;
				p /= j;
				break;
			}
		}
	}

	return pref;
}

ll get_min (ll pref, ll p, ll len) {
	for (int i = 0; i < len; i++) {
		pref *= 10;
	}

	return pref;
}

ll Rec (ll pref, ll len, ll R, ll p, ll m) {
	if (!len) {
		return (p == 1 && pref <= R / m);
	}

	if (R / m  <= get_min (pref, p, len)) return 0;
	if (get_max (pref, p, len) <= R / m) return d[len][p];
	
	ll sum = 0;
	for (ll i = 1; i < 10; i++) {
		if (p % i == 0) sum += Rec (pref * 10 + i, len - 1, R, p / i, m);
	}

	return sum;
}

int main () {
	cin >> A >> B;

	d[0][1] = 1;

	for (ll i = 0; i <= 18; i++) {
		for (auto a : d[i]) {
			for (ll j = 1; j < 10; j++) {
				d[i+1][j * a.first] += a.second;
			}
		}
	}

	ll ans = 0;

	for (auto a : d[11]) {
		for (ll i = 1; i <= 18; i++) {
			ans += Rec (0, i, B, a.first, a.first) - Rec (0, i, A - 1, a.first, a.first);
		}
	}

	cout << ans;
}
