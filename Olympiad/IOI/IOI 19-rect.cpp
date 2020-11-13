#include "rect.h"
#include <bits/stdc++.h>
//Let's first try to analyze an 1D version of this problem. Let's call segments such that all inner elements are smaller than first and last element closed and
//first and last elements outer elements. Let a[l, r] be closed segment and a[l] < a[r]. Then there is no r': l < r' and a[l] < a[r'] and a[l,r'] is closed 
//different from r. We can find such r with minimum stack. Now for position x find r[x] - the right border of a closed segment such that the left border is x and
//a[x] < a[r], same for l[x]. For a 2D version we can do the same in four directions. Now, for example suppose (x, y) is some corner of a closed rectangle, all its
//rows and columns are closed. Let's try to approximize corners: (l[x][y], y) might be the second corner and (l[x][y], u[l[x][y]][y]) be the third corner. After 
//this remember the rectangle defined by these corners as probably closed one (it might happen not to be closed). It can happen this isn't the only such rectangle
//with some corner (x, y) and not all such rectangles are touched, since functions like l[x][y] highly depend if the corner(s) of the rectangle is locally minimal.
//But if we consider all possible orderings of corners of the closed rectangles, we can come up with a group of such conditions that will find all closed rectangles
//given that we go through all possible corners. The last part is to check every of them and check for duplications.
 
using namespace std;
typedef long long ll;
 
int n, m, t;
 
pair <int, int> hor_l[2500][2500], hor_r[2500][2500];
pair <int, int> ver_u[2500][2500], ver_d[2500][2500];
 
vector < array <int, 4> > v;
vector < array <int, 4> > bucket[2500];
 
struct window : vector < pair <int, int> > {
	void append (int x) {
		while (!empty () && back ().first < x) pop_back ();
	}
};
 
void check_above (pair <int, int>& p, int i, int l, int r) {
	if (!i) return;
	if (hor_l[i-1][r].first == l) p.second += hor_l[i-1][r].second;
	else if (hor_r[i-1][l].first == r) p.second += hor_r[i-1][l].second;
}
 
void check_left (pair <int, int>& p, int u, int d, int j) {
	if (!j) return;
	if (ver_d[u][j-1].first == d) p.second += ver_d[u][j-1].second;
	else if (ver_u[d][j-1].first == u) p.second += ver_u[d][j-1].second;
}
 
void check_rectangle (vector < vector <int> >& a, int x1, int y1, int x2, int y2) {
	if (x2 - x1 < 2 || y2 - y1 < 2) return;
	int hor_size, ver_size;
 
	if (a[x2-1][y1] <= a[x2-1][y2]) {
		if (hor_r[x2-1][y1].first != y2) return;
		ver_size = hor_r[x2-1][y1].second;
	}
	else {
		if (hor_l[x2-1][y2].first != y1) return;
		ver_size = hor_l[x2-1][y2].second;
	}
 
	if (a[x1][y2-1] <= a[x2][y2-1]) {
		if (ver_d[x1][y2-1].first != x2) return;
		hor_size = ver_d[x1][y2-1].second;
	}
	else {
		if (ver_u[x2][y2-1].first != x1) return;
		hor_size = ver_u[x2][y2-1].second;
	}
 
	if ((hor_size >= y2 - y1 - 1) && (ver_size >= x2 - x1 - 1)) {
		v.push_back ({x1, y1, x2, y2});
	}
}
 
void check_position (vector< vector <int> >& a, int i, int l, int r) {
	int x;
 
	if (r - l < 2) return;
 
	x = ver_u[i+1][l+1].first;
	if (x != -1) check_rectangle (a, x, l, i + 1, r);
	
	x = ver_d[i-1][l+1].first;
	if (x != -1) check_rectangle (a, i - 1, l, x, r);
	
	x = ver_u[i+1][r-1].first;
	if (x != -1) check_rectangle (a, x, l, i + 1, r);
	
	x = ver_d[i-1][r-1].first;
	if (x != -1) check_rectangle (a, i - 1, l, x, r);
 
}
 
 
ll count_rectangles (vector<vector<int> > a) {
	n = a.size (), m = a[0].size ();
 
	window s;
 
	for (int i = 0; i < n; i++) {
 
		s.clear ();
		
		for (int j = 0; j < m; j++) {
			s.append (a[i][j]);
			if (!s.empty ()) {
				int l = s.back ().second, r = j;
				hor_l[i][r].first = l;
				hor_l[i][r].second = 1;
 
				check_above (hor_l[i][r], i, l, r);
			} else hor_l[i][j].first = -1;
			s.push_back ({a[i][j], j});
		}
 
		s.clear ();
 
		for (int j = m - 1; j >= 0; j--) {
			s.append (a[i][j]);
			if (!s.empty ()) {
				int l = j, r = s.back ().second;
				hor_r[i][l].first = r;
				hor_r[i][l].second = 1;
 
				check_above (hor_r[i][l], i, l, r);
			} else hor_r[i][j].first = -1;
			s.push_back ({a[i][j], j});
		}
	}
 
	for (int j = 0; j < m; j++) {
		
		s.clear ();
 
		for (int i = 0; i < n; i++) {
			s.append (a[i][j]);
			if (!s.empty ()) {
				int u = s.back ().second, d = i;
				ver_u[d][j].first = u;
				ver_u[d][j].second = 1;
 
				check_left (ver_u[d][j], u, d, j);
			} else ver_u[i][j].first = -1;
			s.push_back ({a[i][j], i});
		}
 
		s.clear ();
 
		for (int i = n - 1; i >= 0; i--) {
			s.append (a[i][j]);
			if (!s.empty ()) {
				int u = i, d = s.back ().second;
				ver_d[u][j].first = d;
				ver_d[u][j].second = 1;
 
				check_left (ver_d[u][j], u, d, j);
			} else ver_d[i][j].first = -1;
			s.push_back ({a[i][j], i});
		}
	}
 
	for (int i = 1; i < n - 1; i++) {
		for (int j = 0; j < m; j++) {
			if (hor_l[i][j].first != -1) check_position (a, i, hor_l[i][j].first, j);
			if (hor_r[i][j].first != -1) check_position (a, i, j, hor_r[i][j].first);
		}
	}
 
	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < max (n, m); i++)
			bucket[i].clear ();
 
		for (auto&& a : v) {
			bucket[a[k]].push_back (a);
		}
 
		v.clear ();
 
		for (int i = 0; i < max (n, m); i++)
			for (auto&& a : bucket[i])
				v.push_back (a);		
	}
	
	int cnt = 0;
 
	for (int i = 0; i < (int) v.size (); i++)
		if (!i || v[i-1] != v[i]) cnt++;
 
	v.clear ();
 
	return cnt;
}
