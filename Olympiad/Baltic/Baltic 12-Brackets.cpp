#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
//bracket on position l is paired with bracket on position r when r is the leftmost index > l, where [l+1;r-1] is a
//correct bracket sequence. In correct bracket sequence each bracket is paired with some bracket. Notice that 
//square brackets can be connectec with only square brackets, so after changing opening bracket to square closing, we
//should change one to square opening so those two brackets will be paired. dp state is d[i][j] - the number of ways
//to create a sequence out of first i brackets that way no prefix will have negative balance (no. of opening brackets
//minus no. of closing) and the current balance is j. Transitions are rather simple. When we consider changing opening bracket
//to square closing we have to make sure the balance of (i-1) sequence is positive, so there will be some "spare" 
//opening brackets to be paired with our new one.
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
 
const ll MOD = 1e9 + 9, INF = 1e18 + 1;
 
using namespace std;

string s;

ll d[2][100000];

int main ()
{
	int n;

	cin >> n;

	cin >> s;

	d[0][0] = 1;

	for (int i = 1; i <= n; i++)
	{
		int k = i % 2;

		for (int j = k; j <= i; j += 2)
		{
			if (s[i-1] == '(') d[k][j] = (d[!k][j+1] + (j ? d[!k][j-1] : 0)) % MOD;
			else d[k][j] = d[!k][j+1];
		}
	}

	cout << d[n % 2][0];

}
