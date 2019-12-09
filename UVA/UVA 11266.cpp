#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
//d[i][j] - the number of ways to choose first i variables so that their sum is j. To optimise, use prefix sum technique.
#include <map>
#include <map>
#include <set>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>

using namespace std;

typedef long long ll;

const ll INF = 1e9, MOD = 200003, MOD2 = 1e6 + 3;
const ll N = 1e6, Z = 1e6;

ll d[2][2 * N + 2], n, a[20], b[20], s;

int main () {
    ios::sync_with_stdio (0);
    int t;

    cin >> t;

    while (t--) {
        cin >> n >> s;
        memset (d, 0, sizeof (d));
        int sm = Z, mn = Z;
        s += Z;

        for (int i = 0; i < n; i++) {
            cin >> a[i] >> b[i];
            if (b[i] > 0) sm += b[i];
            if (a[i] < 0) mn += a[i];
        }

        sm = 3 * Z / 2;
        mn = Z / 2;


        for (int i = a[0] + Z; i <= sm; i++) {
            d[0][i] = d[0][i - 1];
            if (i <= b[0] + Z) d[0][i]++;
            if (d[0][i] >= MOD) d[0][i] -= MOD;
        }

        for (int i = 1; i < n; i++) {
            int k = (i & 1);

            for (int j = mn; j <= sm; j++) {
                d[k][j] = d[!k][j - a[i]] - d[!k][j - b[i] - 1] + MOD;
                if (d[k][j] >= MOD) d[k][j] -= MOD;
                if (j > mn) d[k][j] += d[k][j-1];
                if (d[k][j] >= MOD) d[k][j] -= MOD;
            }
        }

        int k = (n - 1) & 1;

        cout << (d[k][s] - d[k][s-1] + MOD) % MOD << endl;
    }
}
