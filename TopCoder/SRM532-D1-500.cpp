#include <bits/stdc++.h>
using namespace std;
//f[i][j][k][p] - the number of assignments of j edges between first i vertices, such that i-th vertex has degree parity
//p, other last min (i, K) vertices have parities as described in a bitmask k. To calculate this table, create a helping one
//d[i][j][nj][k][p] - the same definition, but we created edges from i only to last nj vertices (excluding i itself).
//cnt = the number of edges that can be created between any pair of vertices is O(m), so calculating it from 
//d[i][j-cnt][nj-1][new_k][(p + cnt) mod 2] is O(m), so overall solution works in O(nm^2k2^k)
 
const int N = 1e6, MOD = 1e9 + 7;

struct DengklekBuildingRoads {
	int d[30][31][8][1 << 8][2], f[30][31][1 << 8][2];
	
	void add (int& a, int b) {
		a += b;
		if (a >= MOD) a -= MOD;
	}

	int numWays (int n, int m, int K) {
		memset (d, 0, sizeof (d));
		f[0][0][0][0] = 1;

		for (int i = 1; i < n; i++) {

			for (int j = 0; j <= m; j++) {
				for (int k = 0; k < (1 << min (K, i)); k++) {
					for (int cnt = 0; cnt <= j; cnt++) {
						add (d[i][j][0][k][cnt & 1], f[i-1][j-cnt][k / 2][(cnt + k) & 1]);
					}
				}
			}

			for (int j = 0; j <= m; j++) {
				for (int k = 0; k < (1 << min (K, i)); k++) {
					for (int nj = 1; nj < min (K, i); nj++) {
						for (int cnt = 0; cnt <= j; cnt++) {
							int bm = k;
							if (cnt & 1) bm ^= (1 << nj);
							add (d[i][j][nj][k][0], d[i][j-cnt][nj-1][bm][cnt & 1]);
							add (d[i][j][nj][k][1], d[i][j-cnt][nj-1][bm][1 - (cnt & 1)]);
						}
					}
					f[i][j][k][0] = d[i][j][min (K, i) - 1][k][0];
					f[i][j][k][1] = d[i][j][min (K, i) - 1][k][1];
				}
			}
		}
		return f[n-1][m][0][0];
	}
};
