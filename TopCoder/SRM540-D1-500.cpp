#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
//pretty straightforward dp solution d[i][r][g][b] - probability that you will paint a first i planks of fence
//with red = r, green = g, blue = b. For each state we update the future states with offline prefix sum array.
//Should be implemented with care, by the inclusion-exclusion principle. We can define for each present state
//the set of future states that will be changed by current stage with inclusion-exclusion too 
//but it will actually depict a cube with center (r, g, b) and side 2 * d2 (states with all dimensions 
//not further to x than d2) without a cube with same center and side 2 * (d1 - 1) 
//(states with all dimensions closer to x than d1)
#include <map>
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

class RandomColoring
{
public:

	double p[41][51][51][51];

	void add (int k, int x2, int y2, int z2, int x1, int y1, int z1, double d)
	{
		p[k][x1][y1][z1] += d;
		p[k][x2 + 1][y1][z1] -= d;
		p[k][x1][y2 + 1][z1] -= d;
		p[k][x1][y1][z2 + 1] -= d;
		p[k][x2 + 1][y2 + 1][z1] += d;
		p[k][x1][y2 + 1][z2 + 1] += d;
		p[k][x2 + 1][y1][z2 + 1] += d;
		p[k][x2 + 1][y2 + 1][z2 + 1] -= d;
	}

	double ds (double r, double x, double d)
	{
		if (d < 0) return 0;
		return min (r - 1, x + d) - max (0.0, x - d) + 1.0;
	}

	void calc (int k, int r, int g, int b)
	{
		if (r) p[k][r][g][b] += p[k][r-1][g][b];
		if (g) p[k][r][g][b] += p[k][r][g-1][b];
		if (b) p[k][r][g][b] += p[k][r][g][b-1];

		if (r && g) p[k][r][g][b] -= p[k][r-1][g-1][b];
		if (r && b) p[k][r][g][b] -= p[k][r-1][g][b-1];
		if (g && b) p[k][r][g][b] -= p[k][r][g-1][b-1];

		if (r && g && b) p[k][r][g][b] += p[k][r-1][g-1][b-1];
	}

	double getProbability (int N, int maxR, int maxG, int maxB, int startR, int startG, int startB, int d1, int d2)
	{
		p[0][startR][startG][startB] = 1.0;

		for (int i = 0; i < N - 1; i++)
		{
			for (int r = 0; r < maxR; r++)
				for (int g = 0; g < maxG; g++)
					for (int b = 0; b < maxB; b++)
					{
						if (i) calc (i, r, g, b);
						 

						double limR = ds (maxR, r, d2);
						double lim2R = ds (maxR, r, d1 - 1);

						double limG = ds (maxG, g, d2);
						double lim2G = ds (maxG, g, d1 - 1);

						double limB = ds (maxB, b, d2);
						double lim2B = ds (maxB, b, d1 - 1);

						
						if (limR * limG * limB == lim2R * lim2G * lim2B) continue;
						
						double new_d = p[i][r][g][b] / (limR * limG * limB - lim2R * lim2G * lim2B);

						add (i + 1, min (maxR - 1, r + d2), min (maxG - 1, g + d2), min (maxB - 1, b + d2), 
							 max (0, r - d2), max (0, g - d2), max (0, b - d2), new_d);
						if (d1)
							add (i + 1, min (maxR - 1, r + d1 - 1), min (maxG - 1, g + d1 - 1), min (maxB - 1, b + d1 - 1), 
							max (0, r - d1 + 1), max (0, g - d1 + 1), max (0, b - d1 + 1), -new_d);
					}
		}

		double ans = 0;

		for (int r = 0; r < maxR; r++)
			for (int g = 0; g < maxG; g++)
				for (int b = 0; b < maxB; b++)
				{
					calc (N - 1, r, g, b);

					bool far = (abs (r - startR) > d2 || abs (g - startG) > d2 || abs (b - startB) > d2);
					bool close = (abs (r - startR) < d1 && abs (g - startG) < d1 && abs (b - startB) < d1);

					if (far || close) ans += p[N-1][r][g][b];
				}

		return ans;
	}
};
