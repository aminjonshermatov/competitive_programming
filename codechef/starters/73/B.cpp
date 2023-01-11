#include <bits/stdc++.h>
using namespace std;

int main() {
    auto solve = []() -> void {
        uint n, y; cin >> n >> y;
        vector<uint> A(n);
        uint ors = 0;
        for (auto &a : A) cin >> a, ors |= a;

        int ans = y & (~ors);
        while (y > 0) {
            if ((ors & 1) == 1 && (y & 1) == 0) {
                cout << -1 << '\n';
                return;
            }
            y >>= 1;
            ors >>= 1;
        }
        if (ors > 0) {
            cout << -1 << '\n';
            return;
        }
        cout << ans << '\n';
    };

    int t; cin >> t;
    while (t--) solve();
    return 0;
}
