#include <bits/stdc++.h>
//https://codeforces.com/blog/entry/63384

#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int l[N], u[1501], ch[N], n, k, h;
vector <int> v;
 
bool query (int a, int b, int c) {
    cout << "? " << a << ' ' << b << ' ' << c << endl;
 
    string s;
    cin >> s;
    return s == "Yes";
}
 
bool is_leaf (int x) {
    int y = (x == 1 ? n : x - 1);
    for (int i = 1; i <= n; i++) {
        if (x != i && y != i) {
            if (query (i, x, y)) return false;
        }
    }
 
    return true;
}
 
bool is_dist (int x, int y) {
    if (x == y) return false;
    int cover = 0;
    for (int i = 1; i <= n; i++) {
        if (x != i && y != i && query (x, i, y)) cover++;
    }
 
    return cover == 2 * h - 3;
}
 
void finish (int x, int y) {
    vector <int> path;
    for (int i = 0; i < n; i++) {
        if (v[i] == x || v[i] == y) continue;
        if (query (x, v[i], y)) path.push_back (v[i]);
    }
 
    vector <int> con {x, y};
 
    for (int i : path) {
        if (i == x || i == y) continue;
        for (int j = 1; j < con.size (); j++) {
            if (query (con[j-1], i, con[j])) {
                vector<int> nc;
                for (int k = 0; k < con.size (); k++) {
                    nc.push_back (con[k]);
                    if (k == j - 1) nc.push_back (i);
                }
                con = move (nc);
                break;
            }
        }
    }
 
    cout << "! " << con[con.size () / 2] << endl;
    fflush (stdout);
}
 
int main () {
    mt19937 rng(chrono::steady_clock::now ().time_since_epoch ().count ());
    cin >> n >> k;
    v.resize (n);
 
    int s = 1;
 
    while (s < n) h++, s *= k;
 
    for (int i = 0; i < n; i++)
        v[i] = i + 1;
 
    for (int i = 0; i < n; i++)
        swap (v[i], v[uniform_int_distribution<int>(0, i)(rng)]);
    int lf = 0;
    for (int i = 0; i < n; i++) {
            if (is_leaf (v[i])) {
                lf = v[i];
                break;
            }
        }
 
    for (int i = 0; i < n; i++) {
        if (lf == v[i]) continue;
        if (is_leaf (v[i]) && is_dist (lf, v[i])) {
            finish (lf, v[i]);
            return 0;
        }
    }
}
