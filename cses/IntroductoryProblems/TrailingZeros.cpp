#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define ull uint64_t
#define ll int64_t

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ull n; cin >> n;

    uint64_t res = 0;
    for (uint64_t k = 5; k <= n; k *= 5) res += n / k;
    cout << res << '\n';

    return 0;
}