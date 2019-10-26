#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
//Lemma: every possible assignment has the minimal summary length. Let's look at one assignment and try to swap two dist.
//stations. Either we will get an invalid assignment or both dist. points are above and lefter than both ext. points
//That means, we can divide our plane with two perpendicular lines that way both types of stations will be in opposite 
//quadrants. Then there is a valid path for both pairs that goes through the intersection of these dividing lines (axis)
//and in that point we can "exchange paths" and the total length will not change.
//So the task is to find any possible assignment. We do a sweeping line on x and for each ext. station we want to take
//the lowest available dist. station that is above.
#include <set>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

struct point {
	int x, y, id;

	point (int x, int y, int id) : x (x), y (y), id (id) {}

	bool operator < (const point& b) const {
		return x < b.x;
	}
};

int distance (point a, point b) {
	return abs (a.x - b.x) + abs (a.y - b.y);
}

int n;

set < pair <int, int> > s;

vector <point> ext, dist, orig;

int main () {
	cin >> n;

	ll sum = 0;

	for (int i = 0; i < n; i++) {
		int x, y;
		scanf ("%d%d", &x, &y);
		ext.emplace_back (point (x, y, i));
	}

	for (int i = 0; i < n; i++) {
		int x, y;
		scanf ("%d%d", &x, &y);
		dist.emplace_back (point (x, y, i));
	}

	auto e = ext, d = dist;
	sort (ext.begin(), ext.end());
	sort (dist.begin(), dist.end());

	int ptr = 0;

	vector < pair <int, int> > ans;

	for (int i = 0; i < n; i++) {
		while (ptr < ext.size () && ext[ptr].x <= dist[i].x) {
			s.insert ({ext[ptr].y, ext[ptr].id});
			ptr++;
		}

		auto k = s.lower_bound ({dist[i].y, -1});

		ans.push_back ({k -> second, dist[i].id});

		s.erase (k);
	}

	for (auto a : ans) {
		sum += distance (e[a.first], d[a.second]);
	}

	cout << sum << endl;

	for (auto a : ans) 
		cout << a.first + 1 << ' ' << a.second + 1 << endl;
}
