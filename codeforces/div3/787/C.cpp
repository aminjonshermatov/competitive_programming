#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    int n;
    cin >> n;
    unordered_map<int, vector<int>> tree_;
    int root = -1;

    for (int i = 1; i <= n; ++i) {
        int p;
        cin >> p;

        if (p != i) {
            tree_[p].push_back(i);
        } else {
            root = i;
        }
    }

    int leafs = 0;
    for (const auto& [_, v] : tree_) {
        if (v.empty()) ++leafs;
    }

    cout << leafs << '\n';
    list<int> q;
    q.push_back(root);
    const function<void()>
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