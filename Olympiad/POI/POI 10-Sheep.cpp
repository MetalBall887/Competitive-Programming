#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <algorithm>
//dp[l][r] - the number if ways to divide the area from l to r in clockwise order with triangles. We can check l < j < r
//so we are trying to add a triangle with vertices in fence points l, j, r. We can similarly initialize partial sum
//to then effectively calculate the number of sheeps inside a triangle. Instead of radial sort, which is slowed, we can for
//each sheep and fence node the clockwisely closest segment to this sheep, then apply prefix sum on it.
#include <vector>
#include <math.h>
#include <set>
 
using namespace std;
 
string s;
 
typedef long long ll;
 
int n, dp[600][600], lies[600][600], psum[600][600], K, m;
 
struct point {
    int x, y;
} p[1000], a[100000];
 
int area (point s, point a, point b) {
    return (s.x * a.y + a.x * b.y + b.x * s.y) - (a.x * s.y + b.x * a.y + s.x * b.y);
}
 
bool on_one_line (point s, point a, point b) {
    return area (s, a, b) == 0;
}
 
int main () {
    cin >> n >> K >> m;
 
    for (int i = 0; i < n; i++)
        scanf ("%d%d", &p[i].x, &p[i].y);
    for (int i = 0; i < K; i++)
        scanf ("%d%d", &a[i].x, &a[i].y);
 
    for (int i = 0; i < K; i++) {
        int r = 1;
        for (int l = 0; l < n; l++) {
            while (l == r || area (p[l], a[i], p[r]) > 0) {
                r++;
                if (r == n) r = 0;
            }
 
            if (on_one_line (p[l], a[i], p[r])) {
                lies[l][r] = true;
            }
            psum[l][r]++;
        }
    }
 
    for (int i = 0; i < n; i++)
        for (int j = 1; j < n; j++)
                psum[i][(i + j) % n] += psum[i][(i + j - 1) % n];
 
    for (int i = 0; i < n; i++)
        dp[i][(i + 1) % n] = 1;
 
 
    for (int k = 2; k < n; k++)
        for (int i = 0; i < n; i++) {
            if (lies[i][(i + k) % n]) dp[i][(i + k) % n] = 0;
            else {
                for (int j = i + 1; j < i + k; j++) {
                    int s = K - psum[i][j % n] - psum[j % n][(i + k) % n] - psum[(i + k) % n][i];
 
                    if ((s & 1) == 0)
                        dp[i][(i + k) % n] += dp[i][j % n] * dp[j % n][(i + k) % n] % m;
                    if (dp[i][(i + k) % n] >= m) dp[i][(i + k) % n] -= m;
                }
            }
        }
 
    cout << dp[0][n-1];
}
