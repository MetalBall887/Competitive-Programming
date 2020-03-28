#include <bits/stdc++.h>
//The problem is essentialy a weighted LIS on the tree. LIS on the sequence can be solved by d[i] = the maximum weight of
//the increasing subsequence ending in i, there are O(n) updates on d[] and each can be performed in O(logn). For a tree 
//version we can do the similar dp table d[i] - the maximum weight of the sequence tree ending in i in the current subtree.
//For a subtree we first sum all tables of all his children and optimize the answer in some positions by the value in the 
//of the subtree. This can be done with static arrays O(nk) or note that the number of changes in the table is O(sz of the 
//subtree), so we can store arrays dynamically with balanced treed and aleays sum the smaller array to the bigger for 
//getting O(nlog^2n). Good trick is observing that the array is non-decreasing and instead of values themselves keeping
//differences between them.
 
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
map <ll, ll> mp[N];
map <ll, ll>* it[N];
ll p[N], sz[N], d[N], w[N], v[N];
ll n, m;
 
vector <int> g[N];
 
ll find (ll x) {
    if (x == p[x]) return x;
    return p[x] = find (p[x]);
}
 
void merge (ll a, ll b) {
    a = find (a), b = find (b);
    if (a == b) return;
 
    if (sz[a] < sz[b]) swap (a, b);
 
    for (auto x : *it[b]) {
        (*it[a])[x.first] += x.second;
    }
 
    p[b] = a;
    sz[a] += sz[b];
}
 
void dfs (ll x, ll par) {
    for (ll to : g[x]) {
        if (to == par) continue;
        dfs (to, x);
        merge (x, to);
    }
 
    map <ll, ll>& here = *it[find (x)];
 
    if (v[x] != -1) {
        auto mx = here.upper_bound (d[v[x]]);
 
        ll val = w[v[x]];
 
        while (mx != here.end () && val > 0) {
            auto pr = mx;
            mx++;
            if (val > pr -> second) {
                val -= pr -> second;
                here.erase (pr);
            } else {
                pr -> second -= val;
                break;
            }
        }
 
        here[d[v[x]]] += w[v[x]];
    }
}
 
int main () {
	ll k;
    cin >> n >> m >> k;
 
    memset (v, -1, sizeof (v));
 
    for (ll i = 1; i < n; i++) {
        ll p;
        cin >> p;
        g[p-1].push_back (i);
    }
 
    for (ll i = 0; i < n; i++) {
        p[i] = i, sz[i] = 1;
        it[i] = &mp[i];
    }
 
    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
 
        v[a-1] = i;
        d[i] = b;
        w[i] = c;
    }
 
    dfs (0, -1);
 
    map <ll, ll>& here = *it[find (0)];
 
    ll ans = 0;
 
    for (auto a : here)
        ans += a.second;
 
    cout << ans;
}
