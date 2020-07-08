#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let d[i][j][l][r] be the number of ways to connect vertices i..j assuming vertices i and j are already interconnected and there are edges from vertex i to 
//vertices i+1..j-1 only if l = 1, same for r and vertex j. Let's first try to count d[i][j][1][0]. It means there are no edges going from j inside the
//interval, so there should be some from i. Let x be the rightmost of them. Then d[i][j][1][0] += d[i][x][1][1] * d[x][j][1][0] for each x between i and j. Same
//for d[i][j][0][1]. For d[i][j][1][1] we should consider two possibilities: there are edges from i to i+1..j-1 or there aren't. If there are, iterate the rightmost
//of them as x and d[i][j][1][1] += d[i][x][1][1] * d[x][j][1][1] (for x..j no edges will cross line x-j, so there will be no edges from i to any vertex x+1..j)
//If there aren't, then it's the case d[i][j][0][1]. To obtain the result take the first vertex and iterate the rightmost edge going out of it (n+1'th vertex
//is actually the first one, since the polygon is cyclic, we can do it)
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll d[501][501][2][2];

int a[501][501], n;
ll ans[501];

int main () {
	cin >> n;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> a[i][j];

	for (int i = 0; i < n; i++)
		a[n][i] = a[i][n] = a[i][0];

	for (int i = 0; i < n; i++) {
		for (int l = 0; l < 2; l++)
			for (int r = 0; r < 2; r++)
				d[i][i+1][l][r] = 1;
	}

	for (int k = 2; k <= n; k++)
		for (int i = 0; i + k <= n; i++) {

			for (int j = i + 1; j < i + k; j++) {
				if (a[i][j]) {
					d[i][i+k][1][0] += d[i][j][1][1] * d[j][i+k][1][0] % MOD;
					d[i][i+k][1][1] += d[i][j][1][1] * d[j][i+k][1][1] % MOD;
				}
				if (a[j][i+k]) {
					d[i][i+k][0][1] += d[i][j][0][1] * d[j][i+k][1][1] % MOD;
				}
			}

			d[i][i+k][1][1] += d[i][i+k][0][1];

			for (int l = 0; l < 2; l++)
				for (int r = 0; r < 2; r++)
					d[i][i+k][l][r] %= MOD;
		}

		ll sum = 0;

		for (int i = 1; i < n; i++) {
			if (!a[0][i]) continue;

			sum += d[0][i][1][1] * d[i][n][1][0] % MOD;
		}

		cout << sum % MOD;
}
