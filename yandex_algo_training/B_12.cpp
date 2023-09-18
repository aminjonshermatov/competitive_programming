#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;

using pii = pair<int, int>;

void solve() {
    string s; cin >> s;
    stack<char> st;
    for (auto ch : s) {
        if (ch == '(' || ch == '{' || ch == '[') { st.push(ch); continue; }
        if (st.empty() || (ch == ')' && st.top() != '(') || (ch == '}' && st.top() != '{') || (ch == ']' && st.top() != '[')) { cout << "no\n"; return; }
        st.pop();
    }
    cout << (st.empty() ? "yes" : "no") << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}