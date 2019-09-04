#include <iostream>
#include <vector>
#include <stdio.h>
//Important insight: if we place our elements on coordinate line, we can view the shift as changing place of one element.
//A is for changing to the left, B - to the right. Whatever the coordinates of two elements are, it's always possible to put
//another one between them. Now we can add baskets. We can put our elements in baskets without changing the order. There are
//n baskets. After all operations the element with number i should be in i-th basket. If we put in every basket one element
//we'll get a worst-case O(n) algorithm. But we can do this: |_| |_(2)_| |_(3)_| |_(1)(4)_| |_(5)_|. This way, we'll need only
//one operation, when |_(2)_| |_(3)_| |_(1)_| |_(4)_| |_(5)_| here it will be three. Also it will be more optimal to put 
//the element on the other side of corresponing box. To find the best way, we can do d[i][j] - the cost of sorting i first
//elements into first j baskets.
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7;

ll n, d[5001][5001], A, B;

int main ()
{
	cin >> n >> A >> B;

	for (ll i = 1; i <= n; i++)
	{
		ll a;

		scanf ("%lld", &a);

		for (ll j = 0; j <= n; j++)
		{
			if (j < a) d[i][j] = d[i-1][j] + A;
			else if (j == a) d[i][j] = d[i-1][j];
			else d[i][j] = d[i-1][j] + B;
			if (j) d[i][j] = min (d[i][j], d[i][j-1]);
		}
	}

	cout << d[n][n];
}
