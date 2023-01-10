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

const ll inf = 1e15;
const ll MOD = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

template<typename T = int> struct segment_tree {

    static inline constexpr T DEFAULT_VALUE = T(numeric_limits<T>::max());
    static inline constexpr T NO_OPERATION = T(-1);

    template<typename U> struct node {
        U val;
        U lazy;

        void apply([[maybe_unused]] int l, [[maybe_unused]] int r, U v) {
            val = v;
            lazy = v;
        }

        template<typename V> static node unite(const node<V> &a, const node<V> &b) {
            return node{
                min(a.val, b.val),
                NO_OPERATION
            };
        }
    };

    static inline constexpr node<T> NEUTRAL_ELEMENT = {DEFAULT_VALUE, NO_OPERATION};

    int size;
    vector<node<T>> tree;

    explicit segment_tree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size - 1, NEUTRAL_ELEMENT);
    }

    template<typename U = T> explicit segment_tree(vector<U> &A) : segment_tree(A.size()) {
        build(A, 0, 0, size);
    }

    inline void push(int x, int lx, int rx) {
        if (rx - lx == 1 || tree[x].lazy == NO_OPERATION) return;

        int mid = lx + (rx - lx) / 2;
        tree[2 * x + 1].apply(lx, mid, tree[x].lazy);
        tree[2 * x + 2].apply(mid, rx, tree[x].lazy);
        tree[x].lazy = NO_OPERATION;
    }

    inline void pull(int x) {
        tree[x] = node<T>::unite(tree[2 * x + 1], tree[2 * x + 2]);
    }

    template<typename U = T>
    void build(vector<U> &A, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < A.size()) tree[x] = {A[lx], NO_OPERATION};
            return;
        }

        int mid = lx + (rx - lx) / 2;
        build(A, 2 * x + 1, lx, mid);
        build(A, 2 * x + 2, mid, rx);
        pull(x);
    }

    void modify(int l, int r, T v, int x, int lx, int rx) {
        push(x, lx, rx);
        if (l >= rx || r <= lx) return;
        if (l <= lx && rx <= r) {
            tree[x].apply(lx, rx, v);
            return;
        }

        int mid = lx + (rx - lx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);
        pull(x);
    }

    void modify(int l, int r, int v) {
        modify(l, r, v, 0, 0, size);
    }

    node<T> get(int l, int r, int x, int lx, int rx) {
        push(x, lx, rx);
        if (l >= rx || r <= lx) return NEUTRAL_ELEMENT;
        if (l <= lx && rx <= r) return tree[x];

        int mid = lx + (rx - lx) / 2;
        auto res = node<T>::unite(get(l, r, 2 * x + 1, lx, mid),
                               get(l, r, 2 * x + 2, mid, rx));
        pull(x);
        return res;
    }

    T get(int l, int r) {
        return get(l, r, 0, 0, size).val;
    }

    template<typename U>
    friend ostream& operator<<(ostream &out, const segment_tree<U> &st) {
        for (auto i = 1u, j = 0u; j < st.tree.size(); i <<= 1) {
            auto c = 0u;
            while (c++ < i) out << st.tree[j].val << ',' << st.tree[j++].lazy << ' ';
            out << '\n';
        }
        return out;
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<int> A(n);
    forr(_xxx_, A) cin >> _xxx_;

    segment_tree<int> st(A);
    rep(_, q) {
        char t; cin >> t;

        if (t == '1') {
            int k, u; cin >> k >> u;
            --k;
            st.modify(k, k + 1, u);
        } else if (t == '2') {
            int a, b; cin >> a >> b;
            cout << st.get(--a, b) << '\n';
        }
    }
}

bool is_multi = false;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T = 1;
    if (is_multi) cin >> T;
    for (int tc = 1; tc <= T; ++tc) solve();

    return 0;
}
