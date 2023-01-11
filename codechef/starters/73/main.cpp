#include <bits/stdc++.h>
using namespace std;

int main() {
    auto solve = []() -> void {
        int n; cin >> n;
        vector<array<int, 20>> A(n);
        for (int i = 0; i < n; ++i) {
            int a; cin >> a;
            for (int j = 0; j < 20; ++j, a >>= 1) {
                A[i][j] = a&1;
            }
        }

        for (int j = 0; j < 20; ++j) {
            pair<int, int> cur{A[i][0], 1};
            vector<int> aa;
            for (int i = 1; i < n; ++i) {
                if (A[i][j] != cur.first) {
                    aa.push_back(cur.second);
                }
            }
        }
    };

    int t; cin >> t;
    while (t--) solve();
    return 0;
}
