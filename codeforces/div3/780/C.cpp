#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

auto solve() {
    string s;
    cin >> s;

    const auto n = static_cast<int>(s.size());

    deque<char> dq;
    for (const auto ch : s) {
        if (not dq.empty() and dq.back() == ch) dq.pop_back();
        else dq.push_back(ch);
    }

    string cur{dq.begin(), dq.end()};
    array<vector<int>, 26> idxs;

    for (int i = 0; i < cur.size(); ++i) {
        idxs[cur[i] - 'a'].push_back(i);
    }

    int res = 0;

    for (int i = 0; i < cur.size(); ++i) {
        auto it = upper_bound(idxs[cur[i] - 'a'].begin(), idxs[cur[i] - 'a'].end(), i);
        if (it == idxs[cur[i] - 'a'].end()) ++res;
        else {
            res += *it - i - 1;
            i = *it;
        }
    }

    if (((n - res) & 1) == 1) ++res;

    cout << res << '\n';
}

auto main() -> int {
    auto start = chrono::steady_clock::now();

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

    auto finish = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    // cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";

    return 0;
}