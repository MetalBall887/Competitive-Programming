#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//the important part of this problem is, we can take a vertex i only as a judge or as a cat, which translates the bipartite
//graph to non-bipartite graph. If vertex x is a judge and there is an edge (x, y), vertex y must be a judge as well. That
//means, there can't be path x -> y where x is a judge and y is a cat. So if we condensate the graph (contract SCCs to 
//vertices), we should find at least one vertex that has zero in-degree. if there is only one vertex after contraction,
//there is no answer.
#include <fstream>
#include <set>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <queue>
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e15, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int st[N], n, m, tin[N], fup[N], color, off[N];
int u[N], c[N], timer;
 
vector < pair <int, int> > e;
 
vector <int> g[N], gt[N], v;
 
void dfs1 (int x) {
    u[x] = 1;
    for (int to : g[x])
        if (!u[to])
            dfs1 (to);
 
    v.push_back (x);
}
 
void dfs2 (int x) {
    c[x] = color;
    u[x] = 1;
    for (int to : gt[x])
        if (!u[to]) {
            dfs2 (to);
        }
}
 
 
int main () {
    int t;
    cin >> t;
 
    while (t--) {
        cin >> n >> m;
 
        for (int i = 0; i < n; i++) {
            st[i] = u[i] = off[i] = 0;
            g[i].clear ();
            gt[i].clear ();
        }
        timer = color = 0;
        e.clear ();
        v.clear ();
 
        for (int i = 0; i < m; i++) {
            int a, b;
 
            scanf ("%d%d", &a, &b);
            if (a == b) continue;
            e.push_back ({a - 1, b - 1});
 
            g[a-1].push_back (b - 1);
            gt[b-1].push_back (a - 1);
        }
 
        for (int i = 0; i < n; i++)
            if (!u[i]) dfs1 (i);
 
        reverse (v.begin (), v.end ());
        memset (u, 0, (n + 10) * sizeof (u[0]));
 
        for (int i : v) {
            if (!u[i]) {
                color++;
                dfs2 (i);
            }
        }
 
        if (color == 1) cout << "No\n";
        else {
            for (auto a : e) {
                if (c[a.first] != c[a.second]) {
                    off[c[a.second]] = 1;
                }
            }
 
            int nd = -1, cats = 0;
 
            for (int i = 1; i <= color; i++) {
                if (!off[i]) {
                    nd = i;
                }
            }
 
            for (int i = 0; i < n; i++) {
                if (c[i] == nd) cats++;
            }
 
            assert (nd != -1);
 
            cout << "Yes\n" << n - cats << ' ' << cats << endl;
 
            for (int i = 0; i < n; i++) {
                if (c[i] != nd) printf ("%d ", i + 1);
            }
            cout << endl;
            for (int i = 0; i < n; i++) {
                if (c[i] == nd) printf ("%d ", i + 1);
            }
            cout << endl;
        }
    }
}
