#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//The solution and the proof of its correctness are actually very tricky. First we will present an optimal algorithm, next we will find a set of lower bounds,
//show that the result of the solution is strictly equal to one of these bounds, thus it has to be the highest of them. 
//Let k be the fixed number of processors, d(x) is the distance from x to the deepest leaf in the subtree of x (let's call it depth of x), s(h) will be the 
//number of vertices with distant h from the root and finally r(t) will be the number of processors busy on t-th second. The optimal algorithm simply always takes
//the vertex with the highest depth available. For now let's prove the lemma: if with this algorithm r(t) < k, then after the second t all vertices on height <= t
//are already processed. It's proved by induction on height. Let it be true on any t' < t, assume r(t) < k, b is the smallest such that r(t-b) < k (note that
//t-b is at least 1). After second t-b all corresponding heights were processed. 
//Leaf lemma: Now from the greedy part of our algorithm flows that if all k vertices processed on second t-s (s < b) have depth at least s, there will be k 
//vertices on second t-s+1 with depth at least s-1 and so on until there will be k non-leaves on second t-1 and finally k vertices on second t. So it doesn't 
//happen with all s < b. Specially it means that there was at least one leaf processed on level t-1. Now assume for contradiction that there is a vertex on 
//level <=t processed in second >t. Then there is especially a vertex z on level <=t processed in second t+1. 
//Let's take his whole path of ancestors up to level t-b. x-th father of z will be on level <=t-x and will have depth at least x. From leaf lemma it goes that
//on second t-x there is at least one vertex with depth x-1, which means x-th father of z would be chosen to be processed on second t-x.
//
//   5  --  4  --  3  ---------  2 -- 1 -- z        chain of ancestors
// (t-5)--(t-4)--(t-3)--(t-2)--(t-1)--t--(t+1)      seconds they are processed at
//
//This means that as in the picture above if there is a "gap" like on second t-2 when none of ancestors was processed, it would have been "pulled up"
//
//   5  --  4  --  3  --  2  --  1 -- z             chain of ancestors
// (t-5)--(t-4)--(t-3)--(t-2)--(t-1)--t--(t+1)      seconds they are processed at
//
//So every vertex from the ancestor chain is processed right after the previous one. So if z is processed on second t+1, b times father of z is processed
//on second t-b+1 while being on the level t-b, which is the contractiction to our induction assumption. This means, there is no such z.
//
//Done with the hardest part.
//Let's bound the execution time. One of the bounds is the number of levels. The other bound is the number of vertices divided by the number of processors.
//Once combined, we get that for every level h time will be at least    h + ceil(sum(s(x), x > h)/k). Now for our algorithm above it's true that everytime
//r(t) < k, we are done with t levels. Now take the last t r(t) < k (except the absolutely latest second) as t_0 and we'll see that the running time will be
//t_0 + ceil(sum(s(x), x > t_0)/k), which is a close tie for our bound when h=t_0. But since our running time is at least all of these bounds and for one of
//them it's equality, this one bound is maximal. We need to find such h h + ceil(sum(s(x), x > h)/k) is maximal.
//
//h + ceil(sum(s(x), x > h)/k) = ceil((kh + sum(s(x), x > h)) / k), so we maximize hk + sum(s(x), x > h), which is done by convex hull trick.

using namespace __gnu_pbds;
 
using namespace std;
 
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
 
const ll N = 2000001;
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const ll maxk = 1e6;

struct line {
	int k, b;

	ll operator()(int x) {
		return (ll) k * x + b;
	}
};

bool bad(line a, line b, line c) {
	return (ll) (c.b - a.b) * (a.k - b.k) < (ll) (b.b - a.b) * (a.k - c.k);
}

struct CHT : vector<line> {
	void append(line a) {
		while(size() > 1 && bad(at(size() - 2), at(size() - 1), a)) {
			pop_back();
		}

		push_back(a);
	}
} v;

int s[N], n, qu[N], m, h;
ll ans[N];
vector<int> g[N];

void dfs(int x, int p, int d) {
	s[d]++;
	h = max(h, d);

	for (int to : g[x]) {
		if (to == p) continue;
		dfs(to, x, d + 1);
	}
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		cin >> qu[i];
	}

	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;

		g[p-1].push_back(i);
	}

	dfs(0, -1, 1);

	int cnt = n;

	for (int i = 1; i <= h; i++) {
		cnt -= s[i];
		v.append({i, cnt});
	}

	int ptr = 0;

	for (int i = 1; i <= maxk; i++) {
		while (ptr + 1 < v.size() && v[ptr](i) < v[ptr + 1](i)) {
			ptr++;
		}

		ans[i] = (v[ptr](i) + i - 1) / i;
	}

	for (int i = 0; i < m; i++) {
		cout << ans[qu[i]] << ' ';
	}
}
