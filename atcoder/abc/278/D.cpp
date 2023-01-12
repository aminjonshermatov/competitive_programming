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

    static inline constexpr T DEFAULT_VALUE = T(numeric_limits<T>::min());
    static inline constexpr T NO_OPERATION = T(0);

    template<typename U> struct node {
        U val;
        U lazy; // <val, isSet> 0-add, 1-set
        bool hasLazy;
        bool isSet;
        int right;

        void apply([[maybe_unused]] int l, [[maybe_unused]] int r, U v, bool isSet_) {
            if (isSet_) {
                val = v;
                lazy = v;
            } else {
                val += v;
                lazy += v;
            }
            isSet = isSet_;
            hasLazy = true;
        }

        template<typename V> static node unite(const node<V> &a, const node<V> &b) {
            return node{
                max(a.val, b.val),
                NO_OPERATION,
                false,
                false,
                b.right
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
        if (rx - lx == 1 || !tree[x].hasLazy) return;

        int mid = lx + (rx - lx) / 2;
        tree[2 * x + 1].apply(lx, mid, tree[x].lazy, tree[x].isSet);
        tree[2 * x + 2].apply(mid, rx, tree[x].lazy, tree[x].isSet);
        tree[x].lazy = NO_OPERATION;
        tree[x].hasLazy = false;
    }

    inline void pull(int x) {
        tree[x] = node<T>::unite(tree[2 * x + 1], tree[2 * x + 2]);
    }

    template<typename U = T>
    void build(vector<U> &A, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < A.size()) tree[x] = {A[lx], NO_OPERATION, false, false, lx};
            return;
        }

        int mid = lx + (rx - lx) / 2;
        build(A, 2 * x + 1, lx, mid);
        build(A, 2 * x + 2, mid, rx);
        pull(x);
    }

    void modify(int l, int r, T v, bool isSet, int x, int lx, int rx) {
        push(x, lx, rx);
        if (l >= rx || r <= lx) return;
        if (l <= lx && rx <= r) {
            tree[x].apply(lx, rx, v, isSet);
            return;
        }

        int mid = lx + (rx - lx) / 2;
        modify(l, r, v, isSet, 2 * x + 1, lx, mid);
        modify(l, r, v, isSet, 2 * x + 2, mid, rx);
        pull(x);
    }

    void modify(int l, int r, int v, bool isSet) {
        modify(l, r, v, isSet, 0, 0, size);
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

    template<typename Op> T get_first(T v, int i, int x, int lx, int rx, Op &op) {
        if (!op(tree[x].val, v) || tree[x].right < i) return -1;
        if (rx - lx == 1) return lx;

        int mid = lx + (rx - lx) / 2;
        auto res = get_first(v, i, 2 * x + 1, lx, mid, op);
        if (res == -1) res = get_first(v, i, 2 * x + 2, mid, rx, op);
        return res;
    }

    template<typename Op> T get_first(T v, int i, Op &op) {
        return get_first(v, i, 0, 0, size, op);
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
    int n; cin >> n;
    vector<int> A(n);
    forr(_xxx_, A) cin >> _xxx_;

    segment_tree<ll> st(A);

    int Q; cin >> Q;

    rep(_, Q) {
        char t; cin >> t;

        if (t == '1') {
            int x; cin >> x;
            st.modify(0, n, x, true);
        } else if (t == '2') {
            int i, q; cin >> i >> q;
            st.modify(i-1, i, q, false);
        } else if (t == '3') {
            int i; cin >> i;
            cout << st.get(i-1, i) << '\n';
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
