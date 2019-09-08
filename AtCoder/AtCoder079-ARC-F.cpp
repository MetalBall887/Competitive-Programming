#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//Let's solve a problem for a rooted tree. As we can see, numbers there are placed uniquely: leaves get 0, internal nodes -
//minimal excluded of its children: if we put less, there will be a child with the same number, more - there will be x where
//there is no number in set of children nodes. Now the graph that we get is a forest roots of which are connected in a cycle.
//we can see that root have only one additional direct child which can change their number only once (by adding a new child
//to the set it can "move" the number to the greater values). That means, there are two states of each vertex in a cycle.
//By choosing one in any of them we can uniquely deterimine others. Then we check for correctness of resulting numeration.
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

vector <int> g[1000000], cycle;

int p[1000000], n, cl[1000000], u[1000000], in[1000000];

int d[1000000], d_sec[1000000];

int dfs (int x, int p) {
	if (g[x].size() == 0 || d[x]) return d[x];

	vector <int> v;
	for (int to : g[x])
		if (to != p && !in[to])
			v.push_back(dfs (to, x));

	sort (v.begin(), v.end());
	v.push_back(INF);

	if (v[0] || v.empty()) d[x] = 0;
	else {
		for (int i = 0; i < v.size(); i++)
			if (v[i] + 1 != v[i+1]) {
				if (v[i] == v[i+1]) continue;
				d[x] = v[i] + 1;
				break;
			}
	}

	return d[x];
}

int main () {
	cin >> n;

	for (int i = 0; i < n; i++) {
		scanf ("%d", &p[i]);
		p[i]--;

		g[p[i]].push_back(i);
	}

	int x = 0;

	while (!cl[p[x]]) {
		cl[p[x]] = 1;
		x = p[x];
	}
	
	cycle.push_back(p[x]);
	in[p[x]] = 1;

	int k = p[x];

	while (k != x) {
		k = p[k];
		cycle.push_back(k);
		in[k] = 1;
	}

	for (int i = 0; i < n; i++)
		if (in[i]) dfs(i, -1);

	for (int i = 0; i < n; i++)
		if (in[i]) {
			vector <int> v;

			for (int to : g[i]) 
				if (!in[to]) {
					v.push_back(d[to]);
				}

			v.push_back(d[i]);
			v.push_back(INF);

			sort (v.begin(), v.end());

			if (v[0] || v.empty()) d_sec[i] = 0;
			else {
				for (int j = 0; j < v.size() - 1; j++)
					if (v[j] + 1 != v[j+1])	{
						if (v[j] == v[j+1]) continue;
						d_sec[i] = v[j] + 1;
						break;
					}
			}
		}
	
	bool b1 = true, b2 = true;

	vector <int> t(cycle.size ());

	t[0] = d[cycle[0]];
	for (int i = 1; i < cycle.size(); i++) {
		if (t[i-1] == d[cycle[i]]) {
			t[i] = d_sec[cycle[i]];
		}
		else {
			t[i] = d[cycle[i]];
		}

		if (t[i-1] == t[i]) {
			b1 = false;
			break;
		}
	}


	if (t[0] == t.back()) b1 = false;

	t[0] = d_sec[cycle[0]];
	for (int i = 1; i < cycle.size(); i++) {
		if (t[i-1] == d[cycle[i]]) {
			t[i] = d_sec[cycle[i]];
		}
		else {
			t[i] = d[cycle[i]];
		}

		if (t[i-1] == t[i]) {
			b2 = false;
			break;
		}
	}

	if (t.back() != d[cycle[0]]) b2 = false;

	if (!b1 && !b2) cout << "IMPOSSIBLE";
	else cout << "POSSIBLE";
	return 0;
}
