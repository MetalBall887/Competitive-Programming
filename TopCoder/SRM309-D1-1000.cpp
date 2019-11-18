#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
//The key of the game is to consider differences between all neighboring pairs instead. Reducing one of the elements will
//decrease the difference up to 0, while the difference on the right will increase by the same amount. Reminds of staircase nim
//We can reverse the array of differences, add the "infinity" in the beginning and play staircase nim. The number of different
//moves is not large, so we can try all of them and output the minimal winning
#include <map>
#include <unordered_map>
#include <set>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>

#define N 1000000

using namespace std;

typedef long long ll;

const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

class StoneGameStrategist {
    string to_string (int x) {
        string s;

        while (x) {
            s += char (x % 10 + '0');
            x /= 10;
        }

        reverse (s.begin (), s.end ());

        return s;
    }

    bool is_winning (vector <int> d) {
        vector <int> a;
        int n = d.size ();
        for (int i = 0; i < n; i++) {
            if (i) a.push_back (d[i] - d[i+1]);
            else a.push_back (d[i]);
        }

        a.push_back (INF);

        reverse (a.begin (), a.end ());

        int xr = 0;

        for (int i = 1; i <= n; i += 2) {
            xr ^= a[i];
        }

        return xr;
    }
public:
    string play (vector <int> piles) {
        int n = piles.size ();
        if (!is_winning (piles)) return "YOU LOSE";

        pair <int, int> best = {INF, INF};

        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= piles[i]) {
                piles[i] -= j;
                if (can_win (piles)) best = min (best, make_pair (j, i));
            }
        }

        string ans = "TAKE " + to_string (best.first) + " STONES FROM PILE "
         + to_string (best.second);

        return ans;
    }
}
