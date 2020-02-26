#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

//In this game, there are several moves that ensure the outcome. First is choosing the path with not minimal distance. That means, the
//other player will be able to choose the minimal path and will arrive faster even if one will leap over the other as you should spend
//at least two moves to get off the minimal path and come back to it. Other is, if they both choose the minimal path, one that leaps
//over the other, wins. If there is no leap, the first player wins. Let D be the distance of the minimal path from A to B. For odd D 
//let's notice that after floor(D/2) steps both pieces can't be in the same cell, so even if there is a leap, player A leaps. That means,
//for odd D A always wins. For even D we can divide all vertices by layers from A and B and solve the problem with dynamic programming, 
//where d[xa][xb][i] will be -1 if the player A wins in case if i steps were performed and A piece lies on the xa's cell in the list of
//cells with the distance of i from the A, similarly for B. Notice that the game is settled for all i > D / 2, since there will be no
//way to stay on minimal path and leap, so the first player wins. That means, we need to check only first D/2 moves.
 
using namespace __gnu_pbds;
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, da[N], db[N], st_a, st_b;
string s[N];
int ha[N], hb[N], d[300][300][2];
vector <int> g[N], va[N], vb[N];
int u[N];
 
void bfs(int st, int* d) {
	memset(u, 0, sizeof(int) * n * n);
	queue <int> q;
	q.push(st);
	d[st] = 0, u[st] = 1;
 
	while (!q.empty()) {
		int x = q.front();
		q.pop();
 
		for (int to : g[x])
			if (!u[to]) {
				u[to] = 1, d[to] = d[x] + 1;
				q.push(to);
			}
	}
}
 
int can_jump(int a, int b) {
	return (da[a] + db[b] + 1 == da[st_b]) && (abs(a - b) == 1 || abs(a - b) == n);
}
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while (t--) {
		cin >> n;
 
		for (int i = 0; i < n * n; i++) {
			g[i].clear();
			va[i].clear();
			vb[i].clear();
		}
 
		for (int i = 0; i < n; i++)
			cin >> s[i];
 
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				if (s[i][j] == 'A') st_a = i * n + j;
                if (s[i][j] == 'B') st_b = i * n + j;
                if (s[i][j] == '#') continue;
 
				int x = i * n + j;
				if (j && s[i][j - 1] != '#') g[x].push_back(x - 1);
				if (i && s[i - 1][j] != '#') g[x].push_back(x - n);
 
				if (j + 1 < n && s[i][j + 1] != '#') g[x].push_back(x + 1);
				if (i + 1 < n && s[i + 1][j] != '#') g[x].push_back(x + n);
			}
 
		bfs(st_a, da);
		bfs(st_b, db);
 
		int dist = da[st_b];
		if (dist & 1) {
			cout << "A\n";
			continue;
		}
 
		for (int i = 0; i < n * n; i++) {
			if (da[i] + db[i] == dist) {
				ha[i] = va[da[i]].size();
				va[da[i]].push_back(i);
 
				hb[i] = vb[db[i]].size();
				vb[db[i]].push_back(i);
 
				vector <int> v;
				for (int to : g[i]) {
					if (da[i] + 1 + db[to] == dist ||
						da[to] + 1 + db[i] == dist) {
						v.push_back(to);
					}
				}
 
				g[i] = move(v);
			}
		}
 
		memset(d, -1, sizeof(d));
 
		int c = ((dist / 2) & 1);
 
		memset (d, -1, sizeof (d));
		for (int i = dist / 2 - 1; i >= 0; i--) {
			int c = (i & 1);
			for (int a : va[i])
				for (int b : vb[i]) {
					int xa = ha[a], xb = hb[b];
					if (b == st_a) { d[xa][xb][c] = 1; continue; }
					if (can_jump(a, b)) { d[xa][xb][c] = -1; continue; }
					d[xa][xb][c] = 1;
					for (int new_a : g[a]) {
						if (da[a] + db[new_a] + 1 != dist) continue;
						if (new_a == st_b) { d[xa][xb][c] = -1; break; }
						if (can_jump(new_a, b)) continue;
 
						int cur = -1;
						for (int new_b : g[b]) {
							if (da[new_b] + db[b] + 1 != dist) continue;
							cur = max(cur, d[ha[new_a]][hb[new_b]][!c]);
						}
						if (cur == -1) { d[xa][xb][c] = -1; break; }
					}
				}
		}
 
		if (d[ha[st_a]][hb[st_b]][0] == -1) cout << "A\n";
		else cout << "B\n";
	}
}
