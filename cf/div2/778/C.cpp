#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

auto solve() -> void {
    int n;
    cin >> n;

    vector<int> A(n);
    for (auto &a : A) cin >> a;

    if (n == 1) {
        cout << "YES" << '\n';
        return;
    }

    if (n == 2) {
        if ((A[0] & 1) and (A[1] & 1)) {
            cout << (A[0] == A[1] ? "YES" : "NO") << '\n';
        } else cout << "YES" << '\n';
        return;
    }

    sort(A.begin(), A.end());
    auto k{0};
    if ((n & 1) == 0) k = A[n >> 1] + A[(n >> 1) - 1];
    else k = A[n >> 1] << 1;

    bool ok = true;
    for (int l = 0, r = n - 1; l < r and ok; ++l, --r) {
        if (A[l] + A[r] != k) ok = false;
    }

    cout << (ok ? "YES" : "NO") << '\n';
}

auto main() -> int {
    auto start = chrono::steady_clock::now();

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        // cout << "Case #" << tc << ": ";
        solve();
        // cout << '\n';
    }

    auto finish = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    // cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";

    return 0;
}