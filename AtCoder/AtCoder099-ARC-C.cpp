#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string.h>
//First, consider an inverted graph for this one. Dividing the original graph into two cliques will be dividing inverted into two independent
//sets, basically constructing a bipartite one. So if there are cycles of odd length, it is impossible. If not, we will have some connected
//components divided into two sets independently, so for a fixed "side" of our bipartite graph first assign the smallest sides from connected
//components then try "changing sides" for each component. Since maximal set's size is N, we can apply O(N^2) knapsack dp.
#include <cstdlib>
#include <vector>
#include <string>
#include <bitset>
#include <math.h>
#include <queue>
#include <stack>
#include <set>
#include <map>
 
typedef long long ll;
typedef long double ld;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

int n, m;

vector <int> g[1000000];

int f (int a, int b)
{
	return a * (a - 1) + b * (b - 1);
}

int cl[1000000], u[1000000], d[700][700], cnt[1000][2];
 
bool dfs (int x, int c, int bw)
{
	u[x] = 1;
	cl[x] = bw;
	cnt[c][bw]++;

	for (int to : g[x])
	{
		if (u[to] && cl[x] == cl[to]) return false;
		if (!u[to] && !dfs (to, c, !bw)) return false;
	}

	return true;
}

int main ()
{
	cin >> n >> m;

	for (int i = 0; i < m; i++)
	{
		int u, v;

		scanf ("%d%d", &u, &v);

		d[u-1][v-1] = 1;
		d[v-1][u-1] = 1;
	}

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (!d[i][j])
			{
				g[i].push_back (j);
				g[j].push_back (i);
			}

	int color = 0;

	for (int i = 0; i < n; i++)
		if (!u[i] && !dfs (i, ++color, 0))
		{
			cout << -1;
			return 0;
		}

	vector <int> v;

	int sum = 0;

	for (int i = 1; i <= color; i++)
	{
		sum += min (cnt[i][0], cnt[i][1]);
		v.push_back (abs (cnt[i][0] - cnt[i][1]));
	}

	vector <int> d (n + 1);

	d[0] = 1;

	for (int a : v)
	{
		for (int i = n; i >= 0; i--)
			if (d[i]) d[i + a] = 1;
	}

	int ans = 1e9;

	for (int i = 0; i <= n; i++)
	{
		if (d[i])
			ans = min (ans, f (i + sum, n - i - sum));
	}

	cout << ans / 2;
}
