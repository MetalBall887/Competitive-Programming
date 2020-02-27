#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//https://hsin.hr/coci/archive/2016_2017/results.php?contest=7

using namespace __gnu_pbds;

#define N 1000001

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n, m;
ll pf[N], ans[N], pw[N], s[N];

int main () {
	cin >> n;
	cin >> m;

    pw[0] = 1;

    for (int i = 1; i <= m; i++)
        pw[i] = n * pw[i-1] % MOD;

	for (int i = 0; i < m; i++) {
		cin >> s[i];
	}

	for (int i = 1; i < m; i++) {
		int j = pf[i-1];
		while (j > 0 && s[j] != s[i])
			j = pf[j-1];
		if (s[i] == s[j]) j++;
		pf[i] = j;
	}

    ans[0] = n;
    cout << ans[0] << '\n';
    for (int i = 1; i < m; i++) {
        ans[i] = pw[i+1] + (pf[i] ? ans[pf[i]-1] : 0);
		ans[i] %= MOD;
        cout << ans[i] << '\n';
    }
}
