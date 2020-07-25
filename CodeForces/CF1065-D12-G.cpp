#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Finding the k-th lexicografically smallest string out of all suffixes of a string is equivalent to finding k-th vertex in lexicographic in-order dfs traversal
//of the suffix array of the corresponding string. Since each vertex in the suffix tree will have at most two children (only '0' and '1'), we can look at the
//size of the left subtree and decide whether we go there or skip all these vertices and go to the right. Of course the suffix tree for F(x) will be too big
//but we can use the fact that the size of the subtree rooted in vertex x is the number of occurences of the string defined by the path from the root to x in
//F(x) and a good way to count the number of occurences in a small string for a big string is KMP. Let p be a state of KMP automaton on a string-path from root
//to current vertex x ("needle"), A[p][x] is a state, where KMP automaton will stop if we process F(x) ("hay"). A[p][x] = A[A[p][x-2]][[x-1]] since F(x) = F(x-2) 
//+ F(x-1). If C[p][x] is the same but instead of the state we count the number of times we visited "the last" state of automaton meaning we hit the occurence of 
//a "needle", then C[p][x] = C[p][x-2] + C[A[p][x-2]][x-1]. Our answer is C[0][n], the number of occurnces of the needle in F(n). With that in O(nm) we always
//can find a size of a special subtree and since we need only first m positions, we need to descend in lexicographic search only m times, which makes the solution
//work in O(nm^2)
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int f[201][201];
ll sm[201][201];
 
ll kmp (int x, string s) {
	int sz = s.length ();
 
	vector <int> p (sz);
 
	for (int i = 1; i < sz; i++) {
		int j = p[i-1];
		while (j && s[j] != s[i]) j = p[j-1];
		p[i] = j + (s[j] == s[i]);
	}
 
	f[0][0] = f[0][1] = 0;
	f[0][s[0] - '0'] = 1;
 
	for (int i = 1; i <= sz; i++) {
		if (i < sz && s[i] == '0') f[i][0] = i + 1;
		else f[i][0] = f[p[i-1]][0];
	}
 
	for (int i = 1; i <= sz; i++) {
		if (i < sz && s[i] == '1') f[i][1] = i + 1;
		else f[i][1] = f[p[i-1]][1];
	}
 
	for (int i = 0; i <= sz; i++) {
		sm[i][0] = sm[i][1] = 0;
		if (f[i][0] == sz) sm[i][0] = 1;
		if (f[i][1] == sz) sm[i][1] = 1;
	}
 
	for (int k = 2; k <= x; k++) {
		for (int i = 0; i <= sz; i++) {
			f[i][k] = f[f[i][k-2]][k-1];
			sm[i][k] = sm[i][k-2] + sm[f[i][k-2]][k-1];
			sm[i][k] = min (sm[i][k], INF);
		}
	}
 
	return sm[0][x];
}
 
int main () {
	int n, m;
	ll k;
	cin >> n >> k >> m;
	ll last_x = kmp (n, "0") + kmp (n, "1");
 
	string s;
 
	for (int i = 0; i < m; i++) {
		ll x0 = kmp (n, s + '0');
		ll x1 = kmp (n, s + '1');
 
		if (last_x != x0 + x1) {
			if (k == 1) break;
			else k--;
		}
 
		if (x0 >= k) {
			s += '0';
			last_x = x0;
		} else {
			s += '1';
			k -= x0;
			last_x = x1;
		}
	}
 
	cout << s << endl;
}
