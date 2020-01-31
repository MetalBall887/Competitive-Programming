#include <bits/stdc++.h>
//d[x][l][r] - is it possible for an employee x to invite people that way, their jokes will form a consequtive sequence [l;r]
//temp[l][r] - is it possible to invite some direct subordinates of the current worker and have them invite people that way,
//all invitees' jokes will form a segment [l;r] (not including the current worker). Since d[x][l][r] always includes worker
//x itself, we don't have to worry about same direct subordinate being considered in non-intersecting set of temp[l][r].
//each transition is being completed in O(V^3), but instead of O(V) operations with an array, bitset performs 2-4 ORs, so
//with bitset this solution easily passes time limit.
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

vector <int> g[10000];

bitset <101> d[10000][100];
int vm = 101, v[10000], n;

void dfs (int x) {
	bitset <101> temp[101];
	int ptr = 0;
	for (int to : g[x]) {
		dfs (to);
		for (int i = 0; i < vm; i++) {
			temp[i] |= d[to][i];
		}
	}

	for (int i = vm - 1; i >= 0; i--) {
		for (int j = i + 1; j < vm; j++) {
			if (temp[i][j-1]) temp[i] |= temp[j];
		}
	}

	for (int i = 1; i <= v[x]; i++)
		for (int j = v[x]; j < vm; j++)
			if ((i == v[x] or temp[i][v[x] - 1]) and (j == v[x] or temp[v[x] + 1][j])) 
				d[x][i][j] = 1;
}

int main () {
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}

	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		g[a-1].push_back (b - 1);
	}

	dfs (0);

	int ans = 0;

	for (int i = 0; i < vm; i++)
		ans += d[0][i].count ();

	cout << ans;
}
