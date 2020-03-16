#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let's divide a sequence into the left and the right part. Left part is a1, a2, ..., ai, right is ai+1, ai+2, ..., an. Let's 
//call elements that are in the left part but should be in the right part for a sequence to be sorted (or vice versa) out of 
//order. Note that there is the same number of elements out of order in both parts. In each iteration if there are elements 
//out of order in both parts, after one will move from the left part to the right part and one from the right - to the left. 
//That means the number of such elements will decrease by 1 in both parts. If there are no such elements, nothing will happen. 
//The sequence is sorted if and only if for each such division of the sequence there are no elements out of order. That means,
//the answer is the maximum of elements out of order between all n possible divisions.
 
using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int a[N], s[N], p[N], n;

struct BIT {
	int t[N];

	void update (int x, int d) {
		for (; x <= n; x = (x | (x + 1)))
			t[x] += d;
	}

	int get (int r) {
		int sum = 0;

		for (; r >= 0; r = (r & (r + 1)) - 1)
			sum += t[r];

		return sum;
	}

	int get (int l, int r) {
		return get (r) - get (l - 1);
	}
} t;

int main () {
	freopen ("sort.in", "r", stdin);
	freopen ("sort.out", "w", stdout);

	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> a[i];
		s[i] = a[i];
	}

	sort (s, s + n);

	for (int i = 0; i < n; i++) {
		int k = lower_bound (s, s + n, a[i]) - s;
		a[i] = k + (++p[k]);
	}

	int ans = 1;

	for (int i = 0; i < n; i++) {
		t.update (a[i], 1);
		ans = max (ans, t.get (i + 2, n));
	}

	cout << ans;
}
