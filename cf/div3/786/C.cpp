#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    string s, t;
    cin >> s >> t;

    unordered_set<string> ss;
    ss.insert(s);

    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == 'a') {
            if (t.size() > 1 && std::count(t.begin(), t.end(), 'a') > 0) { cout << -1 << '\n'; return; }
            ss.insert(string{s.begin(), s.begin() + i} + t + string{s.begin() + i + 1, s.end()});
        }
    }

    cout << ss.size() << '\n';
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