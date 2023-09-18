#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<ld>::max();
inline constexpr auto ninf = numeric_limits<ld>::min();

using pii = pair<int, int>;

inline bool can_beat(int l, int r) {
    if (l == 0 && r == 9) return true;
    if (l == 9 && r == 0) return false;
    return l > r;
}

void solve() {
    deque<int> dq1, dq2;
    for (int i = 0; i < 5; ++i) {
        int x; cin >> x;
        dq1.push_back(x);
    }
    for (int i = 0; i < 5; ++i) {
        int x; cin >> x;
        dq2.push_back(x);
    }

    for (int k = 1; k <= 1e6; ++k) {
        if (can_beat(dq1.front(), dq2.front())) {
            dq1.push_back(dq1.front()); dq1.pop_front();
            dq1.push_back(dq2.front()); dq2.pop_front();
        } else {
            dq2.push_back(dq1.front()); dq1.pop_front();
            dq2.push_back(dq2.front()); dq2.pop_front();
        }
        if (dq1.empty()) {
            cout << "second " << k << '\n';
            return;
        }
        if (dq2.empty()) {
            cout << "first " << k << '\n';
            return;
        }
    }
    cout << "botva\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}