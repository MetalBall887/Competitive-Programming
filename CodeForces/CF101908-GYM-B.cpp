#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <map>
//The important idea of this problem can be derived from chess. That is, in some chess games on computers, when your king
//is under a "check", turns that will not protect the king are not presented and you can't choose them. That's because
//in any game a turn that directly makes you lose is the same as not having that possiblility at all, since losing is ne turn
//is always better than everything else. So moving any rock to a x = 0, y = 0 or x = y is the same as instantly losing all
//the matches at once, so we pretend there is no such possible turn at all and if there is only such turns, we tell that there
//are no turns left and this independent game is lost. If all games are lost, you have to do the move with "checkmate" position.
//so the game is a nim with some positions removed without the loss of optimality. On the other hand, when there is already a game
//with such position, we instantly win in the first turn.
#include <set>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const int INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int N = 1e6;
 
int d[101][101], n;
 
int calc_mex (vector <int> s) {
    sort (s.begin (), s.end ());
 
    if (s.empty () || s[0]) return 0;
 
    for (int i = 1; i < s.size (); i++) {
        if (s[i-1] + 1 < s[i]) return s[i-1] + 1;
    }
 
    return s.back () + 1;
}
 
int main () {
    cin >> n;
 
    for (int i = 0; i <= 100; i++)
        for (int j = 0; j <= 100; j++) {
            vector <int> v;
            for (int k = 1; k <= max (i, j); k++) {
                if (i > k && i - k != j) v.push_back (d[i-k][j]);
                if (j > k && i != j - k) v.push_back (d[i][j-k]);
                if (i > k && j > k && i != j) v.push_back (d[i-k][j-k]);
            }
 
            d[i][j] = calc_mex (v);
        }
 
    int ans = 0, k = 0;
 
    for (int i = 0; i < n; i++) {
        int l, c;
        cin >> l >> c;
        if (l == c || l == 0 || c == 0) k = 1;
        ans ^= d[l][c];
    }
    
    if (k) ans = 1;
 
    if (ans) cout << "Y";
    else cout << "N";
}
