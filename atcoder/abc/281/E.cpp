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
#define sz(x)   (ll)(x.size())

#define rep(i, b)       for (auto i = 0; i < b; ++i)
#define forr(el, cont)  for (auto &el : cont)

template<typename T>             using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename K, typename V> using gp_ht = gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>, linear_probe_fn<>, hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<>, true>>;

inline constexpr auto  inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();
inline constexpr int MOD = 1e9 + 7;
inline const ld pi = ::atan2(0, -1);
inline constexpr ld eps = 1e-6;

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> A(n);
    forr(a, A) cin >> a;

    multiset<int> X, Y;
    ll sum = 0;
    vector<ll> ans;
    ans.reserve(n - m + 1);
    rep(i, m) {
        sum += A[i];
        X.insert(A[i]);
        if (sz(X) > k) {
            auto it = prev(X.end());
            sum -= *it;
            Y.insert(*it);
            X.erase(it);
        }
    }
    ans.eb(sum);
    for (int i = m; i < n; ++i) {
        if (A[i] < *--X.end()) {
            auto it = prev(X.end());
            sum -= *it;
            Y.insert(*it);
            X.erase(it);
            sum += A[i];
            X.insert(A[i]);
        } else Y.insert(A[i]);
        
        if (auto it = X.find(A[i - m]); it != X.end()) {
            sum -= *it;
            X.erase(it);
            it = Y.begin();
            sum += *it;
            Y.erase(it);
            X.insert(*it);
        } else Y.erase(A[i - m]);
        ans.eb(sum);
    }
    forr(a, ans) cout << a << ' ';
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