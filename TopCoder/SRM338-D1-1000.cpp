#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <set>
//Let's keep an invariant for the first player. If the number of maximums is odd, we always can make it even. If the number
//maximums is even, you will have to make it odd. Corner case for odd maximums is one. Then find the number of second 
//maximums: if it's odd, we can make one of the maximum the second maximums, if it's even, make it less than second 
//maximum. Finding lexicographically minimum, we always take a cake with lexicographically minimal index and and taking
//lexicographical minimum between two numbers can be found in O(1).
#include <bitset>
#include <cstring>
#include <map>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <queue>

#define N 1000000
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 2;

class CakeParty {

	string to_ll (ll x) {
		string s = "";
		
		if (!x) return "0";

		while (x) {
			s += char (x % 10 + '0');
			x /= 10;
		}

		reverse (s.begin (), s.end ());

		return s;
	}

	string find_min (int a, int b) {
		string sa = to_ll (a);
		string sb = to_ll (b);

		if (sa.length () == sb.length ()) return sa;

		string cand1 = sa;

		string cand2 = "1";

		for (int i = 0; i < sa.length (); i++)
			cand2 += "0";
		return min (cand1, cand2);
	}
public:
	string makeMove (vector <int> piece) {
		ll mx = 0, fst, cnt = 0;
		for (ll i = 0; i < piece.size (); i++) {
			ll x = piece[i];
			if (x > mx) {
				mx = x;
				fst = i;
				cnt = 0;
			}
			cnt += (mx == x);
		}

		ll smx = 0, scnt = 1;

		for (ll i = 0; i < piece.size (); i++) {
			ll x = piece[i];
			if (x == mx) continue;
			if (x > smx) {
				smx = x;
				scnt = 0;
			}
			if (x == smx) scnt++;
		}

		string p;

		string c = to_ll (fst);
		
		vector <string> s;
		for (ll i = 0; i < piece.size (); i++) {
			if (piece[i] == mx)
				s.push_back (to_ll (i));
		}

		sort (s.begin(), s.end());
		c = s[0];

		if (cnt == 1 && scnt & 1) p = to_ll (mx - smx);
		else if (cnt == 1) p = find_min (mx - smx + 1, mx);
		else if (cnt & 1) p = "1";
		else p = "1";

		string ans = "CAKE " + c + " PIECES " + p;
		
		return ans;
	}
};
