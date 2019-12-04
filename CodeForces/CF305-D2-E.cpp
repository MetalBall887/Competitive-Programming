#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <map>
#include <map>
//What does "the cut" do? If it was performed from one side, the character from
//the other side will not be a palindrome center anymore. So consequent palindrome
//centers change each other and non-consequent ones are completely independent
//That way, we divide the string to the set of strings with consequent palindrome centers and
//at this point the game is identical and independent for all of them. We can precompute
//for each string of consequent palindrome centers the Sprague-Grundy number and
//play a nim
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

int n, d[N];
string s;

int calc_mex (vector <int>& v) {
    sort (v.begin (), v.end ());

    if (v[0]) return 0;

    for (int i = 1; i < v.size (); i++) {
        if (v[i-1] + 1 < v[i]) return v[i-1] + 1;
    }

    return v.back () + 1;
}

int solve (string& s) {
    vector <int> v;
    int n = s.length ();

    int l = 1;

    for (int i = 1; i < n - 1; i++) {
        if (s[i-1] != s[i+1]) {
            v.push_back (i - l);
            l = i + 1;
        }
    }

    v.push_back (n - 1 - l);

    int ans = 0;

    for (int l : v) {
        ans ^= d[l];
    }

    return ans;
}

int main () {
    cin >> s;

    s = s;
    n = s.length ();
    for (int i = 1; i <= s.length (); i++) {
        vector <int> v;
        for (int j = 0; j < i; j++) {
            v.push_back (d[max (0, j - 1)] ^ d[max (0, i - j - 2)]);
        }

        d[i] = calc_mex (v);
    }

    if (solve (s)) {
        int mn = -1;
        cout << "First\n";

        for (int i = 1; i < n - 1; i++) {
            if (s[i-1] != s[i+1]) continue;
            string pr, sf;
            for (int j = 0; j < i; j++)
                pr += s[j];

            for (int j = i + 1; j < n; j++)
                sf += s[j];

            if (solve (pr) == solve (sf)) {
                cout << i + 1;
                return 0;
            }
        }
    }
    else cout << "Second";
}
