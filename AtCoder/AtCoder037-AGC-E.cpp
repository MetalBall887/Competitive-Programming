#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//Idea is,
//we can iterate through all possible first moves, last element in the resulting string will be the first one in final string.
//Of course, if there is a result of first operation where last character is less than the one we are processing, or the length
//of consequent substring of identical last elements is longer, then the result is not optimal. After this small filtering we can
//find that the best thing we can do in moves 2...k is to double the number of last characters' substrings.
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

string s;

int n, k;

string process (string s) {

	if (k == 1) return s;
	int l;
	for (l = 1; l <= n && s[n - l] == s.back (); l++);
	l--;
	
	ll p;

	if (k - 1 >= 13) p = n;
	else p = min ((1 << (k - 1)) * l, n);

	string t;

	for (int i = p - l; i < n; i++)
		t += s[i];

	for (int i = 0; i < p - l; i++)
		t += s.back ();

	reverse (t.begin(), t.end());

	return t;
}

int main () {
	cin >> n >> k;

	cin >> s;

	string best = s;

	string rev_s = s;

	reverse (rev_s.begin(), rev_s.end());

	s = s + rev_s;

	for (int i = 0; i <= s.size () / 2; i++) {
		best = min (process (s.substr (i, s.size () / 2)), best);
	}

	cout << best;
}
