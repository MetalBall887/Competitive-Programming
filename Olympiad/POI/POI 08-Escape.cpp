#include <iostream>
#include <vector>
#include <stdio.h>
//d[i][j][x][p][dir] - the number of ways to get to the hideout in a rectangle with the leftmost topmost point (i, j), length
//(y-axis) x, length + width = p (rectangle is ((i, j), (i + x, j + y)) and dir = 0, 1, 2, 3 for four possible starting 
//points in corresponding rectangle (0 - from the top to (i, j), 1 - from the right to (i + x, j), 2 - from the bottom to 
//(i + x, j + y), 3 - from the left to (i, j + y)). I decided to mirror the problem so I swapped top and bottom and now car 
//turns only left. I did it because wanted him to start from (1, 1).
//We can transform this state notation back to ((x1, y1), (x2, y2)) usual type of representing rectangles (we'll see
//why it's better to do like we do). For example for direction 0 we either can make him turn left at point (x2, y1), which
//will lead to dp state ((x1, y1 + 1), (x2, y2)) and direction 1. And if we don't make him turn left at that point, that 
//means he'll do it sooner, so we can just remove last row and it will lead us to dp state ((x1, y1), (x2 - 1, y2)) with
//the same direction. So, we either drive to the next corner or remove it. Similar for other directions. Now notice that 
//when asking for past states we always ask for those whose x + y is lower just by 1, so we can "sort" the states by 
//increasing x + y (or P/2=p). That means, we keep only last two layers of our original dp state and the whole location of
//rectangle can be deduced based on the state. To check whetger the path is clear we can apply 2d prefix sum array.
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;


char s[200][200];

int c[200][200], d[101][101][101][2][4], n, m, k, fx, fy;

int get_sum (int x1, int y1, int x2, int y2) {
	int sum = c[x2][y2];

	if (x1) sum -= c[x1 - 1][y2];
	if (y1) sum -= c[x2][y1 - 1];
	if (x1 && y1) sum += c[x1 - 1][y1 - 1];

	return sum;
}

int get (int x1, int y1, int x2, int y2, int par, int dir) {
	if (x1 > x2 || y1 > y2) return 0;
	return d[x1][y1][x2 - x1][!par][dir];
}

int main () {
	cin >> n >> m >> k;
	cin >> fy >> fx;
	fy--;
	fx--;

	fx = n - 1 - fx;

	for (int i = 0; i < n; i++)
		scanf ("%s", s[i]);

	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < m; j++)
			swap (s[i][j], s[n-i-1][j]);

	c[0][0] = (s[0][0] == '*');
	for (int j = 1; j < m; j++)
		c[0][j] = c[0][j-1] + (s[0][j] == '*');

	for (int i = 1; i < n; i++) {
		c[i][0] = c[i-1][0] + (s[i][0] == '*');
		for (int j = 1; j < m; j++)
			c[i][j] = (s[i][j] == '*') + c[i-1][j] + c[i][j-1] - c[i-1][j-1];
	}

	for (int i = 0; i < 4; i++)
		d[fx][fy][0][0][i] = 1;

	for (int p = 1; p <= (n + m - 2); p++) {
		for (int x = 0; x <= p; x++) {
			int y = p - x;

			for (int i = 0; i + x < n; i++)
				for (int j = 0; j + y < m; j++) {
					int x1 = i, x2 = i + x, y1 = j, y2 = j + y;

					if (fx < x1 || x2 < fx || fy < y1 || y2 < fy) {
						for (int dr = 0; dr < 4; dr++)
							d[i][j][x][p & 1][dr] = 0;
						continue;
					}	


					d[i][j][x][p & 1][0] = get (x1, y1, x2 - 1, y2, p & 1, 0);
					d[i][j][x][p & 1][1] = get (x1, y1, x2, y2 - 1, p & 1, 1);
					d[i][j][x][p & 1][2] = get (x1 + 1, y1, x2, y2, p & 1, 2);
					d[i][j][x][p & 1][3] = get (x1, y1 + 1, x2, y2, p & 1, 3);

					if (y1 == fy && x1 <= fx && fx <= x2 && !get_sum (x1, y1, x2, y1)) d[i][j][x][p & 1][0] = 1;
					if (x2 == fx && y1 <= fy && fy <= y2 && !get_sum (x2, y1, x2, y2)) d[i][j][x][p & 1][1] = 1;
					if (y2 == fy && x1 <= fx && fx <= x2 && !get_sum (x1, y2, x2, y2)) d[i][j][x][p & 1][2] = 1;
					if (x1 == fx && y1 <= fy && fy <= y2 && !get_sum (x1, y1, x1, y2)) d[i][j][x][p & 1][3] = 1;


					if (!get_sum (x1, y1, x2, y1))
						d[i][j][x][p & 1][0] += get (x1, y1 + 1, x2, y2, p & 1, 1);

					if (!get_sum (x2, y1, x2, y2)) {
						d[i][j][x][p & 1][1] += get (x1, y1, x2 - 1, y2, p & 1, 2);
					}

					if (!get_sum (x1, y2, x2, y2))
						d[i][j][x][p & 1][2] += get (x1, y1, x2, y2 - 1, p & 1, 3);
					
					if (!get_sum (x1, y1, x1, y2))
						d[i][j][x][p & 1][3] += get (x1 + 1, y1, x2, y2, p & 1, 0);

					for (int dr = 0; dr < 4; dr++) {
						if (d[i][j][x][p & 1][dr] >= k) d[i][j][x][p & 1][dr] -= k;
					}
				}
			}
	}

	cout << d[0][0][n - 1][(n + m) & 1][0];
}
