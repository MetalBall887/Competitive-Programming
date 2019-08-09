#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <string>
//Consider a chess grid of a table. On black tiles we can put any numbers, on white ones, we can put lcm of all adjacent 
//numbers on black tiles + 1. That will satisfy the condition of modulo. Elements can be not distinct and can exceed the bound
//yet. To deal with both issues let's put primes by diagonals, so on d'th primes will be placed at cells (x, y) where x - y = d
//and n + d'th - where x + y = d. That way element in a cell is a cross of two lines, which can happen only once, so
//the any product of any two primes on this grid can appear at most once. Two diagonally adjacent elements have a common prime
//divisor, so lcm will be bounded by a product of 4 primes. Eventually, this number overall won't exceed the bound given in 
//statement.
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
 
ll er[1000001], p[1000000], ptr, n, d[1000][1000];
 
ll gcd (ll a, ll b)
{
	if (!b) return a;
	else return gcd (b, a % b);
}
 
int main ()
{
	for (ll i = 2; i <= 1000000; i++)
		if (!er[i])
		{
			p[ptr++] = i;
			for (ll j = i * i; j <= 1000000; j += i)
				er[j] = 1;
		}
 
	cin >> n;
 
	for (int i = 0; i < 2 * n; i += 2)
		for (int j = 0; i + j < 2 * n; j++)
			d[j][i + j] = p[i / 2];
 
 
	for (int i = 2; i < 2 * n; i += 2)
		for (int j = 0; i + j < 2 * n; j++)
			d[i + j][j] = p[i / 2 + (n + 1) / 2 - 1];
 
 
	for (int i = 0; i < 2 * n; i += 2)
		for (int j = 0; i >= j; j++)
			d[i - j][j] *= p[i / 2 + n];
 
	ll mx = 0;
 
	if (n == 2)
	{
		printf ("4 7\n23 10");
		return 0;
	}
 
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (!d[i][j])
			{
				ll lcm = 1;
				if (j) lcm = lcm / gcd (lcm, d[i][j-1]) * d[i][j-1];
				if (j < n - 1) lcm = lcm / gcd (lcm, d[i][j+1]) * d[i][j+1];
				if (i) lcm = lcm / gcd (lcm, d[i-1][j]) * d[i-1][j];
				if (i < n - 1) lcm = lcm / gcd (lcm, d[i+1][j]) * d[i+1][j];
 
				d[i][j] = lcm + 1;
			}
 
			printf ("%lld ", d[i][j]);
		}
		putchar ('\n');
	}
}
