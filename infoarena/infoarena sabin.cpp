	
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//For each group of strings a, b, c, d, ... let's add it in a trie in order a_0 b_0 c_0 ... a_1 b_1 c_1 d_1 ... Then from this
//trie we can find for a group the number of groups with similarity level at least k (f(k)), so the answer will be f(k) - f(k+1)
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, k, m, p, q;
string a[40000];
 
struct Trie {
	struct Node {
		int sum;
		map <char, Node*> to;
		Node () : sum (0) {}
	};
 
	Node* root;
 
	void insert (string& s) {
		auto x = root;
 
		for (int i = 0; i < s.length (); i++) {
			x -> sum++;
			if (x -> to.find (s[i]) == x -> to.end ()) x -> to[s[i]] = new Node ();
			x = x -> to[s[i]];
		}
		x -> sum++;
	}
 
	int find (string& s, string& add) {
		auto x = root;
 
		for (int i = 0; i < s.length (); i++) {
			if (x -> to.find (s[i]) == x -> to.end ()) return 0;
			x = x -> to[s[i]];
		}
 
		if (add.empty ()) return x -> sum;
		int ans = x -> sum;
		for (int i = 0; i < add.length (); i++) {
			if (x -> to.find (add[i]) == x -> to.end ()) return ans;
			x = x -> to[add[i]];	
		}
 
 
		return ans - (x -> sum);
	}
 
	Trie () : root (new Node ()) {}
} tr;
 
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	freopen ("sabin.in", "r", stdin);
	freopen ("sabin.out", "w", stdout);
	cin >> n >> k >> m >> p >> q;
 
	for (int i = 0; i < n; i++) {
		vector <string> v;
		for (int j = 0; j < k; j++) {
			string s;
			cin >> s;
			v.push_back (s);
		}
 
		string t;
 
		for (int j = 0; j < p; j++) {
			for (int f = 0; f < k; f++) {
				t += v[f][j];
			}
		}
 
		tr.insert (t);
	}
 
	for (int i = 0; i < m; i++) {
		cin >> a[i];
	}
 
	for (int i = 0; i < q; i++) {
		int t;
		cin >> t;
		vector <int> v;
 
		if (t > p) {
			cout << 0 << '\n';
			continue;
		}
 
		for (int i = 0; i < k; i++) {
			int x;
			cin >> x;
			v.push_back (x-1);
		}
 
		string st, ad;
 
		for (int j = 0; j < t; j++) {
			for (int f = 0; f < k; f++) {
				st += a[v[f]][j];
			}
		}
 
		if (t < p) {
			for (int f = 0; f < k; f++) {
				ad += a[v[f]][t];
			}	
		}
 
		cout << tr.find (st, ad) << '\n';
	}
}
