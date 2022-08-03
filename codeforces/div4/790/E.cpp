#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> A(n);
    for (auto &a : A) cin >> a;
    sort(A.begin(), A.end(), greater<>());

    vector<int> pref(n);
    for (int i = 0; i < n; ++i) {
        pref[i] = A[i];
        if (i > 0) pref[i] += pref[i - 1];
    }

    int x;
    for (int i = 0; i < q; ++i) {
        cin >> x;

        if (x > pref.back()) cout << -1 << '\n';
        else {
            int lo = 0, hi = n;
            while (lo < hi) {
                int mid = lo + ((hi - lo) >> 1);
                if (pref[mid] >= x) hi = mid;
                else lo = mid + 1;
            }
            cout << lo + 1 << '\n';
        }

    }
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