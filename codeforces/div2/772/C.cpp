#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

auto solve() -> void {
    int n;
    cin >> n;

    vector<int64_t> A(n);
    for (auto &a : A) cin >> a;

    bool isSortedInc = true;
    for (int i = 1; i < n and isSortedInc; ++i) {
        if (A[i] < A[i - 1]) isSortedInc = false;
    }

    if (isSortedInc) cout << 0 << '\n';
    else if (A[n - 2] > A[n - 1] or A[n - 1] < 0) cout << -1 << '\n';
    else {
        cout << n - 2 << '\n';
        for (int i = 0; i < n - 2; ++i) cout << i + 1 << ' ' << n - 1 << ' ' << n << '\n';
    }
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