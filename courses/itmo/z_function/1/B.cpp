//
// Created by aminjonshermatov on 2/1/2022.
//

#include "bits/stdc++.h"

using namespace std;

void solve() {
    string S;
    cin >> S;
    string reversed = S;
    reverse(reversed.begin(), reversed.end());

    int res = 0;
    for (int i = 0; i < S.size(); ++i) {
        for (int j = 0; j <= i; ++j) {
            // j...i
            string current = S.substr(j, i - j + 1);
            string prefix = S.substr(0, i - j + 1);
            string suffix = reversed.substr(0, i - j + 1);
            reverse(suffix.begin(), suffix.end());

            res += static_cast<int>((current == prefix) ^ (current == suffix));
        }
    }

    cout << res << '\n';
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