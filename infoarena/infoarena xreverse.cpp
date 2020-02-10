#include <bits/stdc++.h>
//The basic approach for this problem is to define d[i][j][k] - the sum or the number of numbers of length i such that those
//numbers % K is j and reverse(those numbers) % K is k. Unforutnately it's too slow for this solution. But we can ovserve
//that for each d[i] and d[j] we can find d[i+j] in O(K^4). That means, we can apply d&c approach on N, divide it onto two
//halfs, solve each half recursively. That way the complexity of solution is O(K^4logN).
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, k, m, md[N], p[N], p2[N];
 
struct state {
	ll l;
	vector <vector <ll>> cnt, sum;
	state () : l (0) {
		cnt.resize (k);
		for (auto& v : cnt)
			v.resize (k);
 
		sum.resize (k);
		for (auto& v : sum)
			v.resize (k);
	}
 
	state (int n) : l (n) {
		cnt.resize (k);
		for (auto& v : cnt)
			v.resize (k);
 
		sum.resize (k);
		for (auto& v : sum)
			v.resize (k);
	}
};
 
state merge (state a, state b) {
	state s (a.l + b.l);
	for (int i1 = 0; i1 < k; i1++)
		for (int j1 = 0; j1 < k; j1++) {
			if (!a.cnt[i1][j1] && !a.sum[i1][j1]) continue;
			for (int i2 = 0; i2 < k; i2++)
				for (int j2 = 0; j2 < k; j2++) {
					if (!b.cnt[i2][j2] && !b.sum[i2][j2]) continue;
					int new_i = md[i1 * p[b.l] + i2];
					int new_j = md[j2 * p[a.l] + j1];
					assert (new_i < k && new_j < k);
					s.cnt[new_i][new_j] += a.cnt[i1][j1] * b.cnt[i2][j2] % m;
					s.sum[new_i][new_j] += (b.sum[i2][j2] * a.cnt[i1][j1] + a.sum[i1][j1] * p2[b.l] * b.cnt[i2][j2]) % m;
					if (s.sum[new_i][new_j] >= m) s.sum[new_i][new_j] -= m;
					if (s.cnt[new_i][new_j] >= m) s.cnt[new_i][new_j] -= m;
				}
		}
	return s;
}
 
map <int, state> d;
 
state Rec (int n) {
	if (d.count (n)) return d[n];
	if (n & 1) {
		auto a = merge (Rec (n / 2), Rec (1));
 
		return d[n] = merge (a, Rec (n / 2));
	}
 
	return d[n] = merge (Rec (n / 2), Rec (n / 2));
}
 
int main () {
	freopen ("xreverse.in", "r", stdin);
	freopen ("xreverse.out", "w", stdout);
	cin >> n >> k >> m;
	
	p[0] = p2[0] = 1;
	for (int i = 1; i < N; i++) {
		md[i] = (i >= k ? md[i-k] : i);
		p[i] = p[i-1] * 10 % k;
		p2[i] = p2[i-1] * 10 % m;
	}
 
 
	d[1].l = 1;
	for (int i = 1; i < 10; i++) {
		d[1].cnt[i % k][i % k]++;
		d[1].sum[i % k][i % k] += i;
	}
 
	state c = Rec (n);
	cout << c.sum[0][0];
}
