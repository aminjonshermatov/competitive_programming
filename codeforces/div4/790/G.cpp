#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    int n;
    cin >> n;

    unordered_map<int, vector<int>> adj;
    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        adj[p].push_back(i);
    }
    adj[0].push_back(1);
    string s;
    cin >> s;

    int res = 0;

    const function<pair<int, int>(int)> dfs = [&](int node) -> pair<int, int> {
        pair<int, int> res_ = {(int)(s[node - 1] == 'B'), (int)(s[node - 1] == 'W')};

        if (adj.count(node) == 0) return res_;
        pair<int, int> self = res_;
        for (const auto c : adj[node]) {
            auto [b, w] = dfs(c);
            cout << c << ' ' << b << ' ' << w << ' ' << s[c - 1] << '\n';

            if (self.first + b == self.second + w) ++res;
            res_.first += b;
            res_.second += w;
        }

        return res_;
    };

    dfs(0);
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