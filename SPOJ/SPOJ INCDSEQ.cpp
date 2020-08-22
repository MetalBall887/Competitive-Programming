#include <iostream>
#include <algorithm>
//#include <ext/pb_ds/assoc_container.hpp>
//Let d[x][j] be the number of distinct subsequences of length j ending with x. Say we calculated it for some sequence and want to append l to this sequence.
That can affect d[l][j] for each l. Let's iterate on second last element of the subsequences, d[l][j] is the sum over all l' < l d[l'][j-1]. Notice that we don't
//have to consider d[l][j] from the previous occurence of l in the sequence because all those subsequences will be repeated by the new l. Add data structures for
//better complexity
 
//using namespace __gnu_pbds;
 
#define N 100000
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int M = 5e6;

int n, a[N], d[N][50], s[N], k;

struct BIT {
	int t[N];

	void update (int x, int d) {
		if (d >= M) d -= M;
		for (; x <= n; x = (x | (x + 1))) {
			t[x] += d;
			if (t[x] >= M) t[x] -= M;
		}
	}

	int get (int r) {
		int sum = 0;

		for (; r >= 0; r = (r & (r + 1)) - 1) {
			sum += t[r];
			if (sum >= M) sum -= M;
		}

		return sum;
	}
} t[51];

int main () {
	cin >> n >> k;

	for (int i = 0; i < n; i++) {
		cin >> a[i];
		s[i] = a[i];
	}

	sort (s, s + n);

	for (int i = 0; i < n; i++) {
		a[i] = lower_bound (s, s + n, a[i]) - s;
	}

	for (int i = 0; i < n; i++) {
		if (!d[a[i]][0]) {
			d[a[i]][0] = 1, t[0].update (a[i], 1);
		}

		for (int j = 1; j < k; j++) {
			int x = t[j-1].get (a[i] - 1);

			t[j].update (a[i], x + M - d[a[i]][j]);
			d[a[i]][j] = x;
		}
	}

	cout << t[k-1].get (n - 1);
}
