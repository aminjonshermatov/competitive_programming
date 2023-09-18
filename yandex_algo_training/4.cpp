#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;

void solve() {
    i64 N, K, r_, c_;
    cin >> N >> K >> r_ >> c_;

    auto ok    = [&](i64 x) { return clamp(x, i64(1), N) == x; };
    auto print = [&](i64 x) { cout << (x + 1) / 2 << ' ' << 2 - (x & 1); };
    auto cmp   = [&](i64 cur, i64 lhs, i64 rhs) -> bool {
        i64 px = 2 - (cur & 1), py = (cur + 1) / 2;
        i64 lx = 2 - (lhs & 1), ly = (lhs + 1) / 2;
        i64 rx = 2 - (rhs & 1), ry = (rhs + 1) / 2;
        return (abs(px - lx) + abs(py - ly)) < (abs(px - rx) + abs(py - ry));
    };

    i64 petya = 2 * r_ + c_ - 2;
    i64 prv = petya - K;
    i64 nxt = petya + K;
    if (ok(prv) && ok(nxt)) {
        if (cmp(petya, prv, nxt)) print(prv);
        else print(nxt);
    }
    else if (ok(prv)) print(prv);
    else if (ok(nxt)) print(nxt);
    else cout << -1;
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}