#include "bits/stdc++.h"

using namespace std;

using ll = long long;

void solve() {
    ll N, K;
    cin >> N >> K;

    vector<ll> A(N);
    for (auto &a : A) cin >> a;
    sort(A.rbegin(), A.rend());

    ll ans = 0, i = 0;
    while (K--) {
        if (A[i] <= 0) break;
        ans += A[i++];
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    solve();

    return 0;
}