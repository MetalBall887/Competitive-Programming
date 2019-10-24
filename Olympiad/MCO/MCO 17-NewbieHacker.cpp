#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <set>
//First, we have to notice some monotonicity. If some substring is good, its prefix is obviously good too. That means,
//substring in a fixed starting point l is monotoneous to r, so for each point we only need to know the longest
//good substring starting from this point. It can be done with dynamic programming. Let's for d[i] iterate the
//size of the first prefix in decomposition of this string to prefixes. Seems like it can't be more than longest
//common prefix of strings t[i..m] and s (can be precomputed with z-fucntion). Now we know where will we iterate
//and since for chosen end of the first part j the presult doesn't depend on j or i, we can store all d[j] in a 
//segment tree and answer rangle queries.
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <queue>
 
#define N 1000000
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e15, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, m, z[N], d[N];
 
string s, t;

char ch[3000000];
 
struct BIT {
	int t[N], n;

	void build (int x) {
		n = x;
		memset (t, -1, sizeof (t));
	}

	void update (int x, int d) {
		for (; x <= n; x = x | (x + 1))
			t[x] = max (t[x], d);
	}

	int get (int r) {
		int mx = -1;

		for (; r >= 0; r = (r & (r + 1)) - 1)
			mx = max (mx, t[r]);

		return mx;
	}
} dp;

void compute_z () {
    int n = s.length () + t.length () + 1, l = 0, r = -1;
    string st = s;
    st += '#';
    st += t;
 
    for (int i = 1; i < n; i++) {
    	if (st[i] != st[0]) continue;
        if (r >= i) z[i] = min (z[i-l], r - i + 1);
 
        while (i + z[i] < n && st[i + z[i]] == st[z[i]]) {
            z[i]++;
        }
 
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
 
    for (int i = 0; i < t.length (); i++) {
        z[i] = z[i + s.length () + 1];
    }
}
 
int main () {
	scanf ("%300000s%n", ch, &n);
	s = string (ch);
	scanf ("%300000s%n", ch, &m);
	t = string (ch);
 
    compute_z ();
    dp.build (t.length ());
 
    for (int i = t.length () - 1; i >= 0; i--) {
        d[i] = i + z[i] - 1;
        if (z[i] && i != t.length () - 1) {
            d[i] = max (d[i], dp.get (i + z[i]));
        }
 
        dp.update (i, d[i]);
    }
 
    int q;
 
    cin >> q;
 
    for (int i = 0; i < q; i++) {
        int l, r;
        scanf ("%d%d", &l, &r);
 
        if (d[l-1] >= r - 1) puts ("YES");
        else puts ("NO");
    }
}
