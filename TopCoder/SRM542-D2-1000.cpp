#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//By the linearity of expectation the expected position of a string is a sum of probabilites of a=other strings to be higher in this list. For two strings we
//can determine this probability by iterating the first element of the permutation. That being said, the string s is lex. lower than string t in cases when 
//in the first index checked s has a lower character or if they're equal and in this case we proceed recursively to the second index. Note that the actual
//order doesn't matter, so we only need to keep track of indices where s has less, same or greater character. We can precompute this with dp.

using namespace __gnu_pbds;
 
#define N 1000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

struct StrangeDictionary {
	int d[51][51][51];
	vector <double> getExpectedPositions(vector <string> words) {
		vector <double> ans (words.size ());

		for (int l = 0; l <= 50; l++)
			for (int r = 0; r <= 50; r++) {
				d[l][0][r] = (double) l / (l + r);
				for (int m = 1; m <= 50 - l - r; m++) {
					d[l][m][r] = (double) l / (l + m + r) + 
								 (double) m / (l + m + r) * d[l][m-1][r];
				}
			}

		for (int i = 0; i < words.size (); i++)
			for (int j = 0; j < words.size (); j++) {
				if (i == j) continue;
				int l = 0, m = 0, r = 0;
				for (int k = 0; k < words[i].length (); k++) {
					if (words[i][k] < words[j][k]) l++;
					else if (words[i][k] == words[j][k]) m++;
					else r++;
				}

				ans[j] += d[l][m][r];
			}

		return ans;
	}
}
