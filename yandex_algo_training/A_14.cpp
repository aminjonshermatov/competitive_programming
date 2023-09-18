#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<ld>::max();
inline constexpr auto ninf = numeric_limits<ld>::min();

using pii = pair<int, int>;

void solve() {
    int n; cin >> n;
    vector<i64> A(n);
    for (auto &a : A) cin >> a;
    i64 ans = 0;
    stack<pair<int, i64>> st;

    for (int i = 0; i < n; ++i) {
        auto start = i;

        while (not st.empty() and st.top().second > A[i]) {
            auto [idx, height] = st.top(); st.pop();
            ans = max(ans, i64(1) * (i - idx) * height);
            start = idx;
        }
        st.emplace(start, A[i]);
    }

    while (not st.empty()) {
        auto [idx, height] = st.top(); st.pop();
        ans = max(ans, i64(1) * (n - idx) * height);
    }

    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}