#include <iostream>
#include <vector>
#include <stdio.h>
//A couple of observations:
//1) Ball always leaves from the right side
//2) When ball enters a pair of reflectors, the laft one is always A
//3) When ball enters a pair of reflectors, AB becomes AA, AA becomes BA, which means we shift the string by 1 and invert
//it and add A to the left
//4) Since only A's appear from the right, after 2N moves (one for bouncing back from the first reflector, second for shifting)
//it'll look like a string BABABA..BA. For even N it will always transform into itself, for odd it will change the first element
//once in two moves.
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9;
 
int n, k;
string s;
 
int main ()
{
	cin >> n >> k;
 
	deque <int> a (n);
	cin >> s;
	int rev = 0, ptr = 0, last = 0;
 
	for (int i = 0; i < n; i++)
		a[i] = (s[i] == 'B');
 
	for (int i = 0; i < k && ptr <= n; i++)
	{
 
		if (!(a[0] ^ rev)) 
		{
			a[0] = !rev;
			continue;
		}
 
		a.pop_front ();
		ptr++;
		rev ^= 1;
		a.push_back (rev);
		last = i;
	}
	last++;
 
	if ((n & 1) && ((k - last) & 1)) 
		a[0] = !rev;
 
	for (int j = 0; j < n; j++)
		if (rev ^ a[j]) putchar ('B');
		else putchar ('A');
}
