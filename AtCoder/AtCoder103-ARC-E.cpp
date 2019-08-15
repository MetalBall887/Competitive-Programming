#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
//first of all, s1 != 0 and sn != 1. Next, si = s(n-i). Now, go through the string. suppose we have a root of our unfinished
//tree x. If si = 0, we hang a new vertex to our root, if si = 1, we create a new root and hang x to it.
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

vector <int> g[1000000];

string s;

int n;

int main ()
{
	cin >> s;

	n = s.length ();

	s = '0' + s;

	for (int i = 0; i <= n; i++)
		if (s[i] != s[n - i])
		{
			cout << "-1";
			return 0;
		}

	if (s[1] == '0')
	{
		cout << "-1";
		return 0;
	}

	int x = 1, ptr = 1;

	for (int i = 1; i < n; i++)
	{
		g[x].push_back (++ptr);

		if (s[i] == '1') x = ptr;
	}

	for (int i = 0; i <= ptr; i++)
		for (int a : g[i])
			printf ("%d %d\n", i, a);
}
