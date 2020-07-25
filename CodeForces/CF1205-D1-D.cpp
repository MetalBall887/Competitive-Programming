#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//First, notice that if there is a set of numbers of size O(n), you can assign weights on edges such way each element from the set will appear as a path from the
//root to some other vertex. So not only we have a way to place O(n) numbers, but every such path will start at any vertex we choose as a root. So let's find a vertex
//and divide its subtrees into two groups and each group will be treated as a tree with the root in the found vertex. Now apply our O(n) assignment for each of 
//our trees: is the sizes of trees are A and B, in the first tree place values B, 2B, 3B, ..., (A-1)B and in the second tree 1, 2, 3, ..., B-1, so for each 
//value < AB it will be represented as xB + y, xB part will be a path from vertex in the first tree to the root, y part - from the root to vertex in the second
//tree, we "merge" them and get the path with needed sum. Now to maximize AB we need A and B the closest to each other, since A + B = n - 1. If we take the root
//as a centroid of the "full" tree, we can ensure that there are no subtrees with size > n / 2. Now sort all subtrees in ascending order, let a[i] be i-th of them
//p[i] - sum of a[0] to a[i], s[i] - sum of a[i] to the last. Now find such j that p[j-1] < s[j] and p[j] >= s[j+1]. Since p[j-1] < s[j] a[j..last] should consist 
//of at least 2 elements, otherwise there will be a big subtree. Also a[j] <= s[j+1]. 
//Now if p[j-1] >= s[j+1], s[j] = s[j+1] + a[j] <= 2*s[j+1] <= 2*p[j-1]       ->       p[j-1] <= s[j] <= 2*p[j-1]
//if p[j-1] <= s[j+1], p[j] = p[j-1] + a[j] <= s[j+1] + a[j] <= 2 * s[j+1]    ->       s[j+1] <= p[j] <= 2*s[j+1]
//That means, there is always a way to divide subtrees in two groups that way that any of groups is at most twice bigger than the other. Therefore, we are
//Therefore, we are guaranteed to divide the tree into at least A = n/3 and B = 2n/3 half-trees. The AB we wanted to maximize will be n/3 * 2n/3 = 2n^2/9.

using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int sz[N], n, ptr = 1, iter = 1;
 
vector <array<int, 3>> ans;
 
vector <int> g[N];
 
int calc_size (int x, int p) {
	sz[x] = 1;
 
	for (int to : g[x])
		if (to != p) sz[x] += calc_size (to, x);
 
	return sz[x];
}
 
int find_centroid (int x, int p) {
	for (int to : g[x]) {
		if (to != p && sz[to] > n / 2) {
			return find_centroid (to, x);
		}
	}
	return x;
}
 
void dfs (int x, int p, int sum) {
	int d = ptr;
	cout << x + 1 << ' ' << p + 1 << ' ' << ptr - sum << '\n';
	ptr += iter;
 
	for (int to : g[x])
		if (to != p) dfs (to, x, d);
}
 
int main () {
	cin >> n;
 
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].push_back (b);
		g[b].push_back (a);
	}
 
	calc_size (0, -1);
	int c = find_centroid (0, -1);
	calc_size (c, -1);
 
	vector < pair <int, int> > v;
 
	for (int to : g[c])
		v.push_back ({sz[to], to});
 
	sort (v.begin(), v.end());
 
	int sum = 0, dif = n;
 
	for (auto x : v) {
		sum += x.first;
		dif = min (dif, abs (n - 2 * sum));
	}
 
	sum = 0;
 
	for (auto x : v) {
		sum += x.first;
		int a = sum, b = n - sum;
		if (a > b) swap (a, b);
		dfs (x.second, c, 0);
		if (abs (n - 2 * sum) == dif) iter = ptr;
	}
}
