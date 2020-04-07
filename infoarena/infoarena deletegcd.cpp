#include <bits/stdc++.h>
//d[i][j] - the minimal number such that [d[i][j]; i] contains j numbers coprime with a[i]. Can be constructed if each prime
//is processed independently.
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n, m, a[N], q;
int er[N], d[N][2];

vector <int> v[N], dv[N];

int main () {
	freopen ("deletegcd.in", "r", stdin);
	freopen ("deletegcd.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie (NULL);
	cin >> n >> q;

	for (int i = 2; i <= N / i; i++) {
		if (!er[i]) {
			for (int j = i * i; j < N; j += i) {
				er[j] = i;
			}
		}
	}

	fill (d[0], d[0] + N, 1e9);
	fill (d[1], d[1] + N, 1e9);

	for (int i = 0; i < n; i++) {
		cin >> a[i];
		int x = a[i];
		while (er[x]) {
			if (v[er[x]].empty () || v[er[x]].back () < i)
				v[er[x]].push_back (i);
			x /= er[x];
		}
		if (v[x].empty () || v[x].back () < i) v[x].push_back (i);
	}

	for (int i = 2; i < N; i++) {
		int fst = 1, lst = 0;
		for (int j = 0; j < v[i].size (); j++) {
			if (j && v[i][j-1] + 1 == v[i][j]) {
				lst++;
			} else {
				if (j && v[i][j-1] + 2 == v[i][j]) fst = lst;
				else fst = 0;
				lst = 1;
			}

			d[v[i][j]][0] = min (d[v[i][j]][0], v[i][j] - lst + 1);
			d[v[i][j]][1] = min (d[v[i][j]][1], v[i][j] - (fst + lst));
		}
	}

	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		l--, r--;

		if (d[r][1] <= l || d[r-1][0] <= l) cout << "1";
		else cout << "0";
	}
}
