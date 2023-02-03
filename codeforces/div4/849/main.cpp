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

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    ll n, c; cin >> n >> c;
    ll C = c;
    using el_t = tuple<ll, int, bool>; // (val, is_from_left);
    vector<el_t> evs(2 * n);
    rep(i, n) {
        ll x; cin >> x;
        evs[2 * i]      = tuple(x + i + 1, i, true);
        evs[2 * i + 1]  = tuple(x + n - i, i, false);
    }

    sort(all(evs));
    vector<bool> used(n, false);
    bool any_l = false;
    map<ll, int> inserted;
    for (auto [cost, idx, is_from_left] : evs) {
        if (used[idx]) continue;
        auto mn = min(c, cost);
        if (mn == cost) used[idx] = true, any_l |= is_from_left, inserted.emplace(cost, idx);
        else break;
        c -= mn;
    }
    if (!any_l) {
        pll mn(inf, -1);
        for (auto [cost, idx, is_from_left] : evs) {
            if (!is_from_left || used[idx]) continue;
            if (mn.fi > cost) mn = pair(cost, idx);
        }
        if (mn.fi > C) goto ans;
        auto it = inserted.lower_bound(mn.fi);
        if (it == inserted.end()) {
            ll cur_s = c;
            for (auto [cost, idx, is_from_left] : evs) {
                if (is_from_left) continue;
                used[idx] = false;
                if ((cur_s += cost) >= mn.fi) break;
            }
            if (cur_s >= mn.fi) used[mn.se] = true;
        } else {
            used[it->se] = false;
            used[mn.se] = true;
        }
    }
ans:
    //rep(i, n) cout << used[i] << " \n"[i == n - 1];
    cout << count(all(used), true) << '\n';
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
