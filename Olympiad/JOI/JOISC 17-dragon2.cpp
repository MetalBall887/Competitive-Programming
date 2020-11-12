#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//First of all, let's find out when dragon X hits dragon Y through the road AB. Consider vectors AX, AY, BX, BY. If the dragons are on the same side of AB, 
//X attacks Y if and only if  AX < AY and BX > BY. If they are on different sides, AX > -AY and BX < -BY should hold. This can be checked massively with 
//2d offline queries, where we manage vectors from A with a scanning line and vectors from B with range queries. This will specially allow us to find a number 
//of dragons that can get hit by and the number of dragons that can hit the special group through the road AB in O(N), so for a group x we can precalculate
//queries (x, *) and (*, x) in O(N). For groups x and y we can compute (x, y) in O(|x| + |y|). This is a good basis for an sqrt optimisation: If a group x is big,
//we can precompute every query with it in O(N). After precomputing all queries having big groups (there won't be many big groups) we will only have queries with
//small groups left, which we can compute with our plain algorithm. Overall complexity will be O((N+Q)sqrtN)
 
using namespace __gnu_pbds;
 
#define N 200001
 
using namespace std;
 
 
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
struct Pt {
	ll x, y;
 
	Pt (int x, int y) : x (x), y (y) {}
	Pt () : x (0), y (0) {}
 
	ll cross (const Pt& b) const { return x * b.y - b.x * y; }
	bool operator < (const Pt& b) const { return cross (b) < 0; }
	Pt operator - (const Pt& b) const { return Pt (x - b.x, y - b.y); }
	Pt operator - () const { return Pt (-x, -y); }
} s, e;
 
bool OO = true;
 
vector <int> vs[N];
Pt p[N], pe[N], ps[N];
 
vector < pair <Pt, int> > ords, orde;
 
gp_hash_table <int, ll> qu[N];
 
ll big[N], sz[N];
int n, m, q, bl = 150, refl[N], g[N];
 
struct BIT {
	int n;
	vector <int> t;
 
	BIT () {}
	BIT (int n) : n (n), t (vector <int> (n + 1)) {}
 
	void update (int x, int d) {
		for (; x <= n; x = (x | (x + 1)))
			t[x] += d;
	}
 
	int get (int r) {
		int sum = 0;
 
		for (; r >= 0; r = (r & (r + 1)) - 1)
			sum += t[r];
 
		return sum;
	}
 
	int get (int l, int r) { return get (r) - get (l - 1); }
} t1 (N), t2 (N);
 
int find (Pt x) {
	return lower_bound (orde.begin(), orde.end(), make_pair (x,-1)) - orde.begin ();
}
 
void attack_to (int to) {
	for (int i : vs[to]) {
		int x = ords[i].second;
		if (!refl[x]) t2.update (find (pe[x]), 1);
	}
 
	for (int i = 0; i < n; i++) {
		int x = ords[i].second, tribe = g[x];
		int ind = find (pe[x]);
 
		if (tribe == to) {
			if (!refl[x]) t2.update (ind, -1);
			else t1.update (ind, 1);
			continue;		
		}
 
		if (qu[tribe].find (to) == qu[tribe].end ()) continue;
 
		qu[tribe][to] += t2.get (0, ind - 1) + t1.get (ind, n - 1);
	}
 
	for (int i : vs[to]) {
		int x = ords[i].second, cur = find (pe[x]);
		if (t1.get (cur, cur)) t1.update (cur, -1);
		if (t2.get (cur, cur)) t2.update (cur, -1);
	}
}
 
void attack_from (int from) {
	for (int i : vs[from]) {
		int x = ords[i].second;
		t2.update (find (pe[x]), 1);
	}
 
	for (int i = 0; i < n; i++) {
		int x = ords[i].second, tribe = g[x];
		int ind = find (pe[x]);
 
		if (tribe == from) {
			t1.update (ind, 1);
			t2.update (ind, -1);	
			continue;		
		}
 
		if (qu[from].find (tribe) == qu[from].end ()) continue;
 
		if (refl[x]) qu[from][tribe] += t2.get (0, ind - 1);
		else qu[from][tribe] += t1.get (ind, n - 1);
	}
 
	for (int i : vs[from]) {
		int x = ords[i].second, cur = find (pe[x]);
		if (t1.get (cur, cur)) t1.update (cur, -1);
		if (t2.get (cur, cur)) t2.update (cur, -1);
	}
}
 
int attack_small (int from, int to) {
	ll sum = 0;
 
	for (int i : vs[to]) {
		int x = ords[i].second;
		if (!refl[x]) {
			t2.update (find (pe[x]), 1);
		}
	}
 
	int j = 0;
 
	for (int i : vs[from]) {
		int x = ords[i].second;
		int ind = find (pe[x]);
 
		while (j < vs[to].size () && vs[to][j] < i) {
			int cur = ords[vs[to][j]].second;
			if (!refl[cur]) t2.update (find (pe[cur]), -1);
			else t1.update (find (pe[cur]), 1);
			j++;
		}
 
		sum += t1.get (ind, n - 1) + t2.get (0, ind - 1);
	}
 
	for (int i : vs[to]) {
		int x = ords[i].second, cur = find (pe[x]);
		if (t1.get (cur, cur)) t1.update (cur, -1);
		if (t2.get (cur, cur)) t2.update (cur, -1);
	}
 
	return sum;
}
 
int main () {
	cin >> n >> m;
 
	for (int i = 0; i < n; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		g[i] = c - 1;
		p[i] = Pt (a, b);
		sz[c-1]++;
	}
 
	int x, y;
 
	cin >> x >> y;
	s = Pt (x, y);
 
	cin >> x >> y;
	e = Pt (x, y);
 
	for (int i = 0; i < n; i++) {
		ps[i] = p[i] - s;
		pe[i] = p[i] - e;
		if (ps[i].cross (e - s) > 0) {
			refl[i] = 1;
			ps[i] = -ps[i], pe[i] = -pe[i];
		}
		orde.push_back ({pe[i], i});
		ords.push_back ({ps[i], i});
	}
 
	sort (ords.begin(), ords.end());
	sort (orde.begin(), orde.end());
 
	for (int i = 0; i < n; i++) {
		vs[g[ords[i].second]].push_back (i);
	}
 
	cin >> q;
 
	vector < pair <int, int> > e;
 
	for (int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		e.emplace_back (a, b);
 
		qu[a][b] = 0;
	}
 
	for (int i = 0; i < m; i++) {
		if (sz[i] > bl) {
			big[i] = 1;
			attack_from (i);
			attack_to (i);
		}
	}
 
	for (auto [a, b] : e) {
		if (!big[a] && !big[b]) cout << attack_small (a, b) << '\n';
		else if (big[a] && big[b]) cout << qu[a][b] / 2 << '\n';
		else cout << qu[a][b] << '\n';
	}
}
