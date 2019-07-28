#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
//label[x] - the uninity level of the vertex x. if there is two vertices with same levels and there are some elements
//bigger their levels, one of them connected these two vertices while constructing the graph. If there is no, these vertices
//are parent-child, which is prohibited. f[i][j] = 1 when we can't assign vertex i uninity j, because there will
//is another vertex with uninity j and if connected now, path between them will be wrong (see above).
//the key is always taking the lowest available number, because taking another one won't optimise the solution in any way
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

int n;

vector <int> g[1000000];

int label[1000000], f[300000][20], ans;

int dfs (int x, int p)
{
	int mx = 0;
	for (int to : g[x])
		if (to != p)
		{
			dfs (to, x);

			for (int i = 0; i < 20; i++)
			{
        //if there are already two vertices with level i banned, we can't ignore it, as x is LCA of these two points
        //and we can connect these two vertices in a wrong way if label[x] <= i
				if (f[x][i] && f[to][i]) mx = max (mx, i);
				f[x][i] |= f[to][i];
			}
		}
  
  //if f[x][i] = 1, we can't do label[x] = i, because then we would create a wrong path
	while (f[x][mx]) mx++;
  
  //besides that, we take minimal possible
	label[x] = mx;

	ans = max (label[x], ans);

	f[x][mx] = 1;

	for (int i = 0; i < mx; i++)
		f[x][i] = 0;

	return label[x];
}

int main ()
{
	cin >> n;

	for (int i = 0; i < n - 1; i++)
	{
		int a, b;

		scanf ("%d%d", &a, &b);

		g[a-1].push_back (b - 1);
		g[b-1].push_back (a - 1);
	}

	dfs (0, -1);

	cout << ans;
}
