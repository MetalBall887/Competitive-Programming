#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
//Let's define a grundy number for each tree. For each subtree of this tree we can delete all other subtrees and get this
//subtree with an old root above. Xor of grundy numbers of these new trees for each subtree is the grundy number for the 
//original tree. Now to find a grundy number of our trees with "antennae" above, we can claim that for subtree with 1 vertex
//this modification will bring grundy number 1, for bigger subtrees: we can move exactly to position with number 0 and to
//all positions that we could get with the old subtree but with this "antennae". So by induction we can say that grundy number
//of modified tree is the number for an old tree + 1
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
 
vector <int> g[1000000];
 
int a[1000000], n;
 
int dfs (int x, int p)
{
	for (int to : g[x])
		if (to != p)
			a[x] ^= dfs (to, x) + 1;
 
	return a[x];
}
 
int main ()
{
	cin >> n;
 
	for (int i = 0; i < n - 1; i++)
	{
		int u, v;
 
		scanf ("%d%d", &u, &v);
 
		g[u-1].push_back (v - 1);
		g[v-1].push_back (u - 1);
	}
 
	if (dfs (0, -1)) cout << "Alice";
	else cout << "Bob";
}
