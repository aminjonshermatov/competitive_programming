#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define ll int64_t
#define ull uint64_t

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int q; cin >> q;

    // 9*1 + 90*2 + 900*3 + 9000*4 + ...
    // 9 * sum(n*10^(n-1))
    while (q--) {
        ll k; cin >> k;

        ll len = 1;
        ll pow_ = 1;
        while (k > 9ll * len * pow_) {
            k -= 9ll * len * pow_;
            pow_ *= 10;
            ++len;
        }

        --k;
        ll x = k / len;
        ll y = k % len;
        string s = to_string(pow_ + x);
        cout << s[y] << '\n';
    }

    return 0;
}