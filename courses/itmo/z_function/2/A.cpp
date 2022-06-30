#include "bits/stdc++.h"

using namespace std;

void solve() {
    string s;
    cin >> s;

    cout << 0 << ' ';
    for (int i = 1; i < s.size(); ++i) {
        int ii = i, jj = 0;

        while (ii < s.size() and jj < s.size()) {
            if (s[ii] != s[jj]) break;
            ++ii;
            ++jj;
        }

        cout << jj << ' ';
    }
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