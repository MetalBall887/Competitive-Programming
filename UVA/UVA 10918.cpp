#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <map>
//Count all tilings, there aren't too many of them. Then divide by 2, since all can be viewed from the left and from the right. 
//Also before dividing we have to add all palindromes, so dividing wouldn't change the number of them
#include <map>
#include <set>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>

using namespace std;

typedef long long ll;

const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const ll N = 1e6, Z = 1e6;

int d[N], n, t;

int main () {
    n = 30;

    d[0] = 1;
    d[1] = 1;

    for (int i = 2; i <= n; i++) {
        d[i] = d[i-1] + 2 * d[i-2];
    }

    int ans = d[n];
    cin >> t;
    while (t--) {
        cin >> n;
        if (n & 1) {
            ans = (d[n] + d[n / 2]) / 2;
        } else {
            ans = (d[n] + d[n / 2] + 2 * d[(n - 1) / 2]) / 2;
        }

        cout << ans << endl;
    }
}
