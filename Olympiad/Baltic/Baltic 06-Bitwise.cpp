#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//There is a greedy approach. Let's process bits from the highes to the lowest. If we can set the bit in all groups, we have 
//to. For bit x we have to choose in each group the number where we should set the bit. Let's assume all numbers are between 
//0 and 2*2^x - 1. Then we divide all numbers into 3 groups: those that can't have x-th bit is bit set to 1 (R < 2^x), 
//those that can't have the x-th bit set to 0 (L >= 2^x) and others (L < 2^x <= R).  After we chose the number, we set the 
//bit and make sure our assumption still works: for numbers from the first group don't change anything, for the second group 
//subtract thex-th bit since it will not play role in lower bits. For the third group if we set the bit, put L = 2^x and 
//treat as the second group. If we didn't, put R = 2^x-1 because 2^x-1 is 111111... which is already the most optimal value 
//and can set all bits of the group to 1. We can choose the most "harmless" number to set bit in the greedy way. For two 
//numbers from different groups: 1) if one of the is from the first group, take the another one 2) if one of them is from the 
//second group take it. If they are from the same groups: 1) both from 1 - "take none", take any of them, 2) both from 2 - 
//take any of them both numbers already have the bit set to 1, 3) both from 3 - again, take any, one will set x-th bit, other 
//can set all other bits.
 
using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;



struct num {
	ll l, r;

	int ch (int x) {
		if (r < (1 << x)) return 0;
		if (l >= (1 << x)) return 2;
		return 1;
	}

	bool operator < (const num& b) const {
		int bin = 30;
		num x = *this, y = b;

		while (bin >= 0 && x.ch (bin) == y.ch (bin)) {
			if (x.l >= (1 << bin)) {
				x.l -= (1 << bin), x.r -= (1 << bin);
				y.l -= (1 << bin), y.r -= (1 << bin);
			}
			bin--;
		}

		if (bin < 0) bin++;

		return x.ch (bin) < y.ch (bin);
	}
};

vector <vector <num>> v;

int n, p;

int main () {
	cin >> n >> p;

	v.resize (p);

	for (int i = 0; i < p; i++) {
		int k;
		cin >> k;
		v[i].resize (k);
	}

	for (int i = 0; i < p; i++) {
		for (num& x : v[i])
			cin >> x.l >> x.r;
	}

	ll ans = 0;

	for (ll b = 30; b >= 0; b--) {
		bool ok = false;
		for (int i = 0; i < p; i++) {
			ok = false;
			for (num& x : v[i]) {
				if (x.ch (b)) {
					ok = true;
				}
			}

			if (!ok) break;
		}

		if (ok) {
			num zero {-1, 0};
			num* mx = &zero;

			for (int i = 0; i < p; i++) {
				mx = &zero;

				for (num& x : v[i]) {
					if (mx == &zero || *mx < x) mx = &x;
				}

				assert (mx -> ch (b));
				
				if (mx -> ch (b) == 1) {
					mx -> l = 0;
					mx -> r -= (1 << b);
				}
			}

			ans += (1LL << b);
		}

		for (int i = 0; i < p; i++) {
			for (num& x : v[i]) {
				if (x.ch (b) == 1) x.r = (1 << b) - 1;
				if (x.ch (b) == 2) {
					x.l -= (1 << b);
					x.r -= (1 << b);
				}
			}
		}
	}

	cout << ans << endl;
}
