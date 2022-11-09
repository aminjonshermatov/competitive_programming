//
// Created by aminjon on 11/9/22.
//
#include <bits/stdc++.h>

using namespace std;

auto solve() {
    int N, K;
    cin >> N >> K;

    vector<int> A(N - 1, 0);
    for (int i = 1; i < N; ++i) cin >> A[i];

    vector<int> dp(N, 0);
    for (int i = 1; i < N; ++i) {
        int j = max(0, i - K);
        int mx = dp[j];
        for (int k = j + 1; k < i; ++k) mx = max(mx, dp[k]);
        dp[i] = mx + A[i];
    }

    cout << dp[N - 1];
}

int main() {
    solve();
}