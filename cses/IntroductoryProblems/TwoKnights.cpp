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
    for (uint64_t k = 1; k <= n; ++k) {
        uint64_t sqr = k * k;
        cout << (sqr * (sqr - 1) >> 1) - 4 * (k - 1) * (k - 2) << '\n';
    }


    return 0;
}