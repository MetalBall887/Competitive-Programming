#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <algorithm>
//d[i][j] - the maximal path if j castles are int the subtree rooted in i. if j is in this subtree, k - j are outside. If we
//always alternately pick castles inside or outside the subtree rooted in i, edge from ancestor of i to iwill be crossed
//exactly 2 * min (j, k - j + 1) times. Now for subtree rooted in i we have to distribute j castles between child subtrees.
//We do this by helping dp[i][j] - for current node the best way to destribute i castles to first j children. Also should be 
//carefully processed some cases when there is no way to assign castles to subtrees, for example whenthe size of subtree is less
//then the number of castles.
#include <vector>
#include <math.h>
#include <set>
 
using namespace std;
 
string s;
 
typedef long long ll;
 
ll d[1010][101], n, k, sz[1010];
 
vector <ll> g[1010], c[1010];
 
ll calc_dp (ll x, ll j, ll cost) {
    if (n - sz[x] < k - j + 1) return 0;
    ll s = 0;
    if (sz[x] > j) s = max (2 * min (j, k - j + 1) * cost + d[x][j], s);
    if (j && sz[x] >= j) s = max (2 * min (j, k - j + 1) * cost + d[x][j-1], s);
 
    return s;
}
 
void process (ll x) {
    vector <ll> dp[101];
 
    if (g[x].empty ()) {
        for (ll i = 0; i <= k; i++)
            d[x][i] = 0;
        return;
    }
 
    for (ll i = 0; i <= k; i++)
        dp[i].resize (g[x].size ());
 
    for (ll i = 0; i <= k; i++) {
        dp[i][0] = calc_dp (g[x][0], i, c[x][0]);
    }
 
    for (ll i = 1; i < g[x].size (); i++) {
        for (ll j = 0; j <= k; j++) {
            dp[j][i] = calc_dp (g[x][i], j, c[x][i]);
 
            for (ll f = 0; f <= j; f++)
                dp[j][i] = max (dp[j][i], calc_dp (g[x][i], f, c[x][i]) + dp[j-f][i-1]);
        }
    }
 
    for (ll i = 0; i <= k; i++)
        d[x][i] = dp[i][g[x].size () - 1];
}
 
ll dfs (ll x) {
    sz[x] = 1;
    for (ll to : g[x])
        sz[x] += dfs (to);
    process (x);
 
    return sz[x];
}
 
int main () {
    ll t;
    cin >> t;
 
    for (ll v = 1; v <= t; v++) {
        cin >> n >> k;
 
        for (ll i = 0; i <= n; i++) {
            g[i].clear ();
            c[i].clear ();
        }
 
        for (ll i = 0; i < n - 1; i++) {
            ll p, cost;
 
            scanf ("%lld%lld", &p, &cost);
 
            g[p-1].push_back (i + 1);
            c[p-1].push_back (cost);
        }
 
        dfs (0);
 
        printf ("Case %lld: %lld\n", v, d[0][k]);
    }
}
