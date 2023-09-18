#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<ld>::max();
inline constexpr auto ninf = numeric_limits<ld>::min();

using pii = pair<int, int>;

void solve() {
    string cmd;
    deque<int> dq;
    while (cin >> cmd) {
        if (cmd == "push_front") {
            int x; cin >> x;
            dq.push_front(x);
            cout << "ok\n";
        } else if (cmd == "push_back") {
            int x; cin >> x;
            dq.push_back(x);
            cout << "ok\n";
        } else if (cmd == "pop_front") {
            if (dq.empty()) {
                cout << "error\n";
                continue;
            }
            auto x = dq.front();
            dq.pop_front();
            cout << x << '\n';
        } else if (cmd == "pop_back") {
            if (dq.empty()) {
                cout << "error\n";
                continue;
            }
            auto x = dq.back();
            dq.pop_back();
            cout << x << '\n';
        } else if (cmd == "front") {
            if (dq.empty()) {
                cout << "error\n";
                continue;
            }
            auto x = dq.front();
            cout << x << '\n';
        } else if (cmd == "back") {
            if (dq.empty()) {
                cout << "error\n";
                continue;
            }
            auto x = dq.back();
            cout << x << '\n';
        } else if (cmd == "size") {
            cout << dq.size() << '\n';
        } else if (cmd == "clear") {
            dq = deque<int>();
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