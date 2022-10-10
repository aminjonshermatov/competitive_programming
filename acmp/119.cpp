#include "bits/stdc++.h"

using namespace std;

using ll = long long;

struct my_time_t {
    ll h, m, s;
};

void solve() {
    ll N;
    cin >> N;

    vector<my_time_t> A(N);
    for (ll i = 0; i < N; ++i) {
        cin >> A[i].h >> A[i].m >> A[i].s;
    }

    sort(A.begin(), A.end(), [](my_time_t &l, my_time_t &r) {
        if (l.h != r.h) return l.h < r.h;
        if (l.m != r.m) return l.m < r.m;
        return l.s < r.s;
    });

    for (auto &a : A) {
        cout << a.h << ' ' << a.m << ' ' << a.s << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    solve();

    return 0;
}