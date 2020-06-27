#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//First, let's notice that the transactions themselves don't play any role, we only need to know who lost or gained how much money. Let's say if he lost money, 
//gis delta is negtive, if he owes money, it's poisitive, otherwise 0. Since dividing one transaction isn't optimal, we can assume that everytime there is a 
//transaction at least one of the participant will get his delta to 0, so there will be at most n - 1 transactions (each vertex is a person, each edge is a 
//transaction and we always can build a tree). To make it lower, we can notice that more optimal graph is only a forest and we know that since each tree in the
//forest is independent, the sum of deltas in each components should be 0. That means, we want to divide our set of participants in the maximum number of subsets
//where the sum of delta in each subset is 0. Let d[i] be the answer for a mask i. We can for each mask traverse all submasks which will give us O(3^m) solution
//or we can for masks with non-zero delta sums define d[i] as maximal d[j] over all submasks j with sum of delta 0. This will not be a correct solution in this case
//but will help us count because for a mask b we only need to check closest masks (i.e. try only subtracting each bits) as there already is a data about all submasks.
//If delta sum of mask b is 0, then whatever the submask with zero delta sum and the best answer is, its delta sum is zero and thus the sum of all deltas not in
//this mask is also zero and it can be added as a component as well, so d[b] = d[j] + 1.
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, m, S, T, d[1 << 21], s[1 << 21], sb[1 << 21];
int del[21];
 
 
int main () {
	cin >> m >> n;
 
	for (int i = 0; i < n; i++) {
		int a, b, p;
		cin >> a >> b >> p;
		del[a] += p, del[b] -= p;
	}
 
	for (int i = 1; i < (1 << m); i++) {
		for (int j = 0; j < m; j++) {
			if ((i >> j) & 1) {
				int to = i - (1 << j);
				s[i] = s[to] + del[j];
				d[i] = max (d[i], d[to]);
			}
		}
 
		if (!s[i]) d[i]++;
	}
 
	cout << m - d[(1 << m) - 1];
}
