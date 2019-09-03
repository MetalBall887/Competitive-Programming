#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//Let's simulate the game. We can see that if y coordinate of player 1 (or p1.y) equals to p2.y, we could imitate second player's movements 
//on x-axis (on y coordinates) while moving down to p2's position. That will lead us to the solution with |p1.x - p2.x| turns. Now if 
//player 2 is on the left he can't change side relatively player 1 because he will come to state with same y coordinates. So his best
//solution is to go as left as he can and await for unevitable defeat. Same for the mirror situation when p1.y < p2.y. So in that case
//the best choice will be the barcelone distance to either left or right bottom corner for player 1.
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7;

long double n, m;

long double barcelone (long double x, long double y, long double x2, long double y2)
{
	return max (abs (x - x2), abs (y - y2));
}

long double turn (long double x, long double y)
{
	if (x == y) return barcelone (2, x, n, y);
	else if (y < x) return barcelone (2, x, n, 1);
	else return barcelone (2, x, n, m);
}

int main ()
{
	cin >> n >> m;

	long double sum = 0;

	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
		{
			long double a = turn (max (0, i - 1), j);
			a = min (a, turn (i, j));
			a = min (a, turn (min (m, (long double) i + 1), j));
			if (n == 2 && abs (i - j) <= 1) a = 0;

			sum += (a + 1) / (m * m);
		}

	printf ("%.9Lf", sum);
}
