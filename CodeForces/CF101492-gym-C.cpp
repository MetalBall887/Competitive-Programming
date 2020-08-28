#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//First, let's try to solve a smaller problem: for a given set of numbers S and a number x find the number of elements in S coprime to x. It's |S| - # of not
//coprimes. We can find the latter with the application of the principal of inclusion-exlusion called Mobius function: for some pairwise distinct prime numbers 
//d1,d2,d3,...,dn if x is divided by all of them and there are some elements from S that are divided by them, then their gcd will have these numbers in its 
//factorization. We can easily maintain a structure that tells us how many elements from S are divided by some number, so we can answer how many elements in S
//have d1,d2,d3,...,db in its gcd with x's factorization. Use PIE to find out he number of elements that have at least some prime in the gcd's factorization.
//Now we can answer the query for x in O(#divisors of x). With this technique we can maintain a range that knows the number of coprime pairs in it and add a 
//number or delete by doing the reverse to addition. Now we can apply Mo's algorithm.

//using namespace __gnu_pbds;
 
#define N 1000000
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int cnt[N], mu[N], n, m, a[N], ans[N];
 
ll sum;
 
struct query {
	int l, r, id;
};
 
vector <int> dv[N];
 
void add (int x) {
	for (auto d : dv[x]) {
		sum += (ll) mu[d] * cnt[d];
		cnt[d]++;
	}
}
 
void remove (int x) {
 
	for (auto d : dv[x]) {
		cnt[d]--;
		sum -= (ll) mu[d] * cnt[d];
	}
}
 
int er[N], sq = 200;
 
bool comp (query a, query b) {
	if (a.l / sq == b.l / sq) return a.r < b.r;
	return a.l < b.l;
}
 
int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
 
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
 
	fill (mu, mu + 500000, -1);
 
	for (int i = 2; i <= 500000; i++) {
		if (er[i]) continue;
		for (int j = i; j <= 500000; j += i) {
			er[j] = 1;
			if (j / i % i == 0) mu[j] = 0;
			else mu[j] = -mu[j];
		}
	}
 
	for (int i = 2; i <= 500000; i++) {
		if (!mu[i]) continue;
		for (int j = i; j <= 500000; j += i)
			dv[j].push_back (i);
	}
 
	vector<query> q;
 
	for (int i = 0; i < m; i++) {
		int l, r;
		cin >> l >> r;
		l--, r--;
 
		q.push_back ({l, r, i});
	}
 
	sort (q.begin(), q.end(), comp);
 
	int l = 0, r = -1;
 
	for (auto x : q) {
		while (r < x.r) add (a[++r]);
		while (x.l < l) add (a[--l]);
		while (x.r < r) remove (a[r--]);
		while (l < x.l) remove (a[l++]);
 
		ll len = r - l + 1;
 
		if (len * (len - 1) / 2 - sum > 0) ans[x.id] = 1;
	}
 
	for (int i = 0; i < m; i++) {
		if (ans[i]) cout << "S\n";
		else cout << "N\n";
	}
 
}
