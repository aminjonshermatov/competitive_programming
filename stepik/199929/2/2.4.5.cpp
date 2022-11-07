//
// Created by aminjon on 11/7/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

inline constexpr ll inf = numeric_limits<ll>::max();

struct Event {
    ll x, t, idx;
    Event(ll x_, ll t_, ll i) : x{x_}, t{t_}, idx{i} {}
    bool operator<(const Event &ev) const {
        return x < ev.x || (x == ev.x && t < ev.t);
    }
};

auto solve() {
    ll N;
    cin >> N;

    vector<Event> evs;
    evs.reserve(2 * N);
    for (ll i = 0; i < N; ++i) {
        ll l, r;
        cin >> l >> r;
        evs.emplace_back(l, 1, i);
        evs.emplace_back(r, -1, i);
    }
    sort(evs.begin(), evs.end());

    ll open = 0;
    pll last{-1,-1};
    tuple<ll, ll, ll> ans{inf, -1, -1};
    for (auto &ev : evs) {
        if (open > 0
            && ev.t == -1
            && last.first != -1
            && last.second != ev.idx
            && (ev.x - last.first < get<0>(ans) || (ev.x - last.first == get<0>(ans)
                                    && (last.first < get<1>(ans) || ev.x < get<2>(ans))))) {
            ans = {ev.x - last.first, min(last.second, ev.idx), max(last.second, ev.idx)};
        }

        if (ev.t == 1) ++open, last = {ev.x, ev.idx};
        else --open;
    }

    if (get<0>(ans) == inf) cout << 0;
    else cout << get<1>(ans) + 1 << ' ' << get<2>(ans) + 1;
}

int main() {
    solve();
}