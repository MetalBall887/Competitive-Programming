#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <bitset>
#include <math.h>
#include <queue>
#include <stack>
#include <set>
#include <map>
 
typedef long long ll;
typedef long double ld;
 
const ll MOD = 1e9 + 9, INF = 1e18 + 1;
 
using namespace std;

string s;

ll d[2][100000];

int main ()
{
	int n;

	cin >> n;

	cin >> s;

	d[0][0] = 1;

	for (int i = 1; i <= n; i++)
	{
		int k = i % 2;

		for (int j = k; j <= i; j += 2)
		{
			if (s[i-1] == '(') d[k][j] = (d[!k][j+1] + (j ? d[!k][j-1] : 0)) % MOD;
			else d[k][j] = d[!k][j+1];
		}
	}

	cout << d[n % 2][0];

}
