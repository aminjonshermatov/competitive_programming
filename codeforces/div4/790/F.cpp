#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    map<int, int> mm;
    for (int i = 0; i < n; ++i) {
        int temp;
        cin >> temp;
        ++mm[temp];
    }

    vector<int> nums;
    nums.reserve(mm.size());
    for (const auto [kk, vv] : mm) {
        if (vv >= k) nums.push_back(kk);
    }

    pair<int, int> res;
    if (!nums.empty()) {
        int l = 0, r = 1;
        res = {nums[l], nums[l]};

        while (r < nums.size()) {
            if (nums[r] - 1 != nums[r - 1]) {
                l = r;
                r = l + 1;
            } else {
                if (nums[r] - nums[l] > res.second - res.first) res = {nums[l], nums[r]};
                ++r;
            }
        }

        cout << res.first << ' ' << res.second;
    } else cout << -1;
    cout << '\n';
}

int main() {
    // auto start = chrono::steady_clock::now();

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T = 1;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        // cout << "Case #" << tc << ": ";
        solve();
        // cout << '\n';
    }

    // auto finish = chrono::steady_clock::now();
    // auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    // cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";

    return 0;
}