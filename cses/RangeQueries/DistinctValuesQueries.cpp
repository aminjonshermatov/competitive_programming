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

template<typename T>             using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename K, typename V> using gp_ht = gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>, linear_probe_fn<>, hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<>, true>>;

inline constexpr auto  inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();
inline constexpr int MOD = 1e9 + 7;
inline const ld pi = ::atan2(0, -1);
inline constexpr ld eps = 1e-6;

namespace persistent_segment_tree {
    template<typename T> struct Node {
        T val;
        Node *left, *right;

        Node() : Node(-1) { }
        explicit Node(T val_, Node<T> *left_ = nullptr, Node<T> *right_ = nullptr) : val(val_), left(left_), right(right_) { }
    };

    template <typename T> Node<T> EMPTY_NODE = Node<T>(T(0));

    template <typename T> inline Node<T>* get_node(Node<T> *node) { return node == nullptr ? &EMPTY_NODE<T> : node; }
    template <typename T> inline Node<T>* unite(Node<T> *left, Node<T> *right) { return new Node<T>(left->val + right->val, left, right); }


    template<typename T> Node<T>* build(vector<T> &A, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < A.size()) return new Node<T>(A[lx]);
            return nullptr;
        }

        auto mid = lx + (rx - lx) / 2;
        return unite(get_node(build(A, lx, mid)), get_node(build(A, mid, rx)));
    }

    template<typename T> Node<T>* modify(int idx, T new_v, Node<T> *cur, int lx, int rx) {
        if (rx - lx == 1) return new Node<T>(new_v + get_node(cur)->val);

        auto mid = lx + (rx - lx) / 2;
        Node<T> new_node = Node<T>();
        assert(cur != nullptr);
        if (idx < mid)  new_node.left =  modify(idx, new_v, cur->left, lx, mid), new_node.right = cur->right;
        else            new_node.right = modify(idx, new_v, cur->right, mid, rx), new_node.left = cur->left;
        return unite(get_node(new_node.left), get_node(new_node.right));
    }

    template<typename T> Node<T>* get(int l, int r, Node<T> *cur, int lx, int rx) {
        if (l >= rx || r <= lx) return nullptr;
        if (l <= lx && rx <= r) return cur;

        auto mid = lx + (rx - lx) / 2;
        assert(cur != nullptr);
        return unite(get_node(get(l, r, cur->left, lx, mid)), get_node(get(l, r, cur->right, mid, rx)));
    }

    template<typename T> T get_safe(int l, int r, Node<T> *cur, int lx, int rx) {
        return get_node(get(l, r, cur, lx, rx))->val;
    }

};
using namespace persistent_segment_tree;

void solve() {
    int n, q; cin >> n >> q;
    vector<int> A(n);
    forr(a, A) cin >> a;

    vector<int> B = A;
    sort(all(B));
    B.resize(unique(all(B)) - B.begin());
    rep(i, n) A[i] = lower_bound(all(B), A[i]) - B.begin();

    int lg_n = 1;
    while (lg_n < n) lg_n <<= 1;

    vector<Node<int>*> roots(n); // ..r]
    vector<int> ones(n, 1);
    vector<int> prev(sz(A), -1);
    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            roots[i] = build(ones, 0, lg_n);
        } else {
            roots[i] = roots[i - 1];
            if (prev[A[i]] != -1) roots[i] = modify(prev[A[i]], -1, roots[i], 0, lg_n);
        }
        prev[A[i]] = i;
    }

    rep(_, q) {
        int a, b; cin >> a >> b;
        cout << get_safe(a - 1, b, roots[b - 1], 0, lg_n) << '\n';
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