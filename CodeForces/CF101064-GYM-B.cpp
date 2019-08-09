#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <bitset>
//First, we can find the number of cases where it will be equal to 3 or 4, then do n! - this number. It doesn't matter
//if we count the number with LIS or LDS, because those cases are symmetrical.
//let P be some permutation. Ai will be the set of all increasing subsequences of length i in P. ai is the minimal last
//number out of all in Ai. if the set is empty ai is 0 So the state d[i][a2][a3][a4] is the number of 
//permutations of length i with corresponding a2, a3, a4. Notice that a1 is always 1. Transition works like 
//adding a number x on the end and increasing all numbers >= x by 1 ([2,3,1,5,4] + 3 = [2,4,1,6,5,3]). Now to check how
//a2,a3,a4 changed, we have to find the minimal a that is larger and replace it with our x. 
//For example for [4,2,3,1,5] a2 = 3, a3 = 5, a4 = 0. After adding 4 we can see all a-numbers >= 4 will increment, a3 
//will become 6 and also a3 > 4 and a2 < 4, which means a3 could be replaced with 4. So we get a permutation [5,2,3,1,6,4] 
//with a2 = 3, a3 = 4, a4 = 0. If new added element is > a4 that means LIS will be > 4 so we don't have to deal with this case.
//Then count all states with a3 not equal to 0, which grants LIS >= 3 and ignoring x > a4 grants LIS <= 4.
#include <math.h>
#include <queue>
#include <stack>
#include <set>
#include <map>
 
typedef long long ll;
typedef long double ld;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;
 
ll d[61][61][61][61], n;

void add (ll& a, ll b)
{
	a += b;
	if (a >= MOD) a -= MOD;
}
 
int main ()
{
	cin >> n;

	d[1][0][0][0] = 1;

	for (int i = 2; i <= n; i++)
		for (int a = 0; a < i; a++)
			for (int b = 0; b < i; b++)
				for (int c = 0; c < i; c++)
					if (d[i-1][a][b][c])
					{
						for (int k = 1; k <= i; k++)
						{
							if (c && k > c) continue;
							else if (b && k > b) add (d[i][a][b][k], d[i-1][a][b][c]);
							else if (a && k > a) add (d[i][a][k][(c ? c + 1 : c)], d[i-1][a][b][c]);
							else if (k != 1) add (d[i][k][(b ? b + 1 : b)][(c ? c + 1 : c)], d[i-1][a][b][c]);
							else add (d[i][(a ? a + 1 : a)][(b ? b + 1 : b)][(c ? c + 1 : c)], d[i-1][a][b][c]);
						}
					}

	ll ans = 0;

	for (int a = 0; a <= n; a++)
		for (int b = 1; b <= n; b++)
			for (int c = 0; c <= n; c++)
				add (ans, d[n][a][b][c]);

	ll fact = 1;

	for (int i = 1; i <= n; i++)
		fact = (fact * i) % MOD;

	ans = (fact - ans + MOD) % MOD;
	cout << ans;
}
