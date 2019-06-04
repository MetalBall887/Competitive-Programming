#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <stdio.h>
//d[i][j][k][x] - number of correct sequences out of i B's, j R's, k S's that can't start from x
//After calculating dp, descend from the state (B, R, S) and skip first characters if the number of sequences
//starting from them is lower than k (substracting this number from k)
#include <map>
#include <algorithm>
#include <bitset>
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>
 
typedef long long ll;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

ll d[201][201][201][3], B, R, S;
bool u[201][201][201][3];

ll Rec (int i, int j, int k, int x)
{
	if (i == -1 || j == -1 || k == -1) return 0;
	if (!i && !j && !k) return 1;

	if (u[i][j][k][x]) return d[i][j][k][x];
	u[i][j][k][x] = 1;

	ll& f = d[i][j][k][x];

	if (x == 0) f = Rec (i, j - 1, k, 1) + Rec (i, j, k - 1, 2);
	if (x == 1) f = Rec (i - 1, j, k, 0) + Rec (i, j, k - 1, 2);
	if (x == 2) f = Rec (i - 1, j, k, 0) + Rec (i, j - 1, k, 1);

	f = min (f, INF);

	return f;
}

int main ()
{
	ll k;

	cin >> B >> R >> S >> k;

	Rec (B - 1, R, S, 0);
	Rec (B, R - 1, S, 1);
	Rec (B, R, S - 1, 2);

	string s;

	int x = B, y = R, z = S, last = -1;

	d[0][0][0][0] = 1;
	d[0][0][0][1] = 1;
	d[0][0][0][2] = 1;

	if (d[B-1][R][S][0] + d[B][R-1][S][1] + d[B][R][S-1][2] < k)
	{
		cout << "None";
		return 0;
	}

	while (x || y || z)
	{
		if (last != 0 && x && d[x-1][y][z][0] >= k)
    {
			x--;
			last = 0;
			s += 'B';
		}
		else 
		{
			k -= (x && last != 0 ? d[x-1][y][z][0] : 0);
			if (last != 1 && y && d[x][y-1][z][1] >= k)
			{
				y--;
				last = 1;
				s += 'R';
			}
			else
			{
				k -= (y && last != 1 ? d[x][y-1][z][1] : 0);
				z--;
				last = 2;
				s += 'S';
			}
		}
	}

	cout << s;
}
