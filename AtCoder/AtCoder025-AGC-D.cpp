#include <iostream>
#include <vector>
#include <stdio.h>
//First, create two graphs, where a point with integer coordinates is a vertex and there is an edge between two when distance
//between them is sqrt(d1) then sqrt(d2). It can be proven that both will be bipartite. after this, all points will be
//partitioned twice, each of them will be in exactly two sets. We can decribe this partitioning with 4 sets (00, 01, 10, 11)
//and then take the biggest out of it, which will be at least n^2. The number of edges is O(n^3).
#include <cstring>
#include <cstdlib>
#include <cmath>
 
using namespace std;
 
const int N = 1000;
 
const int INF = 1e9;
 
int u[1000000], cl[1000000], n, d1, d2, cnt[4];
 
vector < vector <int> > g (1000000), f (1000000);
 
int dist (pair <int, int> a, pair <int, int> b)
{
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}
 
void dfs_bw (int x, int c)
{
    u[x] = 1;
    cl[x] += 2 * c;
    
    for (int to : g[x])
	if (!u[to])
	    dfs_bw (to, !c);
}
 
void dfs_rb (int x, int c)
{
    u[x] = 1;
    cl[x] += c;
    
    for (int to : f[x])
	if (!u[to])
	    dfs_rb (to, !c);
}
 
void build (int d, vector < vector <int> >& g)
{
    vector < pair <int, int> > ab;
    
    for (int i = -n; i < n; i++)
	for (int j = -n; j < n; j++)
	    if (i * i + j * j == d)
	    ab.push_back ({i, j});
    
    for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
	    for (auto a : ab)
	    {
		if (i + a.first < n && i + a.first >= 0
		    && j + a.second < n && j + a.second >= 0)
		g[n * i + j].push_back (n * (i + a.first) + j + a.second);
	    }
}
 
int main () 
{
    cin >> n >> d1 >> d2;
    
    n *= 2;
    
    build (d1, g);
    build (d2, f);
    
    for (int i = 0; i < n * n; i++)
	if (!u[i]) dfs_bw (i, 0);
    
    memset (u, 0, sizeof (u));
    
    for (int i = 0; i < n * n; i++)
	if (!u[i]) dfs_rb (i, 0);
    
    for (int i = 0; i < n * n; i++)
	cnt[cl[i]]++;
    
    int ind = 0, ptr = 0;
    
    for (int i = 0; i < 4; i++)
	if (cnt[i] > cnt[ind]) ind = i;
    
    for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
	    if (cl[n * i + j] == ind)
	    {
		printf ("%d %d\n", i, j);
		ptr++;
		
		if (4 * ptr == n * n) return 0;
	    }
	
		
	
}
