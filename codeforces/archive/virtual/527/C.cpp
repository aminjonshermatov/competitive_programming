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

const ll inf = 1e15;
const ll MOD = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

void solve() {
    int n; cin >> n;

    map<int, vector<pair<string, int>>> mm;
    set<char> st;
    rep(_, 0, 2*n - 2) {
        string s; cin >> s;
        mm[sz(s)].eb(s, _);
        forr(c, s) st.insert(c);
    }

    map<string, int> ss;
    rep(i, 1, n) {
        for (auto &[a, i1] : mm[i]) for (auto &[b, i2] : mm[n - i]) if (i1 != i2) { ++ss[a+b]; ++ss[b+a]; }
    }
    int mx = 0;
    string res;
    for (auto &[s, c] : ss) if (mx < c && [&](){
        set<char> temp;
        forr(ch, s) temp.insert(ch);
        return sz(temp) >= sz(st);
    }()) mx = c, res = s;
    //for (auto &[s, c] : ss) cout << c << ' ' << s << '\n';
    vector<pair<int, char>> ans;
    ans.reserve(2*n - 2);
    for (auto &it : std::ranges::reverse_view(mm)) {
        int p = sz(it.second)/2;
        for (auto &info : it.second) {
            if (res.starts_with(info.fi) && p > 0) {
                ans.eb(info.se, 'P');
                --p;
            } else ans.eb(info.se, 'S');
        }
    }
    sort(all(ans));
    //cout << res << '\n';
    for (auto [_, t] : ans) cout << t;
    cout << '\n';
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
