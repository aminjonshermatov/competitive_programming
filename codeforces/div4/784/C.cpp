#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai : a) cin >> ai;

    int info[2][2] = { {0, 0}, {0, 0} };

    for (int i = 0; i < n; ++i) {
        ++info[i & 1][a[i] & 1];
    }

    if ((info[0][0] == 0 or info[0][1] == 0) and (info[1][0] == 0 or info[1][1] == 0)) cout << "YES";
    else cout << "NO";
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