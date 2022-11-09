//
// Created by aminjon on 11/9/22.
//
#include <bits/stdc++.h>

using namespace std;

auto solve() {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    vector<int> dp(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        dp[i] = 1;
        for (int j = 1; j < i; ++j) {
            if (A[j - 1] <= A[i - 1]) dp[i] = max(dp[i], dp[j] + 1);
        }
    }

    cout << *max_element(dp.begin(), dp.end());
}

int main() {
    solve();
}