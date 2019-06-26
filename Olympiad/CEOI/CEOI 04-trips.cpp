#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
//Sort all groups and all trips in ascending order, then, assuming first i groups were processed, A is the set of trips
//that fit (i+1)st group and are not taken yet. Take from them the one with lowest upper bound, because with processing
//items in ascending order and adding only trips with "good" lower bound, our only oncern is upper bound, so to be 
//optimal, we always take the worst available possibility.
#include <algorithm>
#include <bitset>
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>
 
typedef long long ll;
typedef long double ld;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

multiset < pair <int, int> > s;

int a[1000000], n, m, orda[1000000], ordb[1000000];

pair <int, int> b[1000000];

vector < pair <int, int> > v;

bool compa (int i, int j)
{
	return a[i] < a[j];
}

bool compb (int i, int j)
{
	return b[i] < b[j];
}

int main ()
{
	cin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		orda[i] = i;
		scanf ("%d", &a[i]);
	}

	for (int i = 0; i < m; i++)
	{
		ordb[i] = i;
		scanf ("%d%d", &b[i].first, &b[i].second);
	}

	sort (orda, orda + n, compa);
	sort (ordb, ordb + m, compb);

	int j = 0, ans = 0;

	for (int i = 0; i < n; i++)
	{
		int x = a[orda[i]];
		while (j < m && b[ordb[j]].first <= x)
		{
			s.insert ({b[ordb[j]].second, ordb[j]});
			j++;
		}

		if (s.lower_bound ({x, -1}) != s.end ())
		{
			ans++;
			v.emplace_back (orda[i] + 1, (s.lower_bound ({x, -1}) -> second + 1));
			s.erase (s.lower_bound ({x, -1}));
		}
	}

	cout << ans << endl;

	for (auto a : v)
		printf ("%d %d\n", a.first, a.second);

}
