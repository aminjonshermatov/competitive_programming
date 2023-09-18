#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<ld>::max();
inline constexpr auto ninf = numeric_limits<ld>::min();

using pii = pair<int, int>;

void solve() {
    int n; cin >> n;
    priority_queue<int, vector<int>, greater<>> pq;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        pq.push(x);
    }
    ld ans = 0;
    while (pq.size() > 1) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        auto s = a + b;
        pq.push(s);
        ans += ld(s) / 20;
    }
    cout << fixed << setprecision(2) << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}