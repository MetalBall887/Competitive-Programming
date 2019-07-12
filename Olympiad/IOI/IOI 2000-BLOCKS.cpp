#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
//Finding all possible blocks with bruteforce and finding for each found block its pattern from 12 patterns given in the input
//Then, try to fit every possible block to the figure in rightmost points with bruteforce. Algorithm is exponential but we can
//use branch-and-bound technique to optimise the bruteforce (in each branch of complete search find the lower bound of the 
//answer that could be gotten from this state. If it is already less optimal then currently found minimal answer, leave 
//the branch).
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

int cur_min, v, timer, ind[10000], ans[1000000], d[1000000], m;

struct point
{
	int x, y, z;

	bool operator < (const point& b) const
	{
		return make_pair (x, make_pair (y, z)) < make_pair (b.x, make_pair (b.y, b.z));
	}


	bool operator == (const point& b) const
	{
		return make_pair (x, make_pair (y, z)) == make_pair (b.x, make_pair (b.y, b.z));
	}

	bool operator != (const point& b) const
	{
		return make_pair (x, make_pair (y, z)) != make_pair (b.x, make_pair (b.y, b.z));
	}

	point operator- (const point& b) const
	{
		return {x - b.x, y - b.y, z - b.z};
	}
};

struct block 
{
	int a[8][8][8];

	bool operator == (const block& b) const
	{
		for (int i = 0; i < 7; i++)
			for (int j = 0; j < 7; j++)
				for (int k = 0; k < 7; k++)
					if (a[i][j][k] != b.a[i][j][k]) return false;

		return true;
	}

	block ()
	{
		memset (a, 0, sizeof (a));
	}
};

vector <vector <point> > blocks;

void Rec (block a, int step, vector <point> old_v)
{
	if (step == 4) return;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 7; j++)
			for (int k = 0; k < 7; k++)
			{
				if (a.a[i][j][k]) continue;

				if ((i && a.a[i-1][j][k]) || (j && a.a[i][j-1][k]) || (k && a.a[i][j][k-1])
					|| a.a[i+1][j][k] || a.a[i][j+1][k] || a.a[i][j][k+1])
				{

					a.a[i][j][k] = 1;
					
					vector<point> v = old_v;
					v.push_back ({i, j - 3, k - 3});
					blocks.push_back (v);

					Rec (a, step + 1, v);
					a.a[i][j][k] = 0;
				}
			}
}

struct state
{
	int a[7][7][7], count, sum[7];

	point start;

	int update ()
	{
		for (int i = 0; i < 7; i++)
		{
			if (!sum[i]) continue;
			for (int j = 0; j < 7; j++)
				for (int k = 0; k < 7; k++)
					if (a[i][j][k])
					{
						start = {i, j, k};
						return 0;
					}
		}
	}

	state ()
	{

		memset (a, 0, sizeof (a));
	}
};

void Rotate (point& x, char d)
{
	int q;
	if (d == 'x')
	{
		if (x.y >= 0 && x.z >= 0) q = 1;
		if (x.y >= 0 && x.z < 0) q = 2;
		if (x.y < 0 && x.z < 0) q = 3;
		if (x.y < 0 && x.z >= 0) q = 4;

		x.y = abs (x.y);
		x.z = abs (x.z);
		swap (x.y, x.z);

		if (q == 1) x.z *= -1;
		if (q == 2) {x.y *= -1; x.z *= -1;}
		if (q == 3) x.y *= -1;
	}

	if (d == 'y')
	{
		if (x.x >= 0 && x.z >= 0) q = 1;
		if (x.x >= 0 && x.z < 0) q = 2;
		if (x.x < 0 && x.z < 0) q = 3;
		if (x.x < 0 && x.z >= 0) q = 4;

		x.x = abs (x.x);
		x.z = abs (x.z);
		swap (x.x, x.z);

		if (q == 1) x.z *= -1;
		if (q == 2) {x.x *= -1; x.z *= -1;}
		if (q == 3) x.x *= -1;
	}

	if (d == 'z')
	{
		if (x.x >= 0 && x.y >= 0) q = 1;
		if (x.x >= 0 && x.y < 0) q = 2;
		if (x.x < 0 && x.y < 0) q = 3;
		if (x.x < 0 && x.y >= 0) q = 4;

		x.x = abs (x.x);
		x.y = abs (x.y);
		swap (x.x, x.y);

		if (q == 1) x.y *= -1;
		if (q == 2) {x.x *= -1; x.y *= -1;}
		if (q == 3) x.x *= -1;
	}
}

void dfs (state a, int t)
{
	a.update ();

	if (!a.count)
	{
		if (cur_min > t)
		{
			cur_min = t;

			for (int i = 0; i < t; i++)
				ans[i] = d[i];
		}
		return;
	}

	if (t + (a.count + 3) / 4 >= cur_min) return;

	for (int z = 0; z < blocks.size (); z++)
	{
		vector<point>& f = blocks[z];
		bool b = true;

		for (int i = 0; i < f.size (); i++)
		{
			if (!b || a.start.x + f[i].x >= 7 || a.start.y + f[i].y >= 7 || a.start.z + f[i].z >= 7 
				|| a.start.x + f[i].x < 0 || a.start.y + f[i].y < 0 || a.start.z + f[i].z < 0 
				|| !a.a[a.start.x + f[i].x][a.start.y + f[i].y][a.start.z + f[i].z])
			{
				b = false;
				break;
			}
		}

		if (b)
		{
			state c = a;

			for (int i = 0; i < f.size (); i++)
			{
				c.count--;
				c.sum[a.start.x + f[i].x]--;
				c.a[a.start.x + f[i].x][a.start.y + f[i].y][a.start.z + f[i].z] = 0;
			}

			d[t] = ind[z];
			dfs (c, t + 1);
		}
	}
}
 
int main ()
{
	block a;

	a.a[0][3][3] = 1;

	vector <point> f;
	f.push_back ({0, 0, 0});
 
	blocks.push_back (f);

	Rec (a, 1, f);

	state st;

	vector < vector <point> > bl;

	for (int i = 0; i < blocks.size (); i++)
	{
		sort (blocks[i].begin(), blocks[i].end());
	}	

	for (int i = 0; i < blocks.size (); i++)
	{
		bool b = true;

		for (int j = 0; j < i; j++)
		{
			if (blocks[i] == blocks[j]) b = false;
		}

		if (b) bl.push_back (blocks[i]);
	}

	blocks = bl;

	m = 12;


	for (int i = 0; i < m; i++)
	{
		int k;
		cin >> k;
		cin >> k;

		vector <point> v;

		for (int j = 0; j < k; j++)
		{
			int x, y, z;

			cin >> x >> y >> z;

			v.push_back ({x, y, z});
		}

		for (int a = 0; a < 4; a++)
		{
			for (int b = 0; b < 4; b++)
			{
				for (int c = 0; c < 4; c++)
				{
					sort (v.begin(), v.end());

					for (int j = 0; j < blocks.size (); j++)
					{
						bool k = true;

						auto& block = blocks[j];
						auto p = block[0] - v[0];

						for (int f = 0; f < block.size (); f++)
							if (block[f] - v[f] != p)
							{
								k = false;
								break;
							}

						if (k && block.size () == v.size ()) ind[j] = i + 1;
					}


					for (point& p : v)
						Rotate (p, 'z');
				}

				for (point& p : v)
					Rotate (p, 'y');
			}

			for (point& p : v)
				Rotate (p, 'x');
		}

	}

	cin >> v;

	for (int i = 1; i <= v; i++)
	{
		int x, y, z;

		cin >> x >> y >> z;
		st.a[x-1][y-1][z-1] = 1;
		st.count++;
		st.sum[x-1]++;
	}

	st.update ();

	cur_min = v;

	dfs (st, 0);

	cout << cur_min << endl;

	for (int i = 0; i < cur_min; i++)
		cout << ans[i] << ' ';
}
