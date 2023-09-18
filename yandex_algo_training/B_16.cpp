#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<ld>::max();
inline constexpr auto ninf = numeric_limits<ld>::min();

using pii = pair<int, int>;

void solve() {

    string cmd;
    queue<int> q;
    while (cin >> cmd) {
        if (cmd == "push") {
            int n; cin >> n;
            q.push(n);
            cout << "ok\n";
        } else if (cmd == "pop") {
            if (q.empty()) {
                cout << "error\n";
                continue;
            }
            auto x = q.front(); q.pop();
            cout << x << '\n';
        } else if (cmd == "front") {
            if (q.empty()) {
                cout << "error\n";
                continue;
            }
            cout << q.front() << '\n';
        } else if (cmd == "size") {
            cout << q.size() << '\n';
        } else if (cmd == "clear") {
            q = queue<int>();
            cout << "ok\n";
        } else if (cmd == "exit") {
            cout << "bye\n";
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}