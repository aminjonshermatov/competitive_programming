#include "bits/stdc++.h"

using namespace std;

void solve() {
    int k, j;
    cin >> k >> j;

    if (j == 0 || (j & 1) == 1) cout << 0;
    else {
        while (j > 0) {
            if ((j & (j - 1)) == 0) break;
            int prev = 1 << k--;

            if (j > prev) j -= prev;
        }

        cout << j - 1;
    }

    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc;
    cin >> tc;

    while (tc--) solve();
}