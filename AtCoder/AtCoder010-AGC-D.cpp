#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//The idea of this game is to keep one property of an array and revert all the changes in the propertymade by another player.
//We can keep the parity of even numbers. If we keep it even ater each our turn, our opponent will have no choice but make it
//odd afterwards, so the number of even numbers won't ever be 0 for us (since 0 is an even number). There is a corner case
//though when we player can change parities of numbers and it's only when all numbers are even. So when there is no other
//optimal move for him, he will change the parities.
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int gcd (int a, int b)
{
	if (!b) return a;
	else return gcd (b, a % b);
}

int n;

bool f (vector <int> v)
{
	int odd = 0;
	for (int a : v)
		odd += (a & 1);

	if ((v.size () - odd) & 1) {
		return true;
	}
	else {
		if (odd > 1) return false;
		else {
			int g = v[0];
			for (int a : v)
				if ((a & 1) && a != 1) g = gcd (g, a - 1);
				else g = gcd (g, a);

			for (int& a : v)
				a /= g;

			if (g != 1) return !f (v);
			else return false;
		}
	}
}

int main ()
{
	cin >> n;
	vector <int> v (n);

	for (int i = 0; i < n; i++)
		scanf ("%d", &v[i]);

	if (f (v)) cout << "First";
	else cout << "Second";
}
