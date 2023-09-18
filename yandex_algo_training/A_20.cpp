#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();

using pii = pair<int, int>;

void solve() {
    int n, k, p; cin >> n >> k >> p;

    int ans = 0;
    vector<int> evs(p);
    vector<list<int>> cars(n);
    for (int i = 0; i < p; ++i) {
        cin >> evs[i], --evs[i];
        cars[evs[i]].push_back(i);
    }

    multiset<int> cur;
    priority_queue<pii> far;
    for (int i = 0; i < p; ++i) {
        auto x = evs[i];
        cars[x].pop_front();

        if (cur.count(x) == 0) {
            if (cur.size() >= k) {
                cur.erase(far.top().second);
                far.pop();
            }
            ++ans;
            cur.insert(x);
        }
        if (cars[x].empty()) far.emplace(inf, x);
        else far.emplace(cars[x].front(), x);
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}