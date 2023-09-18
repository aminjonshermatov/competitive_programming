#include <bits/stdc++.h>

using namespace std;

using i64 =  ::int64_t;
using u64 = ::uint64_t;

void solve() {
    int n, m, k; cin >> m >> n >> k;
    vector<vector<i64>> pf(m + 1, vector<i64>(n + 1, 0));
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int x; cin >> x;
            pf[i][j] = pf[i - 1][j] + pf[i][j - 1] - pf[i - 1][j - 1] + x;
        }
    }

    auto get = [&](int x1, int y1, int x2, int y2) -> i64 {
        return 0ll + pf[y2][x2] - pf[y2][x1 - 1] - pf[y1 - 1][x2] + pf[y1 - 1][x1 - 1];
    };

    for (int _ = 0; _ < k; ++_) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        cout << get(y1, x1, y2, x2) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}