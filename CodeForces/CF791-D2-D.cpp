#include <bits/stdc++.h>
//the sum of lengths between all paths can be found by finding this sum for paths for which LCA is some fixed x. It can be
//done by first precomputing d[x] - sum of lengths of all descending (LCA is the upper endpoint) paths for which the upper 
//endpoint is x. For any u - child of x count the number of paths originated from x but not going to the current child and 
//add d[u] this number of times to the original sum, but need to be cautious of repetitions. Now with the same trick we can
//found for each i from 0 to k - 1 the number of paths with remainders of division by k equal to i. Then for each path with
//remainder i we can add (k - i) to round the division by k up.
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
vector <int> g[N];
 
ll d[N], sum, dc[N][5], sz[N], cnt[N], cm[5], k;
int n;
 
void add (ll& a, ll b) {
    a += b;
}
 
int dfs (int x, int p) {
    sz[x] = 1;
    dc[x][0] = 1;
    cnt[x] = 1;
    for (int to : g[x]) {
        if (to != p) {
            sz[x] += dfs (to, x);
            add (d[x], d[to] + cnt[to]);
            add (cnt[x], cnt[to]);
            for (int j = 0; j < k; j++) {
                add (dc[x][j], dc[to][j ? j - 1 : k - 1]);
            }
        }
    }
 
 
    ll pf[5] = {1, 0, 0, 0, 0};
    for (int to : g[x]) {
        if (to != p) {
            add  (sum, (cnt[x] - cnt[to]) * (d[to] + cnt[to]));
            for (int a = 0; a < k; a++) {
                for (int b = 0; b < k; b++) {
                    ll s = pf[a] * dc[to][b ? b - 1 : k - 1];
                    add (cm[(a + b) % k], s);
                }
                add (pf[a], dc[to][a ? a - 1 : k - 1]);
            }
        }
    }
 
    return sz[x];
}
 
int main () {
    cin >> n >> k;
 
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u-1].push_back (v - 1);
        g[v-1].push_back (u - 1);
    }
 
    dfs (0, -1);
 
    for (int i = 1; i < k; i++) {
        add (sum, (k - i) * cm[i]);
    }
 
    cout << sum / k;
}
