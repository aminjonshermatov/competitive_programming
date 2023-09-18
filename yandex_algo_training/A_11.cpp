#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<ld>::max();
inline constexpr auto ninf = numeric_limits<ld>::min();

using pii = pair<int, int>;

void solve() {
    int n; cin >> n;
    vector<ld> A(n);
    for (auto &a : A) cin >> a;
    vector<ld> mn_sf(n, inf);
    for (int i = n - 2; i >= 0; --i) mn_sf[i] = min(mn_sf[i + 1], A[i + 1]);
    stack<ld> st;
    auto lst = ninf;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && st.top() <= A[i] && st.top() <= mn_sf[i]) lst = st.top(), st.pop();
        if (A[i] > mn_sf[i]) st.push(A[i]);
        else lst = A[i];
    }

    while (!st.empty()) {
        if (st.top() < lst) {
            cout << 0 << '\n';
            return;
        }
        lst = st.top();
        st.pop();
    }
    cout << 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) solve();
}