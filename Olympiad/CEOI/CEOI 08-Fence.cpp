#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let's analyze the set of points we can take. First of all, the cost doesn't depend on the number of fences, so we
//can just construct a polygon with a maximal area which is convex hull. Also since we won't need any other fence points
//the set of points will always form a convex polygon. Now let's transform it to the problem that is more comfortable to 
//solve with this solution: find such set of points that the convex hull has the maximum value 
//111*(# of trees inside of the hull) - 20*(# of points in the set). Break the convex hull down into the leftmost point, 
//the rightmost point, the upper hull and the lower hull. d_up[i][j] - the maximum 111#of trees - 20#of points if counting 
//all trees directly below the upper hull and the leftmost and rightmost points are h[i] and h[j]. Similarly, d_down[i][j] 
//but the lower hull and for trees strictly above it. What will happen if we add those two values: the upper and lower hulls 
//will form a convex hull and each tree is either above the lower hull, below the upper hull or both, which means every tree 
//horizontally corresponding to the polygon is counted, if the tree is inside, it's counted twice. Now we can subtract the 
//number of all trees in the horizontal range between h[i] and h[j] and get the answer. We can transit from states to states 
//as usually in 2d range dp in O(n). Overall complexity is O(n^3).

using namespace __gnu_pbds;

#define N 2000001

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int d_up[100][100], d_low[100][100], above[100][100], below[100][100], n, m;
int mx;

struct Pt {
	int x, y;

	Pt operator- (const Pt& p) {
		return Pt ({x - p.x, y - p.y});
	}

	bool operator< (const Pt& b) {
		return tie (x, y) < tie (b.x, b.y);
	}
};

int cross (Pt a, Pt b) {
	return a.x * b.y - a.y * b.x;
}

Pt h[N], t[N];

int main () {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		cin >> h[i].x >> h[i].y;
	}

	for (int i = 0; i < m; i++) {
		cin >> t[i].x >> t[i].y;
	}

	sort (h, h + n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (h[j] < h[i]) continue;

			for (int k = 0; k < m; k++) {
				if (h[i].x <= t[k].x && t[k].x < h[j].x) {
					if (cross (t[k] - h[i], h[j] - h[i]) < 0) above[i][j]++;
					else below[i][j]++;
				}
			}
		}

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++) {
			d_up[i][j] = below[i][j] * 111;
			d_low[i][j] = above[i][j] * 111;
		}

	for (int k = 1; k < n; k++) {
		for (int i = 0; i + k < n; i++) {
			for (int j = i + 1; j < i + k; j++) {
				if (cross (h[j] - h[i], h[i+k] - h[i]) < 0) {
					d_up[i][i+k] = max (d_up[i][i+k], d_up[i][j] + d_up[j][i+k] - 20);
				}
				else {
					d_low[i][i+k] = max (d_low[i][i+k], d_low[i][j] + d_low[j][i+k] - 20);
				}
			}

			int ans = d_up[i][i+k] + d_low[i][i+k] - 111 * (below[i][i+k] + above[i][i+k]) - 40;

			mx = max (mx, ans);
		}
	}

	cout << m * 111 - mx;
}
