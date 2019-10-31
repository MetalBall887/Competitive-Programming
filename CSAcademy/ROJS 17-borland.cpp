#include <iostream>
#include <vector>
#include <stdio.h>
//First, we define the way we can look on elements in this sequence. We can keep some pointer on the array and move it by 1 to 
//the left or to the right. The easiest solution that comes in mind is for to iterate left and right end of the contiguous 
//subsequence and keep the maximal on it. This solution is similar: we take some anchor element and solve a problem on a given
//subsequence relatively this anchor. But instead of picking the leftmost element as an anchor, we pick the middle one. 
//for f(l, r) we assume mid to be in the middle and find the needed values for subsequences with a <= l <= mid and mid < r <= b
//This can be done with two pointers algorithm: for each l we find the rightmost r so that the maximum lies in the left part.
//Same for the right side, but you should be careful not to count segments with several maximums more than once. For example,
//if maximal is at the left, right pointer can't go further if the next element is equal to maximum, but can if we keep
//maximum at the right.
#include <algorithm>
#include <fstream>
#include <set>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <queue>

#define N 1000000

using namespace std;

typedef long long ll;

const ll INF = 1e15, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll a, b, s, n, c, inv;

ll qpow (ll a, ll b) {
    ll s = 1;

    while (b) {
        if (b & 1) s = s * a % c;
        a = a * a % c;
        b >>= 1;
    }

    return s;
}

ll succ (ll v) {
    return (a * v + b) % c;
}

ll prec (ll v) {
    return (inv * (v - b + c)) % c;
}

ll f (int a, int b, int st) {
    if (a == b) return st;

    int mid = (a + b) / 2;

    ll sum = 0, cur = st;

    for (int i = a; i < mid; i++) {
        cur = succ (cur);
    }

    ll l_ptr = cur, r_ptr = succ (cur), mx = succ (cur), ind = mid;
    for (int i = mid + 1; i <= b; i++) {
        while (ind >= a && l_ptr <= mx) {
            ind--;
            l_ptr = prec (l_ptr);
        }

        ind++;
        l_ptr = succ (l_ptr);

        sum += mx * (mid + 1 - ind) % MOD;
        if (sum >= MOD) sum -= MOD;
        r_ptr = succ (r_ptr);
        mx = max (mx, r_ptr);
    }

    l_ptr = cur, r_ptr = succ (cur), mx = cur, ind = mid + 1;
    for (int i = mid; i >= a; i--) {
        if (ind == mid) {
            r_ptr = succ (cur);
            ind++;
        }
        while (ind <= b && r_ptr < mx) {
            ind++;
            r_ptr = succ (r_ptr);
        }

        ind--;
        r_ptr = prec (r_ptr);

        sum += mx * (ind - mid) % MOD;
        if (sum >= MOD) sum -= MOD;
        l_ptr = prec (l_ptr);
        mx = max (mx, l_ptr);
    }

    sum = (sum + f (a, mid, st) + f (mid + 1, b, succ (cur))) % MOD;
    return sum;
}

int main () {
    int t = 1;
    cin >> n >> s >> a >> b >> c;

    inv = qpow (a, c - 2);
    cout << f (0, n - 1, s) << endl;

    return 0;
}
