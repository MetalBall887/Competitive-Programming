#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
//https://img.atcoder.jp/agc031/editorial.pdf
#include <vector>
#include <string>
#include <bitset>
#include <math.h>
#include <queue>
#include <stack>
#include <set>
#include <map>
 
typedef long long ll;
typedef long double ld;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;
int n, k;

vector <int> d[1000000];

vector <int> f (vector <int> a, vector <int> b)
{
	vector<int> v (n);

	for (int i = 0; i < n; i++)
		v[i] = a[b[i] - 1];

	return v;
}

vector <int> inv (vector <int> a)
{
	vector <int> s (n);

	for (int i = 0; i < n; i++)
		s[a[i] - 1] = i + 1;

	return s;
}

vector <int> qpow (vector <int> a, int b)
{
	vector <int> s;

	for (int i = 0; i < n; i++)
		s.push_back (i + 1);

	while (b)
	{
		if (b & 1) s = f (s, a);
		a = f (a, a);
		b /= 2;
	}

	return s;
}

int main ()
{
	cin >> n >> k;

	vector <int> p (n), q (n);

	for (int i = 0; i < n; i++)
		scanf ("%d", &p[i]);

	for (int i = 0; i < n; i++)
		scanf ("%d", &q[i]);

	auto A = qpow (f (q, f (inv (p), f (inv (q), p))), (k - 1) / 6);

	if(k % 6 == 4) A = f (A, q);
	if(k % 6 == 5 || k % 6 == 0) A = f (A, f (q, inv (p)));

	vector <int> B[7];

	B[1] = p;
	B[2] = q;
	B[3] = f (q, inv (p));
	B[4] = inv (p);
	B[5] = inv (q);
	B[6] = f (inv (q), p);

	auto ans = f (A, f (B[(k - 1) % 6 + 1], inv (A)));

	for (int i = 0; i < n; i++)
		printf("%d ",ans[i]);
}
