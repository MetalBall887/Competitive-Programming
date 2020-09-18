#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>

//using namespace __gnu_pbds;
//Instead of maximizing positions where the prince dies let's minimize ones where he doesn't die. There are two ways to set the protection: defending the
//princess from both ways by dragons or letting "the wall" (the end of the sequence) protect from one of the sides. If some side is protected by dragons, 
//the number of safe spots for the prince is defined by the number of the dragons closest to the princess on this side that can't defeat him. For example if
//the princess is on position x and a is some arrangement of dragons, P > a[x], P > a[x] + a[x+1], but P < a[x] + a[x+1] + a[x+2], there are two safe spots for
//a prince on the right side. Also, similarly, let's call a[x], a[x+1], a[x+2] the defenders from the right side. Obviously, we want the defenders be as strong
//as possible so it's always good to sort the dragons so that the stronger dragon is closer to the princess. For the type of defense where one of the sides is 
//defended by the end of the sequence it's obvious that we should put all strongest dragons on the longer side and sort them by strength and we will get the optimal
//arrangement. For the two-sided type we also have to find a good way to direct dragons to both sides. Let L and R be two disjoint sets of dragons such that 
//sum of strengths in L > P, sum of strengths in R > P and |L| + |R| is the smallest possible. If we can use them as defenders for both sides for some princess's
//position, we will get the optimal double-sided arrangement for this position. If for some position we can't use them because of L or R being too big to fit on 
//some of the sides, this will actually mean there is "a wall" defending better than some set of defenders, so there is a one-sided arrangement better than this
//optimal double-sided arrangement and thus better than all of them. That means, we need to find only one such pair of sets and where it doesn't fit, there is no
//point in checking any double-sided arrangements. To find one such arrangement we can sort all dragons by strength and find first n dragons such that we can
//divide it into two sets of defenders. It can be done by some dp tweaks.
//If some dragon is stronger than the prince, we can always defend the princess with him. Otherwise all strengths < P. Thus, there always will be an arrangement
//with difference in strength between L and R is < P, so if sum of strengths in L and R is > 3P, the weakest of the sets will be > P, so we will stop once the
//sum of strength in both sets will be more than 3P. Now since we know the sum of strengths is at most 3P, the number of different strength levels will be at most
//square root of that, we can group dragons by the same strength levels and obtain O(Psqrt(P)) algorithm.

#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
int t, n, p;
int a[N];
int ans[N], minpref[N];
bool d[N];
int f[N];

int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> t;

	while (t--) {

		cin >> n >> p;

		for (int i = 0; i < n; i++)
			cin >> a[i];

		fill (ans, ans + n, 0);

		sort (a, a + n);
		reverse (a, a + n);

		if (a[0] >= p) {
			for (int i = 0; i < n; i++)
				cout << n << ' ';
			cout << endl;
			continue;
		}

		p -= a[0];

		memset (minpref, 0, sizeof (minpref));


		int sum = 0;

		for (int i = 0; i < n; i++) {
			sum += (i ? a[i] : 0);
			if (sum + 1 >= 300000) break;
			minpref[sum + 1] = i + 1;
		}

		for (int i = 1; i <= 300000; i++)
			minpref[i] = max (minpref[i], minpref[i-1]);

		for (int i = 0; i < n; i++) {
			int l = i, r = n - 1 - i;
			ans[i] = max (0, max (l, r) + 1 - minpref[p]);
		}

		memset (d, 0, sizeof (d));
		d[0] = 1;

		int sm = 0, l = 1, r = 1, reg = 1e9;

		while (l < n) {
			while (r < n && a[l] == a[r]) r++;
			if (l > reg) break;

			int x = a[l], cnt = r - l;
			for (int j = max (0, p - x * cnt); j < p; j++)
				if (d[j]) {
					int dist = (p - j + x - 1) / x;

					if (dist > cnt) continue;

					if (minpref[p + dist * x + j] != -1) {
						int pos = max (minpref[p + dist * x + j], l - 1 + dist);
						reg = min (reg, pos);
					}
				}

			for (int j = 0; j < p; j++) {
				if (d[j]) {
					f[j] = 0;
					continue;
				}
				f[j] = 1e9;
				if (j >= x) f[j] = min (f[j], f[j - x] + 1);
				d[j] = f[j] <= cnt;
			}

			l = r;
		}

		for (int i = 0; i < n; i++) {
			ans[i] = max (ans[i], reg < n ? n + 1 - reg : 0);
			cout << ans[i] << ' ';
		}
		cout << endl;
	}
}
