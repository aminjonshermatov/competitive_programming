#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;

void solve() {
    char ch;
    map<char, int> cnt;
    int mx = 0;
    while (cin >> ch) {
        if (ch == ' ' || ch == '\n') continue;
        mx = max(mx, ++cnt[ch]);
    }
    vector<vector<char>> to_print(mx + 1, vector<char>(cnt.size(), ' '));
    for (size_t i = 0; auto [ch_, cnt_] : cnt) {
        to_print[mx][i] = ch_;
        for (int j = 0; j < cnt_; ++j) to_print[mx - 1 - j][i] = '#';
        ++i;
    }
    for (auto &r : to_print) {
        for (auto c : r) cout << c;
        cout << '\n';
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