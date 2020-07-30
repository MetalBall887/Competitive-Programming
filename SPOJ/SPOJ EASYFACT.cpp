#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let k be the length of a sequence of consecutive numbers, its sum is n!. For this sequence we know k*median = n!. In this case either k is odd or median
//is in the form (s+s+1)/2, n! = k*(2*s+1)/2=(k/2)*(2*s+1). In both ways k*(2*median)=2n! and k/2 <= median -> k <= 2*median. That way, if x is odd divisor of n!
//and n!/x is greater than x, there is a sequence of x numbers with median n!/x, otherwise there is a sequence of 2n!/x numbers with median equal to x/2.
//Since 2*median is bigger than the length of sequence, "big" x will become 2*median, "small" x will become the length. Therefore, there is only one way
//to represent a consecutive sequence with sum = n! for each odd divisor of n!. What's left is to count the number of them. For each odd prime divisor
//count the number of occurences of i in factorization of n!. If this divisor is > sqrt(n), there are at most sqrt(n) occurences, so between all odd prime
//divisors > sqrt(n) there areonly O(sqrt(n)) different number of occurences, so we can "step" in ranges of the same numbers of occurences and find the end
//of the current range with binary search. The number of divisors <= sqrt(n) is O(sqrt(n)). Notice that for divisors> sqrt(n) function "count" works in O(1),
//so the overall complexity is O(tsqrt(n)log(n)).
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int MAXN = 1e8;
 
bitset<MAXN + 1> er;
 
vector <int> pr;
 
int n, m, t;
 
int count (int pr) {
	int sum = 0;
	int s = n;
	while (s) {
		sum += s / pr;
		s /= pr;
	}
 
	return sum % m;
}
 
ll qpow (ll a, ll b) {
	ll s = 1;
 
	while (b) {
		if (b & 1) s = s * a % m;
		b >>= 1;
		a = a * a % m;
	}
 
	return s;
}
 
int main () {
	cin >> t;
 
	for (int i = 2; i <= MAXN / i + 1; i++) 
		if (!er[i]) 
			for (int j = i * i; j <= MAXN; j += i)
				er[j] = 1;
 
	for (int i = 3; i <= MAXN; i++)
		if (!er[i]) pr.push_back (i);
 
	while (t--) {
		ll ans = 1;
		cin >> n >> m;
 
		int bl = 1e4, j = 0;
		for (; pr[j] <= min (bl, n); j++) {
			ans *= count (pr[j]) + 1;
			ans %= m;
		}
 
		int last_count = count (pr[j]);
 
		while (pr[j] <= n) {
			int l = j + 1, r = pr.size ();
 
			while (l < r) {
				int mid = (l + r) / 2;
				if (last_count > count (pr[mid])) r = mid;
				else l = mid + 1;
			}
 
			ans *= qpow (last_count + 1, l - j);
			ans %= m;
 
			if (l == pr.size ()) break;
 
			last_count = count (pr[l]);
			j = l;
		}
 
		ans += m - 1;
		if (ans >= m) ans -= m;
 
		cout << ans << '\n';
	}
} 
