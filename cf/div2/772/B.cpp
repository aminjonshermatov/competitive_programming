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

    int m = 0;

    for (int i = 1; i < n - 1; ++i) {
        if (A[i - 1] < A[i] and A[i] > A[i + 1]) {
            ++m;
            if (i + 3 < n) {
                if (A[i + 2] > A[i + 1] and A[i + 2] > A[i + 3]) {
                    A[i + 1] = max(A[i], A[i + 2]);
                    continue;
                }
            }
            A[i] = max(A[i - 1], A[i + 1]);
        }
    }

    cout << m << '\n';
    for (const auto a : A) cout << a << ' ';
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