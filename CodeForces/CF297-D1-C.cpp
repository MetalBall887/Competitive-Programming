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
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

int sorted[1000000], s[1000000], n;

bool Comp (int i, int j)
{
	return s[i] < s[j];
}

int main ()
{
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		sorted[i] = i;
		scanf ("%d", &s[i]);
	}

	sort (sorted, sorted + n, Comp);

	vector < pair <int, int> > a, b;

	for (int i = 0; i < n / 3; i++)
	{
		a.push_back ({sorted[i], i});
		b.push_back ({sorted[i], s[sorted[i]] - i});
	}

	for (int i = n / 3; i < 2 * n / 3; i++)
	{
		b.push_back ({sorted[i], i});
		a.push_back ({sorted[i], s[sorted[i]] - i});
	}

	for (int i = 2 * n / 3; i < n; i++)
	{
		b.push_back ({sorted[i], n - i - 1});
		a.push_back ({sorted[i], s[sorted[i]] - (n - i - 1)});
	}

	sort (a.begin(), a.end());
	sort (b.begin(), b.end());

	printf ("YES\n");

	for (int i = 0; i < n; i++)
		printf ("%d ", a[i].second);

	cout << endl;

	for (int i = 0; i < n; i++)
		printf ("%d ", b[i].second);
}
