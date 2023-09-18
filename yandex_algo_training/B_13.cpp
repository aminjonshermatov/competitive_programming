#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;

using pii = pair<int, int>;

inline bool is_digit(char ch) { return clamp(ch, '0', '9') == ch; }

void solve() {
    string s;
    getline(cin, s);
    stack<int> vals;
    int cur = 0;
    bool has_val = false;
    for (auto ch : s) {
        if (ch == ' ') {
            if (has_val) vals.push(cur), cur = 0, has_val = false;
            continue;
        }
        if (is_digit(ch)) { cur = cur * 10 + ch - '0'; has_val = true; continue ; }
        if (ch == '+') {
            assert(vals.size() > 1);
            auto b = vals.top(); vals.pop();
            auto a = vals.top(); vals.pop();
            vals.push(a + b);
        } else if (ch == '-') {
            assert(vals.size() > 1);
            auto b = vals.top(); vals.pop();
            auto a = vals.top(); vals.pop();
            vals.push(a - b);
        } else if (ch == '*') {
            assert(vals.size() > 1);
            auto b = vals.top(); vals.pop();
            auto a = vals.top(); vals.pop();
            vals.push(a * b);
        }
    }

    assert(vals.size() == 1);
    cout << vals.top() << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}