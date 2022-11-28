#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ranges>

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

const ll inf = 1e9;
const ll MOD = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

void solve() {
    int n; cin >> n;

    vector<int> A(n);
    map<int, int> h;
    int mx = 0;
    forr(a, A) cin >> a, ++h[a], mx = max(mx, a);

    rep(_, 0, 250) {
        bool moved = false;
        rep(i, 1, n) {
            if (A[i] != mx && A[i] == A[i - 1]) {
                --h[A[i]], --h[A[i - 1]];
                if (i & 1) ++h[A[i] += mx - A[i]], ++h[A[i - 1] += mx - A[i - 1]];
                else ++h[A[i] += A[i] - A[i - 2]], ++h[A[i - 1] += A[i - 1] - A[i - 2]];
                mx = max(mx, A[i]);
                moved |= 1;
            }
        }
        if (!moved && h[mx] == n) { cout << "Yes"; return; }
    }
    cout << "No";
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
