#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
//Lemma: if there are more then 2 segments with odd length, there is no solution. Let Oa be the number of odd segments in a
//and Ob the same number but in b. the number of edges in a will be (n - Oa)/2 and in b - (n - Ob)/2. We have to have at 
//least n - 1 edges to connect the graph, so (n - Oa)/2 + (n - Ob)/2 <= n - 1 -> Oa + Ob <= 2. that means Oa <= 2.
//We can create a spirale in the graph representation of segments a and b combined by making |b| = |a| - 1. If this
//model is reversed and expanded to the right, we can obtain new types of spirales. So for a = [a1,a2,a3...,an] we can
//make b = [a1-1,a2,a3,...,an+1] to get the connected row of spirales. Segment of the odd length in the middle disconnects
//the graph, so, using lemma, we can assume the number of such segments <= 2 and we can put them in the start and the end.
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

int m, n;

vector <int> v[2];

int main ()
{
	cin >> m >> n;

	for (int i = 0; i < n; i++)
	{
		int a;

		scanf ("%d", &a);

		v[a & 1].push_back (a);
	}

	if (v[1].size () > 2) cout << "Impossible";
	else 
	{
		if (v[1].size ()) cout << v[1][0] << ' ';

		for (auto a : v[0])
			printf ("%d ", a);

		if (v[1].size () > 1) cout << v[1][1];

		cout << endl;

		if (!v[0].size ())
		{
			if (v[1].size () == 1) 
			{
				if (v[1][0] == 1) printf ("1\n%d\n", v[1][0]);
				else printf ("2\n%d 1\n", v[1][0] - 1);
			}
			else 
			{
				if (v[1][0] == 1) printf ("1\n%d\n", v[1][1] + 1);
				else printf ("2\n%d %d\n", v[1][0] - 1, v[1][1] + 1);
			}	
		}
		else if (v[0].size () == 1)
		{
			if (v[1].size () == 0) printf ("2\n1 %d\n", v[0][0] - 1);
			else if (v[1].size () == 1) 
			{
				if (v[1][0] == 1) printf ("1\n%d\n", v[0][0] + 1);
				else printf ("2\n%d %d\n", v[1][0] - 1, v[0][0] + 1);
			}
			else 
			{
				if (v[1][0] == 1) printf ("2\n%d %d\n", v[0][0], v[1][1] + 1);
				else printf ("3\n%d %d %d\n", v[1][0] - 1, v[0][0], v[1][1] + 1);
			}
		}
		else
		{
			cout << n - (v[1].size () && v[1][0] == 1 ? 1 : 0) << endl;

			if (v[1].size ())
			{
				if (v[1][0] > 1) cout << v[1][0] - 1 << ' ';
				cout << v[0][0] << ' ';
			}
			else cout << v[0][0] - 1 << ' ';

			for (int i = 1; i < v[0].size () - 1; i++)
				printf ("%d ", v[0][i]);

			if (v[1].size () > 1)
			{
				cout << v[0].back () << ' ';
				cout << v[1][1] + 1 << ' ';
			}
			else cout << v[0].back () + 1 << ' ';
		}
	}
}
