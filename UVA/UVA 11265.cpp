#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
//We need to find an intersection of halfplanes if we can represent the line i as a halfplane where its vector is directed
//towards the fountain. Algorithm is: let's say we have an intersection of first k lines. To add a (k+1)st, we need
//to "cut" the current one: look at all segments, if the segement is fully in the halfplane, leave it. If it's not on the
//halfplane, remove it. If it's partially on the halfplane, leave the part that belongs to the halfplane and change a 
//missing endpoint to the intersection point of line k+1 and this segment. Can be shown, that the intersection's
//borders make a convex polygon, so this new line will have 0 or 2 intersection points. If two, add a new segment with
//these two points. With all points remaining in the polygon order them clockwise with Graham's scan and calculate an
//area with a cross formula.
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
 
int n, ptr, w, h;

ld foun_x, foun_y;

struct point
{
	ld x, y;

	bool operator < (const point& b)
	{
		return (x == b.x ? y < b.y : x < b.x);
	}
};

vector <point> points;

ld area (point a, point b, point c)
{
	return (a.x * b.y + b.x * c.y + c.x * a.y) - (b.x * a.y + c.x * b.y + a.x * c.y);
}

struct line
{
	ld k, b;
	int sign;
	point point_l, point_r;


	line (ld x1, ld y1, ld x2, ld y2)
	{
		if (x1 == x2) 
		{
			sign = (x1 < foun_x ? 1 : -1);
			k = 1e13;
			b = x1;
		}
		else
		{
			ld A = y1 - y2, B = x2 - x1;
			ld C = -A * x1 - B * y1;

			k = -A / B;
			b = -C / B;

			if (k * foun_x + b > foun_y) sign = -1;
			else sign = 1;
		}
	}
};

ld eval (line a, point x)
{
	if (fabs (a.k - 1e13) < 1e-9) return (a.b < x.x ? 1 : -1);

	return (a.k * x.x + a.b > x.y ? -1 : 1);
}

point intersect (line a, line b)
{
	ld x;
	if (fabs (a.k - 1e13) < 1e-9) return {a.b, b.k * a.b + b.b};
	else if (fabs (a.k - 1e13) < 1e-9) return {b.b, a.k * b.b + a.b};
	else x = (a.b - b.b) / (b.k - a.k);

	return {x, a.k * x + a.b};
}

vector <line> lines, new_lines;

int main ()
{
	int t = 0;
	while (cin >> n >> w >> h >> foun_x >> foun_y)
	{
		lines.clear ();
		points.clear ();
		t++;
		line bound_1 (0, 0, w, 0), bound_2 (w, 0, w, h), bound_3 (w, h, 0, h), bound_4 (0, h, 0, 0);

		bound_1.point_r = bound_2.point_l = {(long double) w, (long double) 0};
		bound_2.point_r = bound_3.point_l = {(long double) w, (long double) h};
		bound_3.point_r = bound_4.point_l = {(long double) 0, (long double) h};
		bound_4.point_r = bound_1.point_l = {(long double) 0, (long double) 0};

		lines.push_back (bound_1);
		lines.push_back (bound_2);
		lines.push_back (bound_3);
		lines.push_back (bound_4);

		for (int i = 0; i < n; i++)
		{
			new_lines.clear ();
			ld x1, x2, y1, y2;

			scanf ("%Lf%Lf%Lf%Lf", &x1, &y1, &x2, &y2);

			line a (x1, y1, x2, y2);

			bool is_l = false;

			for (auto l : lines)
			{
				bool del_l = false, del_r = false;

				if (a.sign != eval (a, l.point_l)) del_l = true;
				if (a.sign != eval (a, l.point_r)) del_r = true;

				if (del_l && del_r) continue;

				if (!del_l && !del_r) new_lines.push_back (l);
				else
				{
					point Int = intersect (l, a);

					if (!is_l)
					{
						is_l = true;
						a.point_l = Int;
					}
					else a.point_r = Int;

					if (del_l) l.point_l = Int;
					else l.point_r = Int;

					new_lines.push_back (l);
				}
			}

			if (is_l) new_lines.push_back (a);

			lines = new_lines;
		}

		for (line a : lines)
		{
			points.push_back (a.point_l);
			points.push_back (a.point_r);
		}

		sort (points.begin(), points.end());

		vector <point> ch1, ch2;

		for (auto a : points)
		{
			if (area (points[0], a, points.back ()) >= 0)
			{
				while (ch1.size () >= 2 && area (ch1[ch1.size () - 2], ch1[ch1.size () - 1], a) <= 0)
					ch1.pop_back ();
				ch1.push_back (a);
			}
			else
			{
				while (ch2.size () >= 2 && area (ch2[ch2.size () - 2], ch2[ch2.size () - 1], a) >= 0)
					ch2.pop_back ();
				ch2.push_back (a);
			}
		}

		points.clear ();

		for (auto a : ch1)
			points.push_back (a);

		reverse (ch2.begin(), ch2.end());

		for (auto a : ch2)
			points.push_back (a);

		ld ans = 0;

		for (int i = 1; i < points.size () - 1; i++)
			ans += fabs (area (points[0], points[i], points[i + 1]));

		ans = ans / (ld) 2.0;

		printf("Case #%d: %.3Lf\n", t, ans);
	}
}
