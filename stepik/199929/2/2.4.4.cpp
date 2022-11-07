//
// Created by aminjon on 11/7/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

struct Event {
    ll time, type, idx;
    Event() = default;
    Event(ll t1, ll t2, ll i) : time{t1}, type{t2}, idx{i} {}

    bool operator<(const Event &t) const {
        return time < t.time || (time == t.time && type > t.type);
    }
};

auto solve() {
    ll K, N;
    cin >> K >> N;
    vector<Event> evs;
    evs.reserve(2 * N);
    for (ll i = 0; i < N; ++i) {
        ll e, l;
        cin >> e >> l;
        evs.emplace_back(e, 1, i);
        evs.emplace_back(l, -1, i);
    }
    sort(evs.begin(), evs.end());

    vector<ll> ans(N, -1);
    set<ll> free;
    for (ll i = 0; i < K; ++i) free.emplace(i);
    for (auto ev : evs) {
        if (ev.type == 1) {
            if (free.empty()) { cout << 0 << ' ' << ev.idx + 1 << '\n'; return; }
            auto it = free.begin();
            ans[ev.idx] = *it;
            free.erase(it);
        } else {
            free.insert(ans[ev.idx]);
        }
    }

    for (auto num : ans) cout << num + 1 << '\n';
}

int main() {
    solve();
}