#include "bits/stdc++.h"

using namespace std;

void solve() {
    string t, p;
    cin >> t >> p;

    if (t.size() < p.size()) {
        cout << 0 << '\n';
        return;
    }

    vector<int> indices;
    for (int i = 0; i < t.size() - p.size() + 1; ++i) {
        bool isNotMatch = false;

        for (int j = 0; j < p.size() and not isNotMatch; ++j) {
            if (p[j] != '?' and p[j] != t[i + j]) isNotMatch = true;
        }

        if (not isNotMatch) indices.push_back(i);
    }

    cout << indices.size() << '\n';
    for (const auto idx : indices) cout << idx << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc;
    cin >> tc;

    while (tc--) {
        solve();
    }
}