#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;

using pii = pair<int, int>;

inline constexpr string_view PUSH{"push"};
inline constexpr string_view POP{"pop"};
inline constexpr string_view BACK{"back"};
inline constexpr string_view SIZE{"size"};
inline constexpr string_view CLEAR{"clear"};
inline constexpr string_view EXIT{"exit"};

void solve() {
    string cmd;
    stack<int> st;
    while (cin >> cmd) {
        if (cmd == PUSH) {
            int x; cin >> x;
            st.push(x);
            cout << "ok\n";
        } else if (cmd == POP) {
            if (st.empty()) {
                cout << "error\n";
                continue;
            }
            cout << st.top() << '\n';
            st.pop();
        } else if (cmd == BACK) {
            if (st.empty()) {
                cout << "error\n";
                continue;
            }
            cout << st.top() << '\n';
        } else if (cmd == SIZE) {
            cout << st.size() << '\n';
        } else if (cmd == CLEAR) {
            st = stack<int>();
            cout << "ok\n";
        } else if (cmd == EXIT) {
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