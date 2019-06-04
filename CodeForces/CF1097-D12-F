#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <stdio.h>
#include <map>
//Keep data in bitsets as: a[i][j] - (number of elements in a multiset i
//that is divided be j with no remainder) mod 2. We can calculate the union with a[i] ^ a[j]
//and find the number of elements with value x by inclusion-exclusion principle.
//Number of elements divided by j in resulting multiset after query 3 (m, x, y) is a[x][j] * a[y][j]
//which has analog bitwise AND.
#include <algorithm>
#include <bitset>
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>
 
typedef long long ll;
 
const ll MOD = 1e9 + 7, INF = 1e18;
 
using namespace std;

bitset <7001> query1[7001], query4[7001], a[100001], tmp;

int n, q;

int main ()
{
	cin >> n >> q;
	for (int i = 1; i <= 7000; i++)
		for (int j = i; j <= 7000; j += i)
		{
			query4[i][j] = 1;
			for (int k = 2; k <= 7000 / k; k++)
				if ((j / i) % (k * k) == 0) query4[i][j] = 0;
			query1[j][i] = 1;
		}


		for (int i = 0; i < q; i++)
		{
			int t, x, y, v, m;

			scanf ("%d%d", &t, &m);

			if (t == 1)
			{
				scanf ("%d", &v);
				a[m] = query1[v];
			}
			else if (t == 2)
			{
				scanf ("%d%d", &x, &y);
				a[m] = a[x] ^ a[y];
			}
			else if (t == 3)
			{
				scanf ("%d%d", &x, &y);
				a[m] = a[x] & a[y];
			}
			else
			{
				scanf ("%d", &v);
				tmp = a[m] & query4[v];
				int ans = tmp.count ();
				printf ("%d", ans % 2);
			}
		}

}
