#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<ld>::max();
inline constexpr auto ninf = numeric_limits<ld>::min();

array<char, 29> alpha{};

using pii = pair<int, int>;

void solve() {
    string s; cin >> s;
    if (s.empty()) {
        cout << s << '\n';
        return;
    }
    const int n(s.size());

    auto ok = [&]() -> bool {
        stack<string> st;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '<') {
                bool is_open = true;
                if (i + 1 < n && s[i + 1] == '/') {
                    is_open = false;
                    ++i;
                }
                string cur;
                while (i + 1 < n && ::isalpha(s[i + 1])) cur.push_back(s[++i]);
                ++i;
                if (s[i] != '>') { return false; }
                if (i + 1 < n && s[i + 1] != '<') { return false; }
                if (cur.empty()) { return false; }
                if (!is_open) {
                    if (st.empty() || st.top() != cur) { return false; }
                    st.pop();
                } else st.push(cur);

            }
        }
        return st.empty();
    };

    for (int i = 0; i < n; ++i) {
        for (auto ch : alpha) {
            auto prv = s[i];
            s[i] = ch;
            if (ok()) {
                cout << s << '\n';
                return;
            }
            s[i] = prv;
        }
    }
    assert(false);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int i = 0;
    for (; i < 26; ++i) alpha[i] = char('a' + i);
    alpha[i++] = '<';
    alpha[i++] = '>';
    alpha[i++] = '/';

    int t = 1;
    //cin >> t;
    while (t--) solve();
}