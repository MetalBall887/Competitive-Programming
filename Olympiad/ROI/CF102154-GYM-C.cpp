#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>

//Solution for 80 points is pretty straightforward: if we want to put i-th number on position j, shift(i, j) will halve the distance.
//For 100 points we solve the problem in reverse order (sorting an inverse permutation) and use the operation reversed to shift. Now shift(0, 2 * i + 1)
//pushes i-th element to 2 * i + 1, which is on average much more effective than the usual shift. We can mix a permutation and apply this solution which is
//randomized linear

//using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, m, t, p[3000];
 
int a[3000], b[3000];
 
vector < pair <int, int> > ans;
 
void shift (int l, int r) {
	assert ((r - l) % 2);
	int len = (r - l + 1) / 2, ptr1 = l, ptr2 = l + len;
	for (int i = l; i <= r; i++) {
		if ((i - l) % 2) {
			b[i] = a[ptr1++];
		} else b[i] = a[ptr2++];
	}
 
	for (int i = l; i <= r; i++)
		a[i] = b[i];
}
 
int main () {
	cin >> n;
 
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
		a[p[i]] = i;
	}
 
	if (n > 1) {
		shift (1, n - n % 2);
 
		for (int j = 1; j <= n; j++) {
			p[a[j]] = j;
		}
 
		ans.push_back ({1, n - n % 2});
	}
 
	int end = n;
 
	for (int i = n; i >= 1; i--) {
		int x = p[i];
 
		while (x != end) {
			int len = min (x, end - x);
			shift (x - len + 1, x + len);
			ans.push_back ({x - len + 1, x + len});
			x += len;
		}
		end--;
 
		for (int j = 1; j <= n; j++) {
			p[a[j]] = j;
		}
	}
 
	cout << ans.size () << endl;
 
	reverse (ans.begin(), ans.end());
 
	for (auto a : ans) {
		cout << a.first << ' ' << a.second << '\n';
	}
}
