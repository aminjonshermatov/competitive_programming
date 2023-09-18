#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;

using pii = pair<int, int>;

void solve() {
    int n; cin >> n;
    int last = 0;
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        if (last + 1 == x) {
            ++last;
            continue;
        }
        while (!st.empty() && st.top() == last + 1) {
            ++last;
            st.pop();
        }
        st.push(x);
    }

    while (!st.empty()) {
        if (last + 1 != st.top()) {
            cout << "NO\n";
            return;
        }
        ++last;
        st.pop();
    }
    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}