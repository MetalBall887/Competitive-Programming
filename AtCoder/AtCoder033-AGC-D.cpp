#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//dp[l][r][i][c] - the maximum j, so that the rectangle with left-upper point (l, i) and right-bottom point (r, j)
//will have complexity <= c. For zero it's just the biggest rectangle with the same color. for c > 0 we should consider
//horizontal and vertical division. Important note is, complexity is monotoneous, you can't decrease complexity by adding rows
//or columns as well as increase it by removing them. That means, our dp[l][r][i][c] is monotoneous as an inverted function of
//complexity function: by reducing rectangle and increasing c we can't decrease the value of the cell.
//Assume we computed the table for c-1 (we can easily ensure this by 
//computing dp in order of c ascension). Vertical division is done greedily: we can move the division line to the right as long as
//the complexity of the left subrectangle doesn't exceed c-1 (we can use our precomputed dp for c-1 here), then do the same 
//for the right subrectangle. Due to monotonicity (for the maximal j and some div-line y we can expand y to the right as far as we can
//and the right subrectangle's complexity won't increase) this works.
//Horizontal division is harder: we should notice that for x-axis borders l and r decreasing l and increasing r won't increase 
//the dp value (which is, again, maximal right border for a fixed complexity c)). Knowing this, we can for a fixed l and r and div-line x
//represent the dp value of the upper rectangle as a non-increasing function of x, of the lower one - non-decreasing function of x, so
//the maximum is the part where they intersect or the closest point to it (we should check both sides). We can keep a pointer
//to an optimal point while increasing r, since increasing r means just extending the "first" function (for an upper rectangle)
//and decreasing some of the values of the second fucntion (but never increasing) without losing the 
//monotonicity, which means "pulling down" the second function, which, again, means moving the optimal point to the right.
//Calculating the table for a fixed complexity (when all lesser are calculated) is O(H^2W) and the maximal complexity is O(logHW)
//so overall our solution works in O(H^2WlogHW).
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

string s;

int dp[190][190][190][20], last[190][190], n, m;

char c[200][200];


int main () {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		scanf ("%s", c[i]);

		for (int j = m - 1; j >= 0; j--)
		{
			if (j != m - 1 && c[i][j] == c[i][j + 1]) last[i][j] = last[i][j + 1];
			else last[i][j] = j;
		}
	}

	for (int i = 0; i < m; i++)
		for (int k = 0; k < n; k++)
			for (int j = 0; j + k < n; j++) {
				if (!k) dp[j][j][i][0] = last[j][i];
				else if (c[j][i] == c[j + 1][i]) {
					dp[j][j + k][i][0] = min (last[j][i], dp[j + 1][j + k][i][0]);
				}
				else dp[j][j + k][i][0] = -1;
			}

	for (int c = 1; c <= 16; c++) {

		for (int i = 0; i < m; i++) {
			for (int l = 0; l < n; l++)
				for (int r = l; r < n; r++) {
					if (dp[l][r][i][c-1] != m - 1) {
						dp[l][r][i][c] = dp[l][r][dp[l][r][i][c-1] + 1][c-1];
					}
					else dp[l][r][i][c] = m - 1;
				}

			for (int l = 0; l < n; l++) {
				int ptr = l;

				for (int r = l; r < n; r++) {
					for (; ptr < r - 1 && dp[l][ptr][i][c - 1] >= dp[ptr + 1][r][i][c - 1]; ptr++);

					if(l <= ptr - 1) dp[l][r][i][c] = max(dp[l][r][i][c] , min(dp[l][ptr - 1][i][c - 1] , dp[ptr][r][i][c - 1]));
					dp[l][r][i][c] = max(dp[l][r][i][c] , min(dp[l][ptr][i][c - 1] , dp[ptr + 1][r][i][c - 1]));
					if(ptr + 2 <= r) dp[l][r][i][c] = max(dp[l][r][i][c] , min(dp[l][ptr + 1][i][c - 1] , dp[ptr + 2][r][i][c - 1]));
				}
			}
		}
	}

	for (int c = 0; c <= 16; c++)
		if (dp[0][n - 1][0][c] == m - 1) {
			cout << c;
			return 0;
		}
}
