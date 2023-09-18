#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;

void solve() {
    int n; cin >> n;
    vector<int> A(n);
    for (auto &a : A) cin >> a;
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());

    int k; cin >> k;
    for (int _ = 0; _ < k; ++_) {
        int p; cin >> p;
        cout << (lower_bound(A.begin(), A.end(), p) - A.begin()) << '\n';
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