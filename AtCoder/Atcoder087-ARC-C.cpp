#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string.h>
//https://img.atcoder.jp/arc087/editorial.pdf
#include <cstdlib>
#include <vector>
#include <string>
#include <bitset>
#include <math.h>
#include <queue>
#include <stack>
#include <set>
#include <map>
 
typedef long long ll;
typedef long double ld;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;
ll l;
 
ll grundy (ll height)
{
	return (height & (-height));
}
 
struct Node
{
	bool leaf;
	Node* to[2];
 
	Node ()
	{
		leaf = false;
		to[0] = to[1] = NULL;
	}
};
 
Node* root;
 
int n, ptr;
ll s;
 
void add (string s)
{
	auto x = root;
	for (int i = 0; i < s.length (); i++)
	{
		if (!x -> to[s[i] - '0']) x -> to[s[i] - '0'] = new Node ();
		x = x -> to[s[i] - '0'];
	}
 
	x -> leaf = true;
}
 
void dfs (Node* x, ll h)
{
	if (!x) s ^= grundy (h);
	else
	{
		dfs (x -> to[0], h - 1);
		dfs (x -> to[1], h - 1);
	}
}
 
int main ()
{
	root = new Node ();
 
	cin >> n >> l;
 
	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
 
		add (s);
	}
 
	dfs (root, l + 1);
 
	if (!s || !n) cout << "Bob";
	else cout << "Alice";
}
