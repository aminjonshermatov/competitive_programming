#include <bits/stdc++.h>

using namespace std;

using i64 =  ::int64_t;
using u64 = ::uint64_t;

using pii = pair<int, int>;

inline constexpr auto  inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();

void solve() {
    int m, n; cin >> m >> n;
    vector<pii> A;

    for (int i = 0; i < n; ++i) {
        int a, b; cin >> a >> b;
        vector<pii> na;
        for (auto [a_, b_] : A) {
            if (clamp(a, a_, b_) == a || clamp(b, a_, b_) == b || (a_ <= a && b <= b_) || (a <= a_ && b_ <= b)) continue;
            na.emplace_back(a_, b_);
        }
        na.emplace_back(a, b);
        A = std::move(na);
    }
    cout << A.size() << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}