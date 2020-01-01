#include <bits/stdc++.h>
//First, let's represent our numbers as a set of bits. Vertices have an edge between them only when bits of one number is
//a subset of a complementary set to the set of bits of the second number. Notice that it's commutative. We can represent
//a relation of inclusion of those sets of bits with a Hasse diagram. Now we have to construct a complementary oriented
//graph, where there is an path from A to B only when there is a path between A and B in an AND Graph. Basically, there is an
//edge from a number to its complement and from a set to his nearest subsets. Also we can find unwanted paths between numbers
//if one is a subset of another but we can deal with it by sorting the numbers since if one is a subset of another, it should
//be smaller.
 
typedef long long ll;
 
const ll N = 1e6;
 
using namespace std;
 
int n, m, u[5 * N], cnt, ex[5 * N];
 
vector <int> g[5 * N];
 
int dfs (int x) {
	if (u[x]) return 0;
	u[x] = 1;
	if (!u[(1 << n) - x - 1] && ex[x]) dfs ((1 << n) - x - 1);
	for (int i = 0; i < n; i++)
		if (x & (1 << i) && !u[x ^ (1 << i)]) dfs (x ^ (1 << i));
	return 1;
}
 
int main () {
	ios::sync_with_stdio (0);
	cin.tie (NULL);
	cin >> n >> m;
 
	for (int i = 0; i < m; i++) {
		int a;
		cin >> a;
		ex[a] = 1;
	}
 
	for (int i = 0; i < (1 << n); i++) {
		if (ex[i] && !u[i]) {
			dfs (i);
			cnt++;
		}
	}
 
	cout << cnt;
}
