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

struct primes {
    ll n;
    vector<ll> lp, pr;

    explicit primes(ll n_) : n(n_) { lp.assign(n + 1, 0); }

    auto find_primes() {
        for (ll i = 2; i <= n; ++i) {
            if (lp[i] == 0) {
                lp[i] = i;
                pr.push_back(i);
            }
            for (ll j = 0; i * pr[j] <= n; ++j) {
                lp[i * pr[j]] = pr[j];
                if (pr[j] == lp[i]) { break; }
            }
        }
    }
};

primes pr(5e7);

ll sqrtll(ll n) {
    ll v = ::sqrtl(n);
    while ((v + 1) * (v + 1) <= n) v++;
    while (v * v > n) v--;
    return v;
}

void solve() {
    ll n; cin >> n;
    if (n == 1) { cout << "1 1\n"; return; }
    for (ll p : pr.pr) {
        auto [q, r] = ::lldiv(n, p);
        if (r != 0) continue;
        auto [qq, rr] = ::lldiv(q, p);
        if (rr == 0) {
            cout << p << ' ' << qq << '\n';
        } else {
            cout << sqrtll(q) << ' ' << p << '\n';
        }
        return;
    }
    cout << "1 " << n << '\n';
}

bool is_multi = true;

int main() {
    auto start = std::chrono::steady_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    pr.find_primes();

    int T = 1;
    if (is_multi) cin >> T;
    for (int tc = 1; tc <= T; ++tc) solve();

    //cout << "t= " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() << '\n';

    return 0;
}
