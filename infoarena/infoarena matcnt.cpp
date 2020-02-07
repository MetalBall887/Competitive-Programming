#include <bits/stdc++.h>
//Let's represent the table as a bipartite graph, where there is an edge between ri and cj if there is 1 in cell (i, j).
//In this graph every ri and every cj have degree exactly 2, also, since there are no rectangles, there are no 4-length cycles
//in the graph. That means, that is a set of disjoint even-length cycles larger than 4. We can generate those graphs by two
//operations: create a new 6-length cycle, where one col vertex is fixed to j + 3 and two other taken from [1;j+2], so it's
//(j+1)(j+2)/2 ways. The second operation is taking one column vertex (cj), take one of its edges and perform such division: 
//r1 - c1 => r1 - c2 - r2 - c1. Again, we assume the way to choose the edge to divide is one, because yet we percieve row 
//vertices as distinguishable and already enumerated in some way, so we don't want any pair of generated graphs differ only
//by the enumaration of row vertices. Later we'll multiply the answer by n!, because there are n! ways to enumerate row 
//vertices.


#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll d[N], n;
 
 
int main () {
	freopen ("matcnt.in", "r", stdin);
	freopen ("matcnt.out", "w", stdout);
	cin >> n;
 
	d[3] = 1;
 
	for (ll i = 4; i <= n; i++) {
		d[i] = (i - 1) * d[i-1] % 200003;
		d[i] = (d[i] + d[i-3] * (i - 2) * (i - 1) / 2 % 200003) % 200003;
	}
 
	for (ll i = 1; i <= n; i++) {
		d[n] *= i;
		d[n] %= 200003;
	}
 
	cout << d[n];
}
