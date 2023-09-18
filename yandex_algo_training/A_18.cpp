#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();

using pii = pair<int, int>;

struct segtree {
    int n;
    vector<int> tree;

    explicit segtree(int len) {
        n = 1;
        while (n < len) n <<= 1;
        tree.assign(2 * n - 1, ninf);
    }

    void set(int v, int i, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = v;
            return;
        }

        auto mid = lx + (rx - lx) / 2;
        if (i < mid) set(v, i, 2 * x + 1, lx, mid);
        else set(v, i, 2 * x + 2, mid, rx);
        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void set(int i, int v) {
        set(v, i, 0, 0, n);
    }

    int get(int i, int x, int lx, int rx) {
        if (rx - lx == 1) return tree[lx];
        auto mid = lx + (rx - lx) / 2;
        if (i < mid) return get(i, 2 * x + 1, lx, mid);
        return get(i, 2 * x + 2, mid, rx);
    }

    int get(int i) {
        return get(i, 0, 0, n);
    }

    int first_less(int v, int x, int lx, int rx) {
        if (tree[x] >= v) return -1;
        if (rx - lx == 1) return lx;
        auto mid = lx + (rx - lx) / 2;
        auto xx = first_less(v, 2 * x + 1, lx, mid);
        if (xx == -1) xx = first_less(v, 2 * x + 2, mid, rx);
        return xx;
    }

    int first_less(int v) {
        return first_less(v, 0, 0, n);
    }
};

#define BAD(x) { bad = true; xx = x; continue; }

void solve() {
    int k, n; cin >> k >> n;
    vector<int> ans;
    bool bad = false;
    int xx;
    segtree st(k);
    for (int i = 1; i <= n; ++i) {
        int l, r; cin >> l >> r;
        if (bad) continue;
        auto x = st.first_less(l);
        if (x == -1 || x >= k) BAD(i);
        st.set(x, r);
        ans.emplace_back(x + 1);
    }
    if (bad) {
        cout << 0 << ' ' << xx;
        return;
    }
    assert(ans.size() == n);
    for (auto x : ans) cout << x << ' ';
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