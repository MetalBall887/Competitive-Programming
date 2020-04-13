#include <bits/stdc++.h>
//By caseworking we can prove that each correct segment that has at least three blocks from each side can be extended. Thus,
//an optimal segment has either l <= 3 or n-3 <= r. Traverse each such segment.
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int a['Z'], b, c, n;
string s;

bool check () {
	if (!a['B']) return a['C'] != a['S'];
	if (!a['C']) return a['B'] != a['S'];
	if (!a['S']) return a['B'] != a['C'];
	return a['B'] != a['S'] && a['C'] != a['B'] && a['C'] != a['S'];
}

int main () {
	cin >> n;
	cin >> s;

	int ans = 0;

	for (int st = 0; st <= 3; st++) {
		a['B'] = a['S'] = a['C'] = 0;
		for (int i = st; i < n; i++) {
			a[s[i]]++;

			if (check ()) ans = max (ans, i - st + 1);
		}

		a['B'] = a['S'] = a['C'] = 0;
		for (int i = n - st - 1; i >= 0; i--) {
			a[s[i]]++;
			if (check ()) ans = max (ans, n - st - i);
		}
	}

	cout << ans;
}
