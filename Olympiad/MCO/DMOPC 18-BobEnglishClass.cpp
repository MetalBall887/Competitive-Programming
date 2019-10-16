#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
//Let's call size of a subtree the number of students inside it.
//First of all, let's prove some lemma. Sounds like this: if during pairing we got two paths A -> B and C -> D that are
//vertex-disjoint, sum of lengths of paths A -> D and C -> B will be bigger than sum of lengths of A -> B and C -> D. 
//It's easy: let's find a u and v, such that
//u is in (A -> B), v is in (C -> D) and u -> v doesn't contain any edges from those both paths. Then 
//|A -> B| = |A -> u| + |u -> B|, |C -> D| = |C -> v| + |v -> D|, so |A -> C| + |B -> D| - |A -> B| - |C -> D| = 2 * |u -> v|
//Now we know, that intersecting a pair of paths is always optimal, so each pair of paths must be intersecting. We can achieve
//that in tree by simply making all paths go through one vertex. Thing is, there aren't many vertices in tree where we can do 
//this, because every vertex, that is not centroid, divides a tree such way, one of the subtrees is bigger than the sum of the
//others, making such pairing impossible, because some of the marked nodes will have a pair from the same subtree. On the other
//hand, we always can assign pairs through centroid by sorting all marked nodes by subtrees and for each ith take (i+k/2)%kth,
//having no subtrees with sizes > k / 2 will ensure we always pair correctly. Also impoertan is, after that we don't need to
//directly assign nodes, since it will not influence the resulting sum. There may be 2 centroids, so it would be wiser to check
//them both, since we didn't prove that the outcome will be the same but it works as is.
#include <set>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll n, centr, sz[1000000], k, a[1000000];
 
vector <ll> g[1000000], dist[1000000];
 
ll dp_dfs (ll x, ll p) {
	for (ll to : g[x])
		if (to != p) {
			sz[x] += dp_dfs (to, x);
		}
 
	return sz[x];
}
 
void find_centroid (ll x, ll p) {
	ll sum = 0;
 
	bool b = true;
	for (ll to : g[x])
		if (to != p) {
			sum += sz[to];
			if (sz[to] > k / 2) b = false;
		}
 
	if (b && k - sz[x] <= k / 2) centr = x;
	else {
		for (ll to : g[x])
			if (to != p) {
				find_centroid (to, x);
			}
	}
}
 
ll dist_dp (ll x, ll p, ll dst) {
	ll sum = 0;
	for (ll i = 0; i < g[x].size (); i++) {
		ll to = g[x][i], d = dist[x][i];
		if (to != p) {
			sum += dist_dp (to, x, dst + d);
		}
	}
 
	return sum + dst * a[x];
}
 
int main () {
	cin >> k >> n;
 
	for (ll i = 0; i < k; i++) {
		ll x;
		scanf ("%lld", &x);
		x--;
 
		sz[x]++;
		a[x]++;
	}
 
	for (ll i = 0; i < n - 1; i++) {
		ll u, v, d;
 
		scanf ("%lld%lld%lld", &u, &v, &d);
 
		g[u-1].push_back (v - 1);
		dist[u-1].push_back (d);
		g[v-1].push_back (u - 1);
		dist[v-1].push_back (d);
	}
 
	dp_dfs (0, -1);
	find_centroid (0, -1);
 
	cout << dist_dp (centr, -1, 0);
}
