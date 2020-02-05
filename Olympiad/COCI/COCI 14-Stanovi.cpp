#include <bits/stdc++.h>
//Observation is, in any apartment distribution there will be a straight line going from one to opposite edge of the floor
//consisting of apartmant walls. That means, we can divide the floor by this line and solve both parts recursively. Also we
//have to follow which sides of the apartmant part are connected with the floor walls (i.e. have windows). 
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll dp[501][501][16], n, m, k, tr[100]; 

ll Rec (int n, int m, int bm)
{
	if ((bm & 1) && (bm & 4) == 0) bm ^= 5;
	if ((bm & 2) && (bm & 8) == 0) bm ^= 10;
	if (n > m) {
		bm = (bm >> 1) + 8 * (bm & 1);
		swap (n, m);
	}

    if (!bm)
        return INF;
    if (dp[n][m][bm] != -1)
        return dp[n][m][bm];

    ll ans = (n * m - k) * (n * m - k);
    
    for (int i = 1; i < n && (bm - (bm & 4)) && (bm - (bm & 1)); i++)
    	ans = min (ans, Rec (i, m, bm - (bm & 4)) + 
    					Rec (n - i, m, bm - (bm & 1)));

    for (int i = 1; i < m && (bm - (bm & 8)) && (bm - (bm & 2)); i++)
    	ans = min (ans, Rec (n, i, bm - (bm & 8)) + 
    					Rec (n, m - i, bm - (bm & 2)));

    return dp[n][m][bm] = ans;

}

int main () {
	cin >> n >> m >> k;
	memset (dp, -1, sizeof (dp));

	cout << Rec (n, m, 15);
}
