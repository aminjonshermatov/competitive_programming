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

    vector<int> pref;
    pref.reserve(n + 1);
    pref.push_back(0);
    for (const auto a : A) pref.push_back(a + pref.back());

    int res = 0;
    for (int s = 1; s <= n; ++s) {
        for (int e = s; e <= n; ++e) {
            if (pref[e] - pref[s - 1] > 100 * (e - s + 1)) res = max(res, e - s + 1);
        }
    }

    cout << res << '\n';
}

int main() {
    // auto start = chrono::steady_clock::now();

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T = 1;
    //cin >> T;
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