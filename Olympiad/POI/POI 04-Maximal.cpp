#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//Basically, any node in a graph representing permutation has one in-degree and one out-degree, so the graph itself is a 
//set of cycles. we get every node marked by its number. Every new shuffle we move every mark "forward" along the out-edge,
//so for a cycle of length x to get into original position it takes x shuffles. That means, for lengths x1, x2, x3, ...
//we need lcm(x1, x2, x3, ...) steps. Also we know x1 + x2 + x3 + ... = n. Since we're finding maximal lcm, we need only
//one place to have some p^q, where p is a prime, because if there are two numbers divideable by p, only one with the 
//maximal power counts, so by leaving only the biggest power we reduce the sum but don't reduce lcm. Also for p, q > 1 
//(they are prime) p^a + p^b <= p^a * q^b, so we should keep each prime's power in an isolated element (for each prime there
//is a cycle). Then find it with dp.
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

float d[10001][401], lg[100000];

int last[10001][401], t,len;

vector <int> ans;

int er[100001], primes[10001], ptr, n;

int main () {
	cin >> t;

	for (int i = 2; i <= 10000; i++)
		if (!er[i]) {
			primes[ptr++] = i;

			for (int j = i * i; j <= 10000; j += i)
				er[j] = 1;
		}

	for (int i = 0; i <= 10000; i++)
		lg[i] = log (i);

	while (t--) {
		cin >> n;
		len = 0;
		ans.clear ();

		for (int i = 1; primes[i-1] <= n && i <= 350; i++)
			for (int j = n; j >= 1; j--) {
				d[j][i] = d[j][i-1];
				last[j][i] = 0;
				len = max (len, i);
				int p = 1;
				for (; p <= j; p *= primes[i-1]) {
					if (d[j - p][i-1] + lg[p] >= d[j][i]) {
						d[j][i] = d[j - p][i-1] + lg[p];
						last[j][i] = p;
					}
				}
			}

		int x = n, y = len;

		while (x && y) {
			if (last[x][y]) ans.push_back (last[x][y]);
			x -= last[x][y];
			y--;
		}

		if (x) ans.push_back (x);

		sort (ans.begin(), ans.end());

		int p = 1;

		for (int k : ans) {
			for (int i = 1; i < k; i++) {
				printf ("%d ", ++p);
			}

			printf ("%d ", ++p - k);
		}

		putchar ('\n');
	}
}
