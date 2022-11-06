//
// Created by aminjon on 11/7/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

struct Event {
    ll xl, xr, y, t;

    Event(ll xl_, ll xr_, ll y_, ll t_) : xl{xl_}, xr{xr_}, y{y_}, t{t_} { }

    bool operator<(const Event &ev) const {
        return y < ev.y || (y == ev.y && t > ev.t);
    }
};

auto solve() {
    ll N;
    cin >> N;

    vector<ll> xs;
    xs.reserve(2 * N);
    vector<Event> evs;
    evs.reserve(2 * N);
    for (ll i = 0; i < N; ++i) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        xs.emplace_back(x1);
        xs.emplace_back(x2);
        evs.emplace_back(x1, x2, y1, 1);
        evs.emplace_back(x1, x2, y2, -1);
    }

    sort(xs.begin(), xs.end());
    sort(evs.begin(), evs.end());

    ll ans = 0;
    for (int i = 1; i < 2 * N; ++i) {
        ll open = 0, last;
        for (auto &ev : evs) {
            if (xs[i] <= ev.xl || xs[i - 1] >= ev.xr) continue;
            if (open == 0) last = ev.y;
            open += ev.t;
            if (open == 0) ans += (ev.y - last) * (xs[i] - xs[i - 1]);
        }
    }

    cout << ans;
}

int main() {
    solve();
}