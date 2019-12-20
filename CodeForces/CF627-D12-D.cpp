#include <bits/stdc++.h>
//The idea is generic: when you have to find some maximum, binary search will often fit. while checking if minimum >= x, I changed all
//values < x to 0 ant all values >= x to 1. Then applied dynamic programming on trees with rerooting. Main idea of it is, when
//finding the longest dfs path without zeroes, you first go to subtrees that don't have 0 in it, then out of the remaining ones, 
//recursively find one with the maximal length of dfs-path.


using namespace std;

typedef long long ll;

const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const ll N = 1e6, Z = 1e6;

struct bunch {
    int ex, cl, end;

    bunch up () {
        if (ex) return {1, 0, cl + end};
        else return *this;
    }
};

vector <int> g[N];

int a[N], z[N], k, ans, n;
bunch d[N];
bitset <N> u;

bunch merge (bunch a, bunch b) {
    bunch s;

    s.cl = a.cl + b.cl;
    s.end = max (a.end, b.end);
    s.ex = a.ex || b.ex;

    return s;
}

bunch dfs (int x, int p) {
    u[x] = 1;
    if (!z[x]) return d[x] = {1, 0, 0};
    bunch v {0, 0, 0};
    for (int to : g[x])
        if (to != p) {
            v = merge (v, dfs (to, x));
        }

    v.cl++;
    return d[x] = v.up ();
}

void dfs2 (int x, int p, bunch c) {
    if (!z[x]) return;
    bunch nl {0, 0, 0};
    u[x] = 1;
    int m = g[x].size ();

    vector <bunch> pr (m), sf (m);
    if (g[x][0] != p) pr[0] = d[g[x][0]];
    else pr[0] = nl;
    if (g[x].back () != p) sf[m - 1] = d[g[x].back ()];
    else sf[m-1] = nl;

    for (int i = 1; i < m; i++) {
        int to = g[x][i];
        if (to != p) pr[i] = merge (pr[i-1], d[to]);
        else pr[i] = pr[i-1];
    }

    for (int i = m - 2; i >= 0; i--) {
        int to = g[x][i];
        if (to != p) sf[i] = merge (sf[i+1], d[to]);
        else sf[i] = sf[i+1];
    }
    auto b = merge (sf[0], c);
    ans = max (ans, 1 + b.cl + b.end);
    for (int i = 0; i < m; i++) {
        int to = g[x][i];
        if (to == p) continue;
        bunch pref = (i ? pr[i-1] : nl);
        bunch suff = (i < m - 1 ? sf[i+1] : nl);
        auto new_c = merge (c, merge (pref, suff));
        new_c.cl++;
        dfs2 (to, x, new_c.up ());
    }
}


int main () {
    ios::sync_with_stdio (false);
    cin.tie (NULL);
    cin >> n >> k;

    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u-1].push_back (v - 1);
        g[v-1].push_back (u - 1);
    }

    int l = 0, r = 1e6 + 10;

    while (l < r) {
        ans = 0;
        int mid = (l + r + 1) / 2;

        for (int i = 0; i < n; i++) {
            if (a[i] >= mid) z[i] = 1;
            else z[i] = 0;
        }

        u.reset ();

        for (int i = 0; i < n; i++) {
            if (!u[i]) dfs (i, -1);
        }

        u.reset ();

        for (int i = 0; i < n; i++) {
            if (!u[i]) dfs2 (i, -1, {0, 0, 0});
        }
        if (ans >= k) l = mid;
        else r = mid - 1;
    }

    cout << l << endl;
}
