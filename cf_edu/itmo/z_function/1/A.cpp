//
// Created by aminjonshermatov on 2/1/2022.
//

#include "bits/stdc++.h"

using namespace std;

void solve() {
    string S;
    cin >> S;

    int maxL = 0;

    for (int i = 0; i < S.size(); ++i) {
        int l = 0, r = i;

        while (l <= r) {
            if (S[l] != S[r]) break;
            ++l;
            --r;
        }

        if (l > r) maxL = max(maxL, i + 1);
    }

    cout << maxL << '\n';
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