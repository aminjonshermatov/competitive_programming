// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;
using namespace __gnu_pbds;

typedef long long           ll;
typedef long double         ld;
typedef pair<ll, ll>        pll;
typedef pair<int, int>      pii;
typedef pair<ll, int>       pli;
typedef pair<int, ll>       pil;
typedef unsigned long long  ull;

#define fi      first
#define se      second
#define P       pair
#define mp      make_pair
#define pb      push_back
#define eb      emplace_back
#define all(x)  (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x)   (ll)((x).size())

#define rep(i, b)       for (auto i = 0; (i) < (b); ++(i))
#define forr(el, cont)  for (auto &(el) : (cont))

template<typename T>             using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename K, typename V> using gp_ht = gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>, linear_probe_fn<>, hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<>, true>>;

const ll inf = 1e9;
const ll MOD = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

struct segtree {

    vector<pii> tree;
    int size;

    void init(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, {0, 0});
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < a.size()) tree[x] = {a[lx], 0};
            return;
        }
        int mid = lx + (rx - lx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);
        array<int, 4> temp{};
        temp[0] = tree[2 * x + 1].fi;
        temp[1] = tree[2 * x + 1].se;
        temp[2] = tree[2 * x + 2].fi;
        temp[3] = tree[2 * x + 2].se;
        sort(rall(temp));
        tree[x].fi = temp[0];
        tree[x].se = temp[1];
    }

    void build(vector<int> &a) {
        init(sz(a));
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = {v, 0};
            return;
        }
        int mid = lx + (rx - lx) / 2;
        if (i < mid)    set(i, v, 2 * x + 1, lx, mid);
        else            set(i, v, 2 * x + 2, mid, rx);
        array<int, 4> temp{};
        temp[0] = tree[2 * x + 1].fi;
        temp[1] = tree[2 * x + 1].se;
        temp[2] = tree[2 * x + 2].fi;
        temp[3] = tree[2 * x + 2].se;
        sort(rall(temp));
        tree[x].fi = temp[0];
        tree[x].se = temp[1];
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    pii max_(int l, int r, int x, int lx, int rx) {
        if (l >= rx || r <= lx) return {0, 0};
        if (l <= lx && rx <= r) return tree[x];

        int mid = lx + (rx - lx) / 2;
        auto lhs = max_(l, r, 2 * x + 1, lx, mid);
        auto rhs = max_(l, r, 2 * x + 2, mid, rx);
        if (lhs.fi > rhs.fi) return lhs;
        return rhs;
    }

    pii max_(int l, int r) {
        return max_(l, r, 0, 0, size);
    }

};

void solve() {
    int n; cin >> n;
    
    vector<int> A(n);
    map<int, int> idx;
    rep(i, n) cin >> A[i], idx[A[i]] = i;

    if (n == 2) {
        if (A[0] == 1) {
            cout << 1 << '\n';
            return;
        }
        cout << 0 << '\n';
        return;
    }

    if (is_sorted(all(A))) {
        cout << 1 << '\n';
        return;
    }

    segtree st;
    st.build(A);

    int ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        auto [mx1, mx2] = st.max_(0, i);
        if (mx2 < A[i]) break;

        auto pid = idx[mx1];
        st.set(pid, A[i]);
        st.set(i, mx1);
        A[pid] = A[i];
        idx[A[i]] = pid;
        A[i] = mx1;
        idx[mx1] = i;
        ++ans;
    }
    cout << ans << '\n';
}

bool is_multi = true;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T = 1;
    if (is_multi) cin >> T;
    for (int tc = 1; tc <= T; ++tc) solve();

    return 0;
}
