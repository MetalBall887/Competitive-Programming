#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <map>
#include <fstream>
//Two strings can be in a sequence, when the left one is the prefix and the suffix of the next one
//That means, it should be the prefix of the next one and its reverse should be the prefix of reverse
//of the next one. We should check only the next one because being a prefix is transitive. So we
//construct a doubled string made of original and reversed string (i-th char is i-th char of the original
//string + n-i-1st char of the original string) and now we have to check only if the previous string in
//the subsequence is a prefix. We can traverse all such strings with a trie.
#include <set>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <queue>
 
#define N 2000000
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e15, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
struct Trie {
	struct Node {
		int d;
		map < pair <char, char>, Node* > to;
		bool leaf;

		Node () : d (0), leaf (false) {}
	};

	Node* root = new Node ();

	int add (string s) {
		string t = s;
		reverse (t.begin(), t.end());

		int d = 1;
		Node* x = root;

		for (int i = 0; i < s.length (); i++) {
			if (x -> to.find ({s[i], t[i]}) == x -> to.end ()) {
				x -> to[{s[i], t[i]}] = new Node ();
			}

			x = x -> to[{s[i], t[i]}];
			if (x -> leaf) d = max (d, x -> d + 1);
		}

		x -> leaf = true;
		x -> d = d;

		return d;
	}
} t;

bool comp (const string& a, const string& b) {
	return a.length () < b.length ();
}

int n;

string s;
 
int main () {
	cin >> n;

	int ans = 0;

	for (int i = 0; i < n; i++) {
		cin >> s;
	
		ans = max (ans, t.add (s));
	}

	cout << ans;
}
