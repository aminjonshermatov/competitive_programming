#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;

inline constexpr auto inf = numeric_limits<int>::max();

using pii = pair<int, int>;

struct segtree {
    vector<pii> tree;
    int n;

    explicit segtree(vector<int> &A) {
        n = 1;
        while (n < A.size()) n <<= 1;
        tree.assign(2 * n - 1, pair(inf, inf));
        build(A, 0, 0, n);
    }

    void build(vector<int> &A, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < A.size()) tree[x] = pair(A[lx], lx);
            return;
        }

        auto mid = lx + (rx - lx) / 2;
        build(A, 2 * x + 1, lx, mid);
        build(A, 2 * x + 2, mid, rx);
        tree[x] = pair(min(tree[2 * x + 1].first, tree[2 * x + 2].first), tree[2 * x + 2].second);
    }

    int get(int idx, int x, int lx, int rx) {
        if (rx - lx == 1) return tree[x].first;
        auto mid = lx + (rx - lx) / 2;
        if (idx < mid) return get(idx, 2 * x + 1, lx, mid);
        return get(idx, 2 * x + 2, mid, rx);
    }

    int get(int idx) {
        return get(idx, 0, 0, n);
    }

    int first_less(int val, int idx, int x, int lx, int rx) {
        if (tree[x].first >= val || tree[x].second <= idx) return -1;
        if (rx - lx == 1) return lx;
        int mid = lx + (rx - lx) / 2;
        if (auto res = first_less(val, idx, 2 * x + 1, lx, mid); res != -1) return res;
        return first_less(val, idx, 2 * x + 2, mid, rx);
    }

    int first_less(int val, int idx) {
        return first_less(val, idx, 0, 0, n);
    }
};

void solve() {
    int n; cin >> n;
    vector<int> A(n);
    for (auto &a : A) cin >> a;
    segtree st(A);

    //for (int i = 0; i < n; ++i) cout << st.get(i) << " \n"[i + 1 == n];
    for (int i = 0; i < n; ++i) cout << st.first_less(A[i], i) << " \n"[i + 1 == n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}