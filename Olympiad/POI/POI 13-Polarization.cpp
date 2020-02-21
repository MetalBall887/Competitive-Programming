#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Lemma: the optimal redirection has a center vertex. Each vertex either has a path from the center or to the center.
//Proof by induction: For any vertex x without the loss of generality let's say there is a vertex x -> p[x] (where p[x] is
//a parent of x if center is the root). By induction, all vertices in any subtree of x have the same direction of edges
//relatively the center. For each subtree changing directions of all edges will not change the number of pairs with paths
//inside this subtree. On the other hand, directing edges to the center means, that each vertex will have a path to p[x].
//That means, it's optimal to redirect edges in the direction of the edge x - p[x]. Hence, all for each subtree, which root
//has a parent all edges will be directed in the same way relatively the center. For the center's subtrees we have to apply
//dynamic programming to maximize the |L|*|R| by minimizing ||L|-|R||, where L is the set of vertices x with path x -> center 
//and R is the set of vertices with a path center -> x. Usual knapsack DP will require O(N^2) time, but we may find out that 
//the number of subtrees of different sizes is O(sqrtN), so we can gather items with the same sizes to groups and divide them, 
//so there will be for the batch of items of size x to items of size x, 2x, 4x, 8x, ..., that means O(logn) items. That 
//leaves us with O(NsqrtNlogN) for each center, where we can also compensate log factor by bitsets. Lastly, notice that for 
//any non-centroid vertex there is a subtree with size >= N/2, which means that we can just take all other subtrees to oppose
//the biggest one.

using namespace __gnu_pbds;

#define N 1000001

using namespace std;

typedef long long ll;

const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

vector <int> g[N];
bitset <N + 2> dp;

int sz[N], n, pr[N];

int dfs (int x, int p) {
    sz[x] = 1;
    pr[x] = p;

    for (int to : g[x]) {
        if (to == p) continue;
        sz[x] += dfs (to, x);
    }

    return sz[x];
}

ll dfs_count (int x, int p) {
    ll sum = sz[x] - 1;
    for (int to : g[x]) {
        if (to == p) continue;
        sum += dfs_count (to, x);
    }

    return sum;
}

int knapsack (int x) {
    int p = pr[x];
    for (int to : g[x]) {
        if (to == p) continue;
        if (sz[to] >= n / 2) {
            return sz[to];
        }
    }

    if (sz[x] <= n / 2) {
        return n - sz[x];
    }

    vector <int> items (n + 2);
    vector <int> v;
    for (int to : g[x]) {
        if (to != p) items[sz[to]]++;
    }
    items[n-sz[x]]++;

    for (int x = 1; x < n; x++) {
        int b = 1;
        for (int i = 0; (1 << (i + 1)) - 1 <= items[x]; i++) {
            v.push_back ((1 << i) * x);
            b <<= 1;
        }
        if (items[x] - b + 1) {
            v.push_back (x * (items[x] - b + 1));
        }
    }

    dp.reset ();
    dp[0] = 1;
    int mn = 0, sm = 0;

    for (int a : v) {
    	dp |= (dp << a);
    }

    for (int i = 0; 2 * i < n; i++)
    	if (dp[i]) mn = i;

    return mn;
}

int main () {
    ios::sync_with_stdio (false);
    cin.tie (NULL);
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back (v);
        g[v].push_back (u);
    }

    dfs (0, -1);

    pair <int, int> ans {0, 0};
    for (int i = 0; i < n; i++) {
        int x = knapsack (i);
        if (abs (n - 2 * ans.first) > abs (n - 2 * x))
            ans = {x, i};
    }

    memset (sz, 0, sizeof (sz));
    dfs (ans.second, -1);
    cout << n - 1 << ' ';
    ll x = dfs_count (ans.second, -1) + (ll) ans.first * (n - ans.first - 1);
    cout << x << endl;
}
