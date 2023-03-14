// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

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

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

const size_t BLOCK_SIZE = 750u;

void solve() {
    int n, m;
    ll u;
    cin >> n >> m >> u;
    vector<ll> A(n);
    vector<vector<ll>> blocks;
    blocks.emplace_back();
    rep(i, n) {
        cin >> A[i];
        blocks.back().emplace_back(A[i]);
        if (blocks.size() == BLOCK_SIZE) {
            sort(all(blocks.back()));
            blocks.emplace_back();
        }
    }
    if (!blocks.back().empty()) sort(all(blocks.back()));
    blocks.emplace_back();

    auto query = [&](int l, int r, ll v) -> int {
        int L = l / BLOCK_SIZE, R = r / BLOCK_SIZE;
        int k = 0;
        if (L == R) {
            for (int i = l; i <= r; ++i) {
                k += A[i] < v;
            }
        } else {
            for (int i = l; i < (L + 1) * BLOCK_SIZE && i < n; ++i) {
                k += A[i] < v;
            }
            for (int i = R * BLOCK_SIZE; i <= r && i < n; ++i) {
                k += A[i] < v;
            }
            for (int i = L + 1; i < min<int>(R, blocks.size()); ++i) {
                k += lower_bound(all(blocks[i]), v) - blocks[i].begin();
            }
        }
        return k;
    };

    auto upd = [&](int p, ll new_val) -> void {
        if (A[p] == new_val) return ;
        auto old_val = A[p];
        A[p] = new_val;
        auto pp = p / BLOCK_SIZE;
        int pos = 0;
        while (pos < blocks[pp].size() && blocks[pp][pos] < old_val) ++pos;
        blocks[pp][pos] = new_val;
        while (pos + 1 < min(BLOCK_SIZE, blocks[pp].size()) && blocks[pp][pos + 1] > blocks[pp][pos]) {
            swap(blocks[pp][pos], blocks[pp][pos + 1]);
            ++pos;
        }
        while (pos > 0 && blocks[pp][pos - 1] > blocks[pp][pos]) {
            swap(blocks[pp][pos - 1], blocks[pp][pos]);
            --pos;
        }
    };

    rep(_, m) {
        int l, r, p;
        ll v;
        cin >> l >> r >> v >> p;
        --l, --r, --p;

        int k = query(l, r, v);
        upd(p, k * u / (r - l + 1));
    }
    rep(i, n) cout << A[i] << '\n';
}

//#define MEASURE_TIME
bool is_multi = false;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef MEASURE_TIME
    auto start = chrono::steady_clock::now();
#endif
    int T = 1;
    if (is_multi) cin >> T;
    for (int tc = 1; tc <= T; ++tc) solve();
#ifdef MEASURE_TIME
    auto finish = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";
#endif
    return 0;
}
