#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

auto solve() -> void {
    int n;
    cin >> n;

    if (n == 3) {
        cout << "3 2 1" << '\n';
        cout << "2 3 1" << '\n';
        cout << "1 3 2" << '\n';
        return;
    }

    list<int> nums;
    for (int i = n; i >= 1; --i) nums.push_back(i);


    for (int i = 1; i <= n; ++i) {
        auto cur{nums};

        while (not cur.empty()) {
            cout << cur.front() << ' ';
            cur.pop_front();
        }
        cout << '\n';

        nums.push_back(nums.front());
        nums.pop_front();
    }
}

auto main() -> int {
    auto start = chrono::steady_clock::now();

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
//        cout << "Case #" << tc << ": ";
        solve();
//        cout << '\n';
    }

    auto finish = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    // cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";

    return 0;
}