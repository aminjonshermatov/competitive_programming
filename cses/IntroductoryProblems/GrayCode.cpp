#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    int n_ = 1 << n;
    for (int i = 0; i < n_; ++i) {
        int k = i ^ (i >> 1);

        list<char> l;
        while (k > 0) {
            l.push_front('0' + (k & 1));
            k >>= 1;
        }
        while (l.size() != n) l.push_front('0');
        while (!l.empty()) {
            cout << l.front();
            l.pop_front();
        }
        cout << '\n';
    }

    return 0;
}