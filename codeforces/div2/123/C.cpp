#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

auto solve() -> void {
    int n, x;
    cin >> n >> x;

    vector<int> A(n);
    for (auto &a : A) cin >> a;

    vector<int> maxSum(n + 1, INT_MIN);
    maxSum[0] = 0;
    for (int i = 0; i < n; ++i) {
        int sum = A[i];
        maxSum[1] = max(maxSum[1], sum);
        for (int j = i + 1; j < n; ++j) {
            sum += A[j];
            maxSum[j - i + 1] = max(maxSum[j - i + 1], sum);
        }
    }

    for (int i = 0; i <= n; ++i) {
        int res = 0;
        for (int j = 0; j <= n; ++j) res = max(res, maxSum[j] + min(i, j) * x);
        cout << res << ' ';
    }
    cout << '\n';
}

auto main() -> int {
    auto start = chrono::steady_clock::now();

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
//        cout << "Case #" << tc << ": ";
        solve();
//        cout << '\n';
    }

    auto finish = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    // cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";

    return 0;
}