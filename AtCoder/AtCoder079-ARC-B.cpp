#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <string>
//if abs (ai - aj) < n for each i and j, no element will be decreased twice in a row, also we can split now operations in layers
//with length n. In this leayer we once decrease element by n and n-1 times increase it by 1. So after each layer all elements are
//decreased by 1. Last k % 50 operations can be processed by making exactly k % 50 elements equal to n after all full layers. Other
//elements should be very small (since distance between them must be < n, we make them n - k % 50 - 1, as after all layers there will
//be exactly k % 50 operations.
#include <bitset>
#include <math.h>
#include <queue>
#include <stack>
#include <set>
#include <map>
 
typedef long long ll;
typedef long double ld;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

ll k, n;

int main ()
{
	cin >> k;

	cout << "50\n";

	for (int i = 0; i < 50; i++)
	{
		ll x = 49;

		if (i < k % 50) x = 50;
		else x = 49 - k % 50;
		x += k / 50;

		a.push_back (x);
		cout << x << ' ';
	}

	//cout << check (a);
}
