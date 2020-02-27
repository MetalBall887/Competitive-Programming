#include <bits/stdc++.h>
#include "grader.h"
#include "lang.h"
//Solution uses the relative frequence of different character sequences (up to 4 chars in a row) to occur. Sequences of higher lengths
//distinguish exact languages "better", so we add weight to them.
 
using namespace std;
 
int a[4][56][300000], b[4][300000];
int cnt[4][300000];
const int MOD = 299993;
 
void excerpt (int* E) {
    int n = 100;
    memset (cnt, 0, sizeof (cnt));
    std::vector <int> s[4];
    
    for (int i = 0; i < 100; i++) {
        int val = 1;
        for (int j = 0; j < min (4, n - i); j++) {
            val = val * E[i+j] % MOD;
            if (!cnt[j][val]) s[j].push_back (val);
            cnt[j][val]++;
        }
    }
    
    double mx = 0;
    int x = 0;
    
    for (int i = 0; i < 56; i++) {
        double points = 0;
        
        for (int k = 0; k < 4; k++) {
            for (int j : s[k]) {
                if (b[k][j]) points += cnt[k][j] * ((double) a[k][i][j] / b[k][j]) * (k + 1);
            }
        }
        
        if (mx < points) {
            mx = points;
            x = i;
        }
    }
    
    x = language (x);
    
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < min (4, n - i); j++) {
            int val = 1;
            for (int k = 0; k <= j; k++)
                val = val * E[i+k] % MOD;
            a[j][x][val]++;
            b[j][val]++;
        }
    }
}
