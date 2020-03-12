#include "interactive.h"
#include <bits/stdc++.h>
//We can get an unordered set of elements on several indices in 2 queries with such trick: suppose we know a value on position
//0, take pairwise xor of the indices set including and the n excluding 0. Second set of xors excluding the first one will 
//be all elements from the needed set of valued + value at position 0 but xored by value of 0. Now we can for each i
//for each value define if the i-th bit of index for the value is 1 or 0 by taking all indices with 1 in i-th bit and finding
//out corresponding to them values.
 
using namespace std;
 
vector <int> guess (int n) {
    map <int, int> ind;
    int d = ask (1);
 
    for (int b = 0; b < 7; b++) {
        vector <int> v;
 
        for (int i = 0; i < n; i++) {
            if (i & (1 << b)) v.push_back (i + 1);
        }
 
        if (v.empty ()) break;
        vector <int> ans = get_pairwise_xor (v);
        v.push_back (1);
        vector <int> ans2 = get_pairwise_xor (v);
 
        for (int a : ans)
            ans2.erase (find (ans2.begin (), ans2.end (), a));
 
        sort (ans2.begin(), ans2.end());
 
        for (int i = 1; i < ans2.size (); i += 2) {
            ind[ans2[i] ^ d] |= (1 << b);
        }
    }
 
    vector <int> ans (n);
 
    ans[0] = d;
 
    for (auto x : ind) {
        ans[x.second] = x.first;
    }
 
    return ans;
}
