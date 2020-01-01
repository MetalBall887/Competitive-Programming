#include <bits/stdc++.h>
//The main part of the problem is the fact Chebyshev distance (one we meet here) on a chessboard 
//is actually a Manhattan distance rotated by 45 degrees and scaled. That way, if we rotate our discrete plane, we can
//transform Chebyshev distance to Manhattan distance. Manhattan variation of problem is solved by trying every spot with
//a linear sweep algorithm

typedef long long ll;
 
const ll N = 1e6;
 
using namespace std;

ll n, dist[N];

struct point {
    ll x, y;
};

vector <point> v;
ll p[N];

int main () {
    cin >> n;

    for (ll i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        v.push_back ({x + y, x - y});
    }

    for (ll i = 0; i < n; i++)
        p[i] = i;

    sort (p, p + n, [&] (ll i, ll j) {
        return v[i].x < v[j].x;
    });

    ll sl = 0, sr = 0;
    for (ll i = 0; i < n; i++)
        sr += v[i].x;

    for (ll i = 0; i < n; i++) {
        dist[p[i]] = i * v[p[i]].x - sl + sr - (n - i) * v[p[i]].x;
        sl += v[p[i]].x;
        sr -= v[p[i]].x;
    }

    sort (p, p + n, [&] (ll i, ll j) {
        return v[i].y < v[j].y;
    });

    sl = 0, sr = 0;
    for (ll i = 0; i < n; i++)
        sr += v[i].y;

    for (ll i = 0; i < n; i++) {
        dist[p[i]] += i * v[p[i]].y - sl + sr - (n - i) * v[p[i]].y;
        sl += v[p[i]].y;
        sr -= v[p[i]].y;
    }

    cout << *min_element (dist, dist + n) / 2;
}
