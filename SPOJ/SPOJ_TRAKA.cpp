#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
//First, let's divide time spent into two groups. In first group Mirko works, in second Mirko waits. Since 
//it's easier to calculate the first part, let's concentrate on the second one. let a_i be the time when 
//the car with f = 1 moves out of the i-th worker's place if it moves out of first one's in time 0. b_i will be the
//same: the time when the i-th coworker gets the car with f = 1. So when Mirko gets the j-th car, if there is a such i
//a_i * f_j-1 - b_i * f_j > 0, Mirko will have to wait this amount of time. So out of i he has to take the maximal
//c = a_i * f_j-1 - b_i * f_j and wait this time. but since on step j f_j is constant for each i, we can divide all such
//equations on f_j and get maximal c/f_j = a_i * f_j-1/f_j - b_i, and this i will be maximum in our original set of lines too.
//so we can for each i contain a line of type g_i(x) = a_i * x + b_i and for each car to find waiting time we have to find
//max i g_i(f_j/f_j-1) which is possible with Convex Hull Trick.
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
 
int n, m, ptr;
 
ld t[1000000], f[100000], p;
 
struct line
{
	ld k, b;
 
	bool operator < (const line& a)
	{
		return (k == a.k ? b < a.b : k < a.k);
	}
};
 
vector <line> lines, cht;
 
ld intersect (line a, line b)
{
	return (a.b - b.b) / (b.k - a.k);
}
 
ld eval (line a, ld x)
{
	return a.k * x + a.b;
}
 
ld find_max (ld x)
{
	if (ptr == 1 || x <= intersect (cht[0], cht[1])) return eval (cht[0], x);

	int l = 0, r = ptr - 2;

	while (l < r)
	{
		int mid = (l + r + 1) / 2;

		if (intersect (cht[mid], cht[mid + 1]) <= x) l = mid;
		else r = mid - 1;
	}

	return eval (cht[l + 1], x);
}

int main ()
{
	cin >> n >> m;
 
	for (int i = 0; i < n; i++)
	{
		scanf ("%Lf", &t[i]);
		p += t[i];
		lines.push_back ({p - t[0], -(p - t[i])});
	}
 
	for (line l : lines)
	{
		while (ptr >= 2 && intersect (cht[ptr-2], l) <= intersect (cht[ptr-2], cht[ptr-1]))
		{
			cht.pop_back ();
			ptr--;
		}
		cht.push_back (l);
		ptr++;
	}
 
	for (int i = 0; i < m; i++)
		scanf ("%Lf", &f[i]);
 
	ld timer = 0;
 
	for (int i = 0; i < m; i++)
	{
		if (i) timer += max (find_max (f[i-1] / f[i]) * f[i], (long double) 0.0);
		timer += t[0] * f[i];
	}
 
	timer += (p - t[0]) * f[m-1];
 
	cout << (long long) timer << endl;
}   
