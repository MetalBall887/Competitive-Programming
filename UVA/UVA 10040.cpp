#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
//The type of sequence we're using is De-Bruijn sequence and finding it requires processing the De-Bruijn graph
//and finding the Euler cycle in it. You can find more about De-Brujin squence via the Internet. Algorithm I used 
//for finding Euler cycle is Hierholtz algorithm with a modification that we always takes the lexicographically smallest
//chain and starts inserting subchains from the end to leave as much of the chain prefix we  found untouched as possible, 
//since it is the optimal one
#include <map>
#include <set>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>

using namespace std;

typedef long long ll;

const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const ll N = 1e6, Z = 1e6;

int n, k, bn;

vector <int> g[10 * N];
vector<pair <int, int> > ans, d[23];
int u[23];

void find_chain (int x) {
	vector <int> v;
	while (g[x].size ()) {
		v.push_back (x);
		int to = g[x].back ();
		g[x].pop_back ();
		x = to;
	}
	ans.push_back ({v.back (), v[0]});
	for (int i = v.size () - 1; i >= 0; i--) {
		int x = v[i];
		if (g[x].size ()) {
			find_chain (x);
		}
		if (i != v.size () - 1) ans.push_back ({x, v[i+1]});
	}
}

int main () {
	ios::sync_with_stdio (0);
	cin.tie (NULL);
	int t;
	cin >> t;
	while (t--) {
		cin >> n >> k;

		if (n == 1 && k == 1) {
			cout << 1 << '\n';
			continue;
		}

		int p = n;

		if (!u[n]) {

			n = (1 << (n - 1));

			for (int i = 0; i < n; i++)
				g[i].clear ();
			ans.clear ();

			for (int i = 0; i < n; i++) {
				int x = i;
				x <<= 1;
				if (x >= n) x -= n;
				g[i].push_back (x + 1);
				g[i].push_back (x);
			}

			find_chain (0);
			reverse (ans.begin (), ans.end ());

			d[p] = ans;
			u[p] = 1;
		}

		int a = d[p][k].first * 2 + d[p][k].second % 2;

		cout << a << '\n';
	}
}
