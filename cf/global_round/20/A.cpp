#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

void solve() {
    int n;
    cin >> n;

    priority_queue<int> pq;
    for (int i = 0; i < n; ++i) {
        int temp;
        cin >> temp;
        if (temp > 1) pq.push(temp);
    }

    bool errorgorn = true;
    while (!pq.empty()) {
        int it = pq.top(); pq.pop();

        int a = it / 2;
        int b = it - a;

        if (a > 1) pq.push(a);
        if (b > 1) pq.push(b);
        errorgorn = !errorgorn;
    }

    cout << (errorgorn ? "maomao90" : "errorgorn") << '\n';
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