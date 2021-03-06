#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//First, consider the graph with all salaries undefined. We can already say that the root will have the highest salary.
//Then, we can assign salaries with, for example, topological ordering. But that means, if there is a subtree with 
//2+ children, there is more that one topological ordering, which means, that all of the salaries inside of this subtree
//are undefined. So in an empty tree we can define the salary of the root and some lower nodes until there is a node
//with 2+ children. Now let's return to our original problem where some of the nodes are defined. Let's erase all
//edges that lead to the nodes with specified salary. Now we get a forest of rooted trees (We'll call them T-trees), 
//where only the root has a specified salary. For them we can solve this problem inductively. Ti will be the i-th T-tree 
//if ordered by increasing the root salary (ai).
//K is a set of salaries not yet taken. Now for T1 we can define K1 as a subset of salaries in K that are lower than a1 and
//thus can be used in T1. Note that we can take any |T1| salaries from K1, since it is always possible for them to fill
//the vacant places in T1 (but don't forget that we can determine uniquely only the highest path nodes as was told above)
//and also all elements that fit into K1 will fit into any Ki so it also doesn't matter which elements we leave in K.
//So we can greedily pick any |T1| salaries from K1. When |K1|=|T1|, there is only one way to choose the salaries but when
//|K1| > |T1| we can't uniquely determine salaries in T1, neither we can determine which elements from K1 are left in K, so
//all nodes with salaries from K1 (they can be not just from T1, but T2 and else, depending on how big K1 is) remain undefined.
//After we assigned nodes for T1, we consider it processed and remove, now the old T2 is our new T1. Do the same thing by 
//inducktion.
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

vector <int> g[1000001];

int sz[1000001], n, p[1000001], a[1000001], u[1000001], undef[1000001];
int path_end[1000001];

vector <int> decomp[1000001], K;
vector < pair <int, int> > sub;

void dfs_decomp (int x, int root, bool in_path) {

	if (x != root) {
		decomp[root].push_back (x);
	}
	int c = 0;

	for (int to : g[x])
		if (!a[to]) c++;

	if (c > 1) path_end[root] = min (path_end[root], (int) decomp[root].size ());

	for (int to : g[x]) {
		if (a[to]) continue;

		dfs_decomp (to, root, in_path);
	}
}

int main () {

	cin >> n;

	for (int i = 0; i < n; i++) {

		scanf ("%d%d", &p[i], &a[i]);

		if (p[i] - 1 == i) {
			u[n] = 1;
			a[i] = n;
		}
		else {
			g[p[i] - 1].push_back (i);

			if (a[i]) u[a[i]] = 1;
		}
	}

	for (int i = 1; i <= n; i++)
		if (!u[i]) K.push_back (i);

	for (int i = 0; i < n; i++)
		if (a[i]) {
			path_end[i] = n + 1;
			dfs_decomp (i, i, true);
			sub.push_back ({a[i], i});
		}

	sort (sub.begin(), sub.end());

	int l = 0, r = 0, ptr = 0;

	for (auto x : sub) {
		int val = x.first;
		int ind = x.second;

		if (decomp[ind].empty ()) continue;

		l = r;

		while (r < K.size () && K[r] < val && r - l < decomp[ind].size ()) r++;

		if (r == K.size () || K[r] > val) {
			int j = 0;

			for (int i = r - 1; i >= l && j < path_end[ind]; i--) {
				a[decomp[ind][j]] = K[i];
				j++;
			}

			while (ptr < K.size () && K[ptr] < val) {
				ptr++;
			}
		}
		else {
			while (ptr < K.size () && K[ptr] < val) {
				undef[K[ptr]] = 1;
				ptr++;
			}
		}
	}

	for (int i = 0; i < n; i++)
		printf ("%d\n", (undef[a[i]] ? 0 : a[i]));
}
