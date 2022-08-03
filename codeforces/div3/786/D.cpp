#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> A(n);
    for (auto &a : A) cin >> a;

    int lo = 1, hi = n - 2;
    bool ok = true;

    while (lo < hi && ok) {
        if (A[lo] <= A[lo - 1] && A[hi] >= A[hi + 1]) {
            ++lo;
            --hi;
        } else ok = false;
    }

    if (lo == hi && n > 2) ok &= A[lo] <= A[lo - 1] && A[hi] >= A[hi + 1];

    cout << (ok ? "yes" : "no") << '\n';
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