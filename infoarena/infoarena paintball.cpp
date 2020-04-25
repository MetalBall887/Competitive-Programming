	
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Each component has exactly one cycle.
//The minimal number of deaths = the minimal number of shots. Let's start with a leaf cutting induction. Take all leaves from
//the current graph (if there are any) and group them by vertices they are pointing on (two leaves are in the same set if
//they point at the same vertex). Notice that from each set exactly one vertex will shoot its predecessor and also in each
//set it actually doesn't matter which vertex it will be. That means, if we take any leaf and shoot the predecessor, this will
//be the optimal move. Thus, we can always take a leaf (if there are any) and shoot predecessors and erase both the predecessor
//and the leaf from the graph. After this we will end up with a group of cycles, for each cycle it's possible to arrange an order
//in such way the number of shots will be |V| / 2 (and it will be the optimal way).
//For the maximal number of deaths notice that leaves will never get killed, so let's find a way to shoot everyone but leaves.
//If it has leaves, let's take such an edge from a cycle so that we will not create a new leaf (the vertex has to have trees
//"attached" to it) and obtain a tree. Then simply have someone shoot the root, the tree will break down to several components
//shoot roots in each of them and proceed by induction. If there are no leaves in the graph, then it's a cycle and we can 
//arrange shots in a way the number of them will be |V|-1
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int u[N], to[N], cnt[N], lf[N];
vector <int> g[N];
int n;
 
int main () {
	ios::sync_with_stdio (0);
	cin.tie (NULL);
 
	freopen ("paintball.in", "r", stdin);
	freopen ("paintball.out", "w", stdout);
 
	cin >> n;
 
	for (int i = 0; i < n; i++) {
		int p;
		cin >> p;
 
		to[i] = p - 1;
		cnt[p-1]++;
	}
 
	int mn = 0, mx = 0;
 
	queue <int> q;
 
	for (int i = 0; i < n; i++) {
		if (!cnt[i]) {
			q.push (i); 
			lf[i] = 1;
		}
	}
 
	while (!q.empty ()) {
		int x = q.front ();
		q.pop ();
		u[x] = 1;
		if (u[to[x]]) continue;
		mn++;
		u[to[x]] = 1;
		if (!u[to[to[x]]] && --cnt[to[to[x]]] == 0) {
			q.push (to[to[x]]);
		}
	}
 
	for (int i = 0; i < n; i++) {
		if (!u[i]) {
			int sum = 0;
			int x = i;
			while (!u[x]) {
				u[x] = 1, sum++;
				x = to[x];
			}
 
			mn += (sum + 1) / 2;
		}
	}
 
	fill (u, u + n, 0);
 
	for (int i = 0; i < n; i++) {
		if (lf[i]) {
			int sum = 0;
			int x = i;
			while (!u[x]) {
				u[x] = 1, sum++;
				x = to[x];
			}
 
			mx += sum - 1;
		}
	}
 
	for (int i = 0; i < n; i++) {
		if (!u[i]) {
			int sum = 0;
			int x = i;
			while (!u[x]) {
				u[x] = 1, sum++;
				x = to[x];
			}
 
			mx += sum - 1 + (sum == 1);
		}
	}
 
	cout << mn << ' ' << mx;
}
