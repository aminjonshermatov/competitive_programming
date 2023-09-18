#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;

void solve() {
    int k; string s;
    cin >> k >> s;
    const int n(s.size());

    int ans = 0;
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        for (int kk = k - (s[0] != ch), l = 0, r = 0; l <= r && r < n; kk += s[l++] != ch) {
            while (r + 1 < n && (s[r + 1] == ch || kk > 0)) kk -= s[++r] != ch;
            ans = max(ans, r - l + 1);
        }
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