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

#define rep(i, a, b)    for (auto i = (a); (i) < (b); ++(i))
#define forr(el, cont)  for (auto &(el) : (cont))
#define read(k)         ll k; cin >> k

template<typename T = ll> using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

const ll inf = 1e15;
const ll MOD = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-7;

void solve() {
    int n, k; cin >> n >> k;

    vector<ll> A(k);
    forr(a, A) cin >> a, --a;
    vector<pll> P(n);
    forr(p, P) cin >> p.fi >> p.se;

    vector<bool> seen(n);
    auto f = [&](ld r) -> bool {
        fill(all(seen), false);
        forr(a, A) seen[a] = true;
        forr(a, A) {
            rep(i, 0, n) {
                if (seen[i]) continue;
                auto d = (P[i].fi - P[a].fi) * (P[i].fi - P[a].fi) + (P[i].se - P[a].se) * (P[i].se - P[a].se);
                if (d <= r * r) seen[i] = true;
            }
        }

        return all_of(all(seen), [](auto el) { return el; });
    };

    ld lo = 1e-6, hi = 4e6;
    while (hi - lo > eps) {
        auto mid = lo + (hi -lo) / 2;

        if (f(mid)) hi = mid;
        else lo = mid;
    }
    cout << fixed << setprecision(9) << lo;
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
