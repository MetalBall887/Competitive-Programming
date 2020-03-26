#include <bits/stdc++.h>
//Let's solve this problem with graphs. Nodes are corners of rectangles that are not inside of any (because then we wouldn't
//be able to connect the fence to them). Edges are sets of fences. We can see that either we can draw a line between
//two nodes as corners (that means, the minimal length of the fencing between them is the Manhattan distance between corners)
//or we can't. With the second option we can imagine "tying" the rope between these two points where it will either degrade to
//the straight line or there will be a polyline with breakpoints being corners. That was performed for Euclidian distance
//If we do this in a Manhattan distance, we'll get a similar image but there will be a "line" between corners only if there is 
//nothing in the rectangle formed by these corners. If there is something, the path will go through this "something".
//It's easier to get it if you imagine the "lasso" is metal and rectangles are "magnets". To find such edges we can use for 
//each corner a scanning line on x with keeping a range of y. After this we want to find the smallest cycle going around the 
//first mansion. For this let's put a "scanner" - a half-line above the leftmost topmost corner of the first mansion. For every
//topological loop not containing this first mansion the start of this half-line will start be of it and thus the scanner will 
//intersect the loop an even number of times. To use this, we can keep for each path not only the destination vertex but the 
//parity of the number of times the path crossed the scanner. It will start at even and end  should in odd so that the scanner 
//with the mansion itself would be inside of the loop. Now we can start Dijkstra from every node v and search for the shortest 
//path (v, 0) -> (v, 1).
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

struct Pt {
	int x, y;

	bool operator < (const Pt& b) {
		return tie (x, y) < tie (b.x, b.y);
	}

	bool operator == (const Pt& b) {
		return tie (x, y) == tie (x, y);
	}
};

vector <Pt> p;

vector < pair <int, int> > g[N]; 

struct Rect {
	Pt l, r;

	bool operator < (const Rect& b) {
		if (tie (l.x, r.x) == tie (b.l.x, b.r.x)) {
			return tie (l.y, r.y) < tie (b.l.y, b.r.y);
		}
		return tie (l.x, r.x) < tie (b.l.x, b.r.x);
	}
} a[10000];

int n, m;

bool is_inner (int x, int y) {
	for (int i = 0; i < n; i++) {
		if (a[i].l.x < x && x < a[i].r.x &&
			a[i].l.y < y && y < a[i].r.y) return true;
	}

	return false;
}

int d[10000], pr[10000];

int main () {

	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> a[i].l.x >> a[i].l.y >> a[i].r.x >> a[i].r.y;
	}

	Pt st = a[0].l;

	sort (a, a + n);

	for (int i = 0; i < n; i++) {
		if (!is_inner (a[i].l.x, a[i].l.y)) p.push_back (a[i].l);
		if (!is_inner (a[i].l.x, a[i].r.y)) p.push_back (Pt ({a[i].l.x, a[i].r.y}));
		if (!is_inner (a[i].r.x, a[i].l.y)) p.push_back (Pt ({a[i].r.x, a[i].l.y}));
		if (!is_inner (a[i].r.x, a[i].r.y)) p.push_back (a[i].r);
	}

	m = p.size ();

	sort (p.begin(), p.end());

	for (int i = 0; i < m; i++) {
		int j = 0;

		int min_y = -1e9, max_y = 1e9;

		while (j < n && a[j].l.x < p[i].x) {
			if (a[j].r.x <= p[i].x) {
				j++;
				continue;
			}

			if (p[i].y <= a[j].l.y) max_y = min (max_y, a[j].l.y);
			else min_y = max (min_y, a[j].r.y);

			j++;
		}

		for (int k = i + 1; k < m; k++) {
			while (j < n && a[j].l.x < p[k].x) {
				if (a[j].l.y < p[i].y && p[i].y < a[j].r.y) {
					min_y = a[j].r.y, max_y = a[j].l.y;
				}
				else if (p[i].y <= a[j].l.y) max_y = min (max_y, a[j].l.y);
				else min_y = max (min_y, a[j].r.y);
				j++;
			}

			if (min_y > max_y) break;

			if (p[k].y < min_y || max_y < p[k].y) continue;

			int len = abs (p[i].x - p[k].x) + abs (p[i].y - p[k].y);

			if (p[k].y <= st.y && p[i].y <= st.y && p[i].x <= st.x && st.x < p[k].x) {
				g[i].push_back ({k + m, len}), g[k + m].push_back ({i, len});
				g[k].push_back ({i + m, len}), g[i + m].push_back ({k, len});
			} else {
				g[i + m].push_back ({k + m, len}), g[k].push_back ({i, len});
				g[k + m].push_back ({i + m, len}), g[i].push_back ({k, len});
			}
		}
	}

	priority_queue < pair <int, int> > q;

	int ans = 1e9;

	for (int i = 0; i < p.size (); i++) {
		fill (d, d + 2 * m, 1e9);
		memset (pr, -1, sizeof (pr));
		d[i] = 0;
		q.push ({0, i});

		while (!q.empty ()) {
			auto x = q.top ();
			q.pop ();

			if (d[x.second] != -x.first) continue;

			if (d[x.second] >= ans) break;

			for (auto to : g[x.second]) {
				if (d[to.first] > d[x.second] + to.second) {
					d[to.first] = d[x.second] + to.second;
					q.push ({-d[to.first], to.first});
					pr[to.first] = x.second;
				}
			}
		}

		ans = min (ans, d[i + m]);
	}

	cout << ans;
}
