#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//let's consider i-th line of this rectangle. By going from top to bottom for each line we can contain the length of 
//1's subsegment going to (i, j) in O(NM). So on i-th line we can sort columns by this value and go from the biggest one.
//For j-th column in sorted sequence we know that all columns before them have height of "tower" of 1's more or equal to
//current one, so if j-th column has height of tower hj and it's the rightmost in the sequence with such height, we can
//see that rectangle of first j columns will have a height hj and will be the biggest rectangle with height hj on this line
//by going through all heights like this we'll eventually find the biggest rectangle with lowest point on line i. Now how
//to keep it sorted. We can notice that while going from up to bottom order either stays unchanged or one of the elements
//becomes 0 and moves to the end of the sorted sequence. That means, we move elements only to the end of the sequence,
//and that allows us keep arrays sorted in O(NM).
#include <set>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

vector <pair <int, int> > cur, t;
vector <int> zeroes;

int n, m, best, p[10000];

string s;

int main () {
	ios_base::sync_with_stdio(false); 
    cin.tie(NULL);   
	memset (p, -1, sizeof (p));
	cin >> n >> m;

	for (int i = 0; i < m; i++)
		cur.emplace_back (-1, i);

	for (int i = 0; i < n; i++) {
		vector < pair <int, int> > t;
		cin >> s;

		for (int j = 0; j < m; j++) {
			if (s[j] == '0') {
				p[j] = i;
			}
		}

		for (auto a : cur) {
			if (p[a.second] == a.first)
				t.push_back (a);
		}
		cur = t;

		for (int j = 0; j < m; j++) {
				if (p[j] == i) cur.push_back ({i, j});
		}

		for (int j = 0; j < m; j++) {
			best = max (best, (j + 1) * (i - cur[j].first));
		}
	}

	cout << best;
}
