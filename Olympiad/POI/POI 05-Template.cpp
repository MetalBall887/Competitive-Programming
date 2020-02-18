#include <bits/stdc++.h>
//To start with the algorithm, we need to acknowledge some lemmas:
//Lemma 1: if there is a prefix-suffix s of the string x (string that appears as a prefix and a suffix in x) that is
//bigger than the template of x, template of x is also a template of s. It's not hard to prove, just 
//observe that the template of x is a suffix of s and s as prefix is almost covered by this template
//(almost, because the last few characters may be covered only by the prefix of the template)
//Lemma 2: if for x we take the biggest prefix-suffix s, then the shortest template will be either the shortest
//template of s (call it p') or x itself. It can be proved by using the 1st Lemma, the hardest part is proving that the
//shortest template will not be longer than p', because by Lemma 1 it should cover s -> be the prefix-suffix of s -> 
//should be coverable by p'. Other cases are proven easier.
//Our algorithm is built on Lemma 2, where we take the shortest pattern of the largest prefix-suffix (found be prefix function)
//and in z[i] contain for the template x[0..i] the rightmost yet index that can be covered by this template.
//Now how do we check so quickly with z? Let's say for a string x and template t, x- is x without the last occurrence of t
//and t' is the shortest template for x-. t' is obviously at most t. Let's say it's smaller than t. But by the Lemma 1, since
//t still is a prefix-suffix of x-, it's constructible by t', which means that last occurrence of t in x, as well as x- can be
//constructed by t', from which we get to a contradiction. That means, if for x[0..i] x[0..j] was the shortest template and i!=j
//it appeared somewhere between x[0..i-j] ... x[0..i-1] as a shortest template, so information in z[i] is up-to-date as long as
//x[0..i] can be the shortest template.
 
using namespace std;
 
typedef long long ll;

const int N = 1e6 + 1, inf = 1e9;
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

string st;
int n, p[N], z[N], s[N];

int main () {
	cin >> st;
	n = st.length ();

	for (int i = 1; i < n; i++) {
		int j = p[i-1];
		while (j > 0 && st[i] != st[j]) j = p[j-1];
		if (st[i] == st[j]) j++;
		p[i] = j;
	}

	for (int i = 0; i < n; i++) {
		z[i] = i;
	}

	for (int i = 1; i < n; i++) {
		if (!p[i]) {
			s[i] = i;
			continue;
		}
		int t = s[p[i]-1];
		if (z[t] >= i - (t + 1)) {
			s[i] = t, z[t] = i;
		} else s[i] = i;
	}

	cout << s[n-1] + 1;
}
