#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        int64_t a, b;
        cin >> a >> b;

        int64_t x = 2 * a - b;
        int64_t y = 2 * b - a;

        if (x >= 0 && y >= 0 && x % 3 == 0 && y % 3 == 0) cout << "YES";
        else cout << "NO";
        cout << '\n';
    }

    return 0;
}