#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//Note that we can find a match greedily: for a current adjacent pair of symbols in a string look if these symbols go in the same order in the permutation 
//If no, we have to append a new permutation. Also note that for the pairs with the same symbols we always have to append new permutation. So the number of
//permutations we need is n minus #of adjacent pairs that go in the same order in a permutation. To find it out everytime in O(k^2) we can keep the number of
//adjacent pairs of each coloring (except pairs with the same colors but they never contribute) by holding a set of positions where characters change.
 
//using namespace __gnu_pbds;
 
#define N 100000
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int M = 5e6;
 
set < pair <int, int> > s;
 
int n, m, k, C[50][50];
 
int get (int x) {
	if (x < 0) return k + 1;
	auto it = s.lower_bound ({x, -1});
	return it -> second;
}
 
void insert (int l, int r, int v) {
	int left = get (l - 1), right = get (r + 1);
	C[left][get (l)] --;
 
	auto it = s.lower_bound ({l, -1});
 
	while (it -> first <= r) {
 
		C[it -> second][next(it) -> second]--;
		it++;
		s.erase(prev(it));
	}
 
	it = s.lower_bound ({l - 1, -1});
	if (it -> first != l - 1 && l) {
		s.insert ({l - 1, left});
	}
 
	it = s.lower_bound ({r, -1});
 
	assert (it -> first != r);
	s.insert ({r, v});
 
	C[left][get (l)] ++;
	C[get (r)][right] ++;
}
 
int main () {
	string v;
	
	cin >> n >> m >> k;
	cin >> v;
	
	int last = 0;
 
	s.insert ({n, k + 1});
 
	for (int i = 0; i < n; i++) {
		if (i && v[i] != v[i-1]) {
			insert (last, i - 1, v[i-1] - 'a');
			last = i;
		}
	}
 
	insert (last, n - 1, v[n-1] - 'a');
 
	for (int i = 0; i < m; i++) {
		int t, l, r;
 
		cin >> t;
 
		if (t == 1) {
			cin >> l >> r >> v;
			l--, r--;
 
			insert (l, r, v[0] - 'a');
		} else {
			int ans = n;
			cin >> v;
 
			for (int i = 0; i < k; i++)
				for (int j = i + 1; j < k; j++) {
					ans -= C[v[i] - 'a'][v[j] - 'a'];
				}
 
			cout << ans << '\n';
		}
	}
}
