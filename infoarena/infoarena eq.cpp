#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <set>
//This problem is fully D&C. For each yt on the segment it should be xt + max on [t;r] - min on [t;r]. Identical for zt.
//The most important part is, xt must always be the leftmost of all of them, so taking two maximums and one minimum won't work
//The values of the node is minimal and maximal elements and two arrays of size 4, for y and z
//y[00] - maximal for only the leftmost component, y[01] for leftmost + positive component, y[10] for leftmost + negative
//component, y[11] - for all three components combined. Now we can see that, when merging, we either have leftmost component
//on the left side and another on the right or we already have a precomputed intermediate value in the left half that holds
//the order rule by induction.
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <queue>

#define N 1000000

using namespace std;

typedef long long ll;

const ll INF = 1e15, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int start = 1, n, m;

struct SegTree {
    struct tr {
        ll mn, mx, y[4], z[4];

        tr () {
            mn = INF, mx = -INF;
            for (int i = 0; i < 4; i++) {
                y[i] = mx;
                z[i] = mn;
            }
        }

        tr (int x) {
            mn = mx = x;
            y[0] = z[0] = x;
            y[1] = z[1] = 2 * x;
            y[2] = z[2] = 0;
            y[3] = z[3] = x;
        }
    } t[600000];

    void merge (tr& c, tr a, tr b) {
        c.mn = min (a.mn, b.mn), c.mx = max (a.mx, b.mx);
        c.y[0] = c.mx;

        c.y[1] = max (max (a.y[1], b.y[1]), a.y[0] + b.mx);
        c.y[2] = max (max (a.y[2], b.y[2]), a.y[0] - b.mn);

        c.y[3] = max (a.y[3], b.y[3]);
        c.y[3] = max (c.y[3], a.y[0] - b.mn + b.mx);
        c.y[3] = max (c.y[3], max (a.y[1] - b.mn, a.y[2] + b.mx));

        c.z[0] = c.mn;

        c.z[1] = min (min (a.z[1], b.z[1]), a.z[0] + b.mn);
        c.z[2] = min (min (a.z[2], b.z[2]), a.z[0] - b.mx);

        c.z[3] = min (a.z[3], b.z[3]);
        c.z[3] = min (c.z[3], a.z[0] - b.mx + b.mn);
        c.z[3] = min (c.z[3], min (a.z[1] - b.mx, a.z[2] + b.mn));
    }

    void build (vector <ll>& v) {
        while (start < v.size ()) start <<= 1;

        for (int i = 0; i < v.size (); i++) {
            t[i + start] = tr (v[i]);
        }

        for (int i = start - 1; i; i--) {
            merge (t[i], t[2 * i], t[2 * i + 1]);
        }
    }

    tr get (int node, int t_l, int t_r, int l, int r) {
        tr c;

        if (r < t_l || t_r < l) return c;

        if (l <= t_l && t_r <= r) return t[node];

        int tm = (t_l + t_r) / 2;

        merge (c, get (2 * node, t_l, tm, l, r), get (2 * node + 1, tm + 1, t_r, l, r));

        return c;
    }
} t;

int main () {
    ifstream fin ("eq.in");
    ofstream fout ("eq.out");

    fin >> n >> m;

    vector <ll> v (n);

    for (int i = 0; i < n; i++) {
        fin >> v[i];
    }

    t.build (v);

    for (int i = 0; i < m; i++) {
        ll l, r, mn = INF, mx = -INF;
        fin >> l >> r;
        l--, r--;

        auto a = t.get (1, 0, start - 1, l, r);
        ll sum = a.y[3] + a.z[3];

        fout << sum << '\n';
    }
}
