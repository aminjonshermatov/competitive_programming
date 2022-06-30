#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<pair<int, int>> p;

    function<void(int, int, int, int)> toh = [&](int n_, int from, int to, int aux) {
        if (n_ == 1) {
            p.emplace_back(from, to);
            return;
        }

        toh(n_ - 1, from, aux, to);
        p.emplace_back(from, to);
        toh(n_ - 1, aux, to, from);
    };

    int n; cin >> n;
    toh(n, 1, 3, 2);

    cout << p.size() << '\n';
    for (const auto [f, t] : p) cout << f << ' ' << t << '\n';

    return 0;
}