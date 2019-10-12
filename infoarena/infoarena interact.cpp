#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//To quickly find the first place, we'll keep a sorted array A. What is A? Pretend we know the rest of actual string. Then for every
//unique character leave only the first one. for example, from badacbabc we'll leave only (b)(a)(d)a(c)abc -> badc. First character
//in A will be the next character in string. So after we added this element to our prefix, we should find out where will it be (in
//our example b will move from the first position to the last). Since othere characters are sorted relevantly each other, we can do
//a binary search on them, where we check in bs iteration, if the next our current character is before the next key character.
//We can do this if we form a string where first it will be our current prefix, then the current character, then all remaining
//key characters. If current character is before, this string will fully be in the password.
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n, s, cnt[26], sorted[26], c[100][100];

string cur;

int query (string s) {
	int l;
	cout << "? " << s << endl;
	fflush (stdout);
	cin >> l;
	return l;
}

bool comp (int a, int b) {
	if (a == b) return false;
	string s = cur;
	s += char (a + 'a');
	for (int i = 0; i < cnt[b]; i++)
		s += char (b + 'a');
	if (s.length () > n) return false;
	return query (s);
}

bool C (int a, int b) {
	return c[a][b];
}

int main () {
	s = 26;

	for (int i = 0; i < s; i++){
		for (int k = 1; 1; k++) {
			string s;
			for (int j = 0; j < k; j++)
				s += char (i + 'a');
			if (query (s)) cnt[i] = k;
			else break;
		}
		n += cnt[i];
	}	

	for (int i = 0; i < s; i++)
		for (int j = 0; j < s; j++)
			if (cnt[i] && i != j && comp (i, j))
				c[i][j] = 1;

	for (int i = 0; i < s; i++)
		sorted[i] = i;

	sort (sorted, sorted + s, C);

	for (int i = 0; i < n; i++) {
		int x = sorted[0];
		cnt[x]--;
		cur += char (x + 'a');

		int l = 0, r = s - 1;

		while (l < r) {
			int mid = (l + r + 1) / 2;

			if (comp (sorted[0], sorted[mid])) r = mid - 1;
			else l = mid;
		}

		for (int j = 0; j < l; j++)
			sorted[j] = sorted[j + 1];

		sorted[l] = x;
	}

	cout << "! " << cur << endl;
	fflush (stdout);
}
