#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Note that we can write all rules in the implication graph from 2-SAT algorithm (basically for i there are two vertices "s[i] is consonant" and "s[i] is vowel")
//and check the correctness of these rules. If rules don't contain contradictions, there is at least one string that satisfies them. To add a rule "s[i] should be
//consonant" we can simply add an edge "s[i] is vowel" => "s[i] is consonant" which is automatically false is s[i] is vowel. And then we're greedily trying to
//find the lexicographically closest string first by making the common prefix be as long as it's possible, then, if at some point it would be impossible, decrease
//it until there is a character at the end of the prefix which you can increase and the string that has this prefix and satisfies the rule will appear. This
//character will be the first bigger than in the actual string. After this character, find the smallest string satisfying rule greedily (if 'a' is consonant, try
//putting consonant, if worked, move on, if didn't, put the smallest vowel and move on).
 
using namespace __gnu_pbds;
 
#define N 1000000
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int M = 1e6;
 
vector <int> g[N], gt[N], t;
bitset <N> u;
 
int n, m, c[N], cnt;
 
void topsort (int x) {
	u[x] = 1;
	for (int to : g[x]) {
		if (!u[to]) topsort (to);
	}
 
	t.push_back (x);
}
 
void scc (int x, int col) {
	c[x] = col;
	for (int to : gt[x]) {
		if (!c[to]) scc (to, col);
	}
}
 
bool check_sat () {
	fill (gt, gt + 2 * n, vector <int> ());
	u.reset ();
	t.clear ();
 
	fill (c, c + 2 * n, 0);
 
	for (int i = 0; i < 2 * n; i++)
		for (int to : g[i]) {
			gt[to].push_back (i);
		}
 
	for (int i = 0; i < 2 * n; i++)
		if (!u[i]) topsort (i);
 
	reverse (t.begin(), t.end());
 
	int col = 1;
 
	for (int i = 0; i < 2 * n; i++)
		if (!c[t[i]]) scc (t[i], col++);
 
	for (int i = 0; i < n; i++)
		if (c[2 * i] == c[2 * i + 1]) return false;
	return true;
}
 
string a, s;
 
int v[200], min_c[200], min_v[200];
 
bool try_set (int x, int c) {
	char old = s[x];
	g[2 * x + !c].push_back (2 * x + c);
	if (check_sat ()) {
		if ((c ? min_c[s[x]] : min_v[s[x]]) == a.size () + 'a') {
			g[2 * x + !c].pop_back ();
			s[x] = old;
			return false;
		}
		s[x] = (c ? min_c[s[x]] : min_v[s[x]]);
		return true;
	} else {
		g[2 * x + !c].pop_back ();
		return false;
	}
}
 
int main () {
	cin >> a;
 
	for (int i = 0; i < a.size (); i++) {
		v[i + 'a'] = (a[i] == 'C');
	}
 
	min_c[a.size () + 'a'] = min_v[a.size () + 'a'] = a.size () + 'a';
 
	for (int i = 'a' + a.size () - 1; i >= 'a'; i--) {
		min_c[i] = min_c[i+1];
		min_v[i] = min_v[i+1];
		if (a[i - 'a'] == 'C') min_c[i] = i;
		else min_v[i] = i;
	}
 
	cin >> n >> m;
 
	for (int i = 0; i < m; i++) {
		string a, b;
		int posa, posb;
		cin >> posa >> a >> posb >> b;
		posa--, posb--;
 
		int sa = (a == "C"), sb = (b == "C");
 
		g[2 * posa + sa].push_back (2 * posb + sb);
		g[2 * posb + !sb].push_back (2 * posa + !sa);
	}
 
	cin >> s;
 
	if (max (min_v['a'], min_c['a']) == a.size () + 'a') {
		if (min_c['a'] == a.size () + 'a') {
			for (int i = 0; i < n; i++) {
				g[2 * i + 1].push_back (2 * i);
			}
		} else {
			for (int i = 0; i < n; i++) {
				g[2 * i].push_back (2 * i + 1);
			}
		}
 
		if (check_sat ()) cout << s;
		else cout << -1;
		return 0;
	}
 
	if (!check_sat ()) {
		cout << -1;
		return 0;
	}
 
	int ptr = n;
 
	for (int i = 0; i < n; i++) {
		char old_s = s[i];
		if (!try_set (i, v[s[i]]) || s[i] != old_s) {
			ptr = -1;
			for (int j = i; j >= 0; j--) {
				if (j != i) g[2 * j + !v[s[j]]].pop_back ();
				s[j]++;
				int k = 0;
				if (min_c[s[j]] < min_v[s[j]]) k = !k;
				if (try_set (j, k) || try_set (j, !k)) {
					ptr = j + 1;
					break;
				}
			}
 
			break;
		}
	}
 
	if (ptr == -1) {
		cout << -1;
		return 0;
	}
	for (int i = ptr; i < n; i++) {
		int k = 0;
		s[i] = 'a';
		if (min_c[s[i]] < min_v[s[i]]) k = !k;
		if (!try_set (i, k)) try_set (i, !k);
	}
 
	cout << s;
}
