#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    string s;
    cin >> s;

    int alice = 0;
    for (const auto ch : s) alice += (ch - 'a') + 1;

    if (s.size() == 1) {
        cout << "Bob " << alice << '\n';
        return;
    }

    if ((s.size() & 1) == 1) {
        auto bob = min(s.front() - 'a', s.back() - 'a') + 1;
        alice -= bob;
        auto diff = alice - bob;
        if (bob > alice) {
            cout << "Bob " << diff << '\n';
        } else {
            cout << "Alice " <<  diff << '\n';
        }
    } else {
        cout << "Alice " << alice << '\n';
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