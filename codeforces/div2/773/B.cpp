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

    unordered_map<int, int> freq;
    for (const auto a : A) ++freq[a];

    auto cmp = [&freq](const auto lhs, const auto rhs) -> bool { return freq[lhs] > freq[rhs]; };
    priority_queue<int, vector<int>, decltype(cmp)> heap(cmp);
    for (const auto [a, _] : freq) heap.push(a);

    int group = 0;
    for (int i = 0; i < n; ++i) {
        cout << max<int>(heap.size(), i) << ' ';
        auto cur{heap.top()}; heap.pop();
        --freq[cur];

        if (freq[cur] != 0) heap.push(cur);
        else ++group;
    }
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
        // cout << "Case #" << tc << ": ";
        solve();
        // cout << '\n';
    }

    auto finish = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    // cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";

    return 0;
}