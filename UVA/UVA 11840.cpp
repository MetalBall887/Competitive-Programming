#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <map>
//First of all, let's try to win the game in one turn. We can do this, for example, when two X's are adjacent or have only one
//empty square between them. So we might assume there is no such thing in the further solution. We can divide the game on
//substrings of consequent empty squares, distinguishing X...X, ...X, X... cases for prefixes and suffixes and the empty string
//We know that they are independent, because whenever, two X's become adjacent, the game is over. Divide substrings with
//X's, not creating a possibility for an opponent to make three in a row. When you run out of such "safe" moves, the game
//is over.
#include <set>
#include <cstring>
#include <bitset>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const int INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int N = 1e4;

int d[N + 1][4], n, u[N + 1];

string s;

int main () {

	d[1][1] = 0;
	d[1][2] = 0;
	d[1][3] = 1;

	for (int i = 2; i <= N; i++) {
		int l, r;
		for (int z = 0; z < 4; z++) {
			l = (z >= 2 ? 2 : 0);
			r = ((z & 1) ? i - 2 : i);

			memset (u, 0, sizeof (u));
			for (int j = l; j < r; j++) {
				if (z == 0) u[d[j][1] ^ d[i - j - 1][2]] = 1;
				if (z == 1) u[d[j][1] ^ d[i - j - 1][3]] = 1;
				if (z == 2) u[d[j][3] ^ d[i - j - 1][2]] = 1;
				if (z == 3) u[d[j][3] ^ d[i - j - 1][3]] = 1;
			}
			for (int j = 0; j <= N; j++) {
				if (!u[j]) {
					d[i][z] = j;
					break;
				}
			}
		}
	}

	while (cin >> n && n) {
		cin >> s;
		int p = -1, ans = 0;
		bool win = false;

		for (int i = 0; i < s.length (); i++) {
			if (s[i] == 'X') {
				if (p < 0) {
					p = i;
					ans ^= d[i][1];
				}
				else {
					if (i - p < 3) win = true;
					else ans ^= d[i - p - 1][3];
					p = i;
				}
			}
		}

		if (p >= 0) ans ^= d[n - 1 - p][2];
		else ans = d[n][0];


		if (win || ans) cout << "S\n";
		else cout << "N\n";
	}
}
