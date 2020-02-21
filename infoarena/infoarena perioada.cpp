#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//There is a lemma about borders and periods that says that if in string of size n there is a period of size k, there will be
//a border of size n - k. That means, there is a period of size k if and only if the prefix and the suffix of size n - k are
//the same. It can be checked for some k in a constant time by hashing or by LCA on a suffix tree. I used hashes. For any
//string the size of period must be its divisor. Complexity is O(qsqrt(n)).

using namespace __gnu_pbds;

#define N 1000001

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n, m;
string s;

ull h[N], p[N];
vector <int> dv[N];

ull get (int l, int r) {
	return h[r] - (l ? h[l - 1] * p[r - l + 1] : 0);
}


int main () {
	freopen ("perioada.in", "r", stdin);
	freopen ("perioada.out", "w", stdout);
	ios::sync_with_stdio (0);
	cin >> n >> s >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 2 * i; j <= n; j += i)
			dv[j].push_back (i);
	}

	h[0] = (s[0] - 'a');
	p[0] = 1;
	for (int i = 1; i < n; i++) {
		p[i] = 31 * p[i-1];
		h[i] = h[i-1] * 31 + s[i] - 'a';
	}

	for (int i = 0; i < m; i++) {
		int l, r, ans = 0;
		cin >> l >> r;
		l--, r--;
		for (int d : dv[r - l + 1]) {
			if (get (l, r - d) == get (l + d, r)) ans++;
		}

		cout << ans << '\n';
	}
}
