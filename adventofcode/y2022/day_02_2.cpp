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
const ld eps = 1e-6;

void solve() {
    map<char, int> scores = {{'R', 1}, {'P', 2}, {'S', 3}};
    map<char, char> mapper = {{'A', 'R'}, {'B', 'P'}, {'C', 'S'}, {'X', 'R'}, {'Y', 'P'}, {'Z', 'S'}};
    map<char, map<char, int>> beats {
        {'R', { {'R', 3}, {'S', 6}, {'P', 0} }},
        {'S', { {'R', 0}, {'S', 3}, {'P', 6} }},
        {'P', { {'R', 6}, {'S', 0}, {'P', 3} }}
    };

    map<char, map<char, char>> choose {
        {'R', { {'X', 'S'}, {'Y', 'R'}, {'Z', 'P'} }},
        {'S', { {'X', 'P'}, {'Y', 'S'}, {'Z', 'R'} }},
        {'P', { {'X', 'R'}, {'Y', 'P'}, {'Z', 'S'} }}
    };

    ll ans = 0;
    string line;
    while (getline(cin, line)) {
        char A = mapper[line[0]];
        char B = choose[A][line[2]];
        ans += beats[B][A] + scores[B];
    }

    cout << ans;
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
