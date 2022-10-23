#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int k = n / m;
    vector<int> a(n);
    vector<vector<int> > rems(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        rems[a[i] % m].push_back(i);
    }

    long long ans = 0;
    vector<pair<int, int>> freepos;
    for (int i = 0; i < 2 * m; ++i) {
        int cur = i % m;
        while (rems[cur].size() > k) {
            int curr = rems[cur].back();
            rems[cur].pop_back();
            freepos.emplace_back(curr, i);
        }
        while (rems[cur].size() < k && !freepos.empty()) {
            auto [curr, mdp] = freepos.back();
            freepos.pop_back();
            rems[cur].push_back(curr);
            a[curr] += ((i - mdp) % m + m) % m;
            ans += ((i - mdp) % m + m) % m;
        }
    }

    cout << ans << '\n';
    for (int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];

}