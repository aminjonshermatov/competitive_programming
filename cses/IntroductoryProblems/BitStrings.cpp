#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define MOD 1000000007

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    uint64_t n; cin >> n;

    uint64_t ans = 1;
    for (uint64_t i = 1; i <= n; ++i) {
        ans <<= 1;
        ans %= MOD;
    }
    cout << ans << '\n';

    return 0;
}