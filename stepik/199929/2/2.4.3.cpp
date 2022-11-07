//
// Created by aminjon on 11/7/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

auto solve() {
    ll N;
    cin >> N;
    vector<pll> A(N);
    for (ll i = 0; i < N; ++i) {
        ll l, r;
        cin >> l >> r;
        A[i] = make_pair(r, r - l);
    }

    sort(A.begin(), A.end(), [](pll &l, pll &r) { return l.second < r.second; });

    ll ans = 0;
    set<pll> ss;
    for (ll i = N - 1; i >= 0; --i) {
        ll t = A[i].first - (i > 0 ? A[i - 1].first : 0);
        ss.emplace(A[i].second, i);
        while (t > 0 && !ss.empty()) {
            auto it = ss.begin();
            if (it->first <= t) {
                t -= it->first;
                ++ans;
            } else {
                ss.emplace(it->first - t, it->second);
                t = 0;
            }
            ss.erase(it);
        }
    }
    cout << ans;
}

int main() {
    solve();
}