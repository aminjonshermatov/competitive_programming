#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define all(x) (x).begin(), (x).end()
#define F first
#define S second

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc = 1;
    cin >> tc;

    int64_t x, y;
    while (tc--) {
        cin >> y >> x;

        int64_t max_ = max(x, y);
        if (max_ & 1) {
            if (x >= y) {
                cout << ((max_ * max_) - y + 1);
            } else {
                cout << ((max_ * max_) - (max_ << 1) + x + 1);
            }
        } else {
            if (x >= y) {
                cout << ((max_ * max_) - (max_ << 1) + y + 1);
            } else {
                cout << ((max_ * max_) - x + 1);
            }
        }
        cout << '\n';
    }

    return 0;
}