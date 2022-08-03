#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n), suffix(n, 0);
    for (auto &ai: a) cin >> ai;

    int count = 0;
    for (int i = n - 2; i >= 0; --i) {
        if (a[i] == a[i + 1]) suffix[i] = ++count;
    }

    int res = 0;
    for (int l = 0, r = 2; r < n; ++l, ++r) {
        if (a[l] == a[l + 1] && a[l + 1] == a[r]) {
            if (suffix[l] >= 2) {
                if (suffix[l] == 2) {
                    int next = r + 1 < n ? a[r + 1] : a[l] + 1;

                    a[l + 1] = a[r] = next;
                } else {
                    a[l + 1] = a[r] = a[r + 1];
                }
                ++res;
            }
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