#include <bits/stdc++.h>

using namespace std;

using i64 =  ::int64_t;
using u64 = ::uint64_t;

void solve() {
    string s; cin >> s;
    const int n(s.size());

    vector<u64> freq(n, 0);
    for (int i = 1; i <= n; ++i) freq[i - 1] = u64(1) * (n - i + 1) * i;
    array<u64, 26> cnt{};
    for (auto &x : cnt) x = 0;
    for (int i = 0; i < n; ++i) cnt[s[i] - 'a'] += freq[i];
    for (int ch = 0; ch < 26; ++ch) if (cnt[ch] > 0) cout << char('a' + ch) << ": " << cnt[ch] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}