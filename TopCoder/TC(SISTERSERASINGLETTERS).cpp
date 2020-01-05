#include <bits/stdc++.h>
//d[i][j][turn] - 1 is player turn (0 - first, 1 - second) wins if the leftmost erasable element is at position j, there 
//are i elements left in original sequence [0..j-1] and this sequence matches prefix s[0..i]. 
using namespace std;
 
const int N = 1e6;

struct SistersErasingLetters {
	int d[100][100][2], n;
	string s;


	int Move (int i, int j, int turn) {
		int& to = d[i][j][turn];
		if (j == n) return turn;
		if (to != -1) return to;

		to = !Move (i, j + 1, !turn);
		for (int k = 0; j + k < n - 1; k++) {
			if (s[i + k] != s[j + k]) {
				if (turn ^ (s[i + k] < s[j + k])) to = 1;
				break;
			}
			assert (i + k < n);
			to = max (to, 1 - Move (i + k + 1, j + k + 2, !turn));
		}

		return to;
	}

	string whoWins (string word) {
		s = word, n = word.length ();
		memset (d, -1, sizeof (d));

		if (Move (0, 0, 0)) return "Camomile";
		else return "Romashka";
	}
};
