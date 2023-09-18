#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<ld>::max();
inline constexpr auto ninf = numeric_limits<ld>::min();

using pii = pair<int, int>;

void solve() {
    string s;
    getline(cin, s);
    const int n(s.size());

    auto ok_chars = [&]() -> bool {
        return all_of(s.begin(), s.end(), [](auto ch) { return isdigit(ch) || ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '(' || ch == ')'; });
    };
    auto ok_brackets = [&]() -> bool {
        int bal = 0;
        for (auto ch : s) {
            if (ch == '(') ++bal;
            else if (ch == ')' && --bal < 0) return false;
        }
        return bal == 0;
    };
    auto ok_spaces = [&]() -> bool {
        for (int i = 0; i < n; ++i) {
            if (!isdigit(s[i])) continue;
            bool any_ns = false, any_s = false;
            for (int j = i + 1; j < n; ++j) {
                if (s[j] == ' ') {
                    any_s = true;
                    continue;
                }
                if (isdigit(s[j])) break;
                any_ns = true;
            }
            if (any_s && !any_ns) return false;
        }
        return true;
    };

    auto ok_gen = [&]() -> bool {
        stack<int> vals;
        stack<char> ops;
        for (int i = 0; i < n; ++i) {
            if (s[i] == ' ') continue;
            if (isdigit(s[i])) {
                vals.push(s[i] - '0');
                while (i + 1 < n && isdigit(s[i + 1])) ++i;
            } else if (s[i] == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    if (vals.size() < 2) return false;
                    vals.pop(); vals.pop(); vals.push(11);
                    ops.pop();
                }
                if (ops.top() != '(') return false;
                ops.pop();
            } else ops.push(s[i]);
        }
        while (!ops.empty()) {
            if (vals.size() < 2) return false;
            vals.pop(); vals.pop(); vals.push(11);
            ops.pop();
        }
        return vals.size() == 1;
    };

    if (!ok_chars() || !ok_brackets() || !ok_spaces() || !ok_gen()) {
        cout << "WRONG\n";
        return;
    }

    stack<int> vals;
    stack<char> ops;
    int cur = 0;
    bool has_val = false;
    for (int i = 0; i < n; ++i) {
        char ch = s[i];
        if (ch == ' ') continue;
        if (isdigit(ch)) {
            cur = cur * 10 + ch - '0';
            has_val = true;
        } else {
            if (has_val) {
                vals.push(cur), cur = 0, has_val = false;
                while (!ops.empty() && ops.top() == '*') {
                    ops.pop();
                    assert(vals.size() > 1);
                    auto b = vals.top(); vals.pop();
                    auto a = vals.top(); vals.pop();
                    vals.push(a * b);
                }
            }

            if (ch == ')') {
                while (ops.top() != '(') {
                    auto op = ops.top(); ops.pop();
                    assert(vals.size() > 1);
                    auto b = vals.top(); vals.pop();
                    auto a = vals.top(); vals.pop();
                    if (op == '+') {
                        if (!ops.empty() && ops.top() == '-') vals.push(a - b);
                        else vals.push(a + b);
                    }
                    else if (op == '-') vals.push(a - b);
                }
                assert(ops.top() == '(');
                ops.pop();
                while (!ops.empty() && ops.top() == '*') {
                    ops.pop();
                    assert(vals.size() > 1);
                    auto b = vals.top(); vals.pop();
                    auto a = vals.top(); vals.pop();
                    vals.push(a * b);
                }
            } else ops.push(ch);
        }
    }
    if (has_val) vals.push(cur);

    while (!ops.empty()) {
        auto op = ops.top(); ops.pop();
        assert(vals.size() > 1);
        auto b = vals.top(); vals.pop();
        auto a = vals.top(); vals.pop();
        if (op == '+') {
            if (!ops.empty() && ops.top() == '-') vals.push(a - b);
            else vals.push(a + b);
        }
        else if (op == '-') vals.push(a - b);
        else if (op == '*') vals.push(a * b);
        else assert(false);
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