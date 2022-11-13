#include "bits/stdc++.h"

using namespace std;

void solve() {
    string s;
    cin >> s;

    const auto N = (int)s.size();

    vector<int> z(N, 0);
    for (int i = 1; i < N; ++i) {
        while (z[i] + i < N && s[z[i]] == s[z[i] + i]) ++z[i];
    }

    for (auto c : z) cout << c << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc = 1;
    // cin >> tc;

    while (tc--) solve();
}