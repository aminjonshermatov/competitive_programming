#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;

using pii = pair<int, int>;

void solve() {
    int n; cin >> n;
    vector<int> temp(n);
    for (auto &a : temp) cin >> a;

    queue<vector<int>> q;
    i64 ans = 0;
    q.emplace(temp);
    while (!q.empty()) {
        auto qq = q.front(); q.pop();
        auto sz = int(qq.size());
        auto mn = *min_element(qq.begin(), qq.end());
        ans += i64(1) * mn * (sz - 1);
        for (auto &a : qq) a -= mn;
        int ii = 0;
        if (ii == qq.size()) continue;
        while (true) {
            vector<int> cur;
            while (ii < qq.size() && qq[ii] == 0) ++ii;
            int jj = ii;
            while (jj  + 1 < qq.size() && qq[jj + 1] != 0) ++jj;
            if (jj == qq.size()) --jj;
            for (int k = ii; k <= jj; ++k) cur.emplace_back(qq[k]);
            if (cur.size() > 1) q.emplace(cur);
            if ((ii = jj + 1) >= qq.size()) break;
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