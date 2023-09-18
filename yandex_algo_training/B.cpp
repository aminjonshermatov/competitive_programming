#include <bits/stdc++.h>

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

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();

struct Event {
    i64 a, dur, idx;
    bool operator<(const Event &other) const {
        if (a != other.a) return dur < other.dur;
        return a < other.a;
    }
};

void solve() {
    int n, w; cin >> n >> w;
    map<i64, deque<Event>> evs;
    for (int i = 0; i < n; ++i) {
        i64 a, dur; cin >> a >> dur;
        evs[a].emplace_back(Event{a, dur, i});
    }
    vector<int> ans;
    int emp = 0;
    while (!evs.empty()) {
        ++emp;
        auto cur = evs.begin()->second.front();
        if (evs.begin()->second.size() == 1) evs.erase(evs.begin());
        else evs.begin()->second.pop_front();
        ans.emplace_back(cur.idx);
        while (!evs.empty() && evs.lower_bound(cur.a + cur.dur) != evs.end()) {
            auto it = evs.lower_bound(cur.a + cur.dur);
            cur = it->second.front();
            if (it->second.size() == 1) evs.erase(it);
            else it->second.pop_front();
            ans.emplace_back(cur.idx);
        }
    }
    cout << emp << '\n';
    assert(ans.size() == n);
    for (int i = 0; i < n; ++i) cout << ans[i] + 1 << " \n"[i + 1 == n];
}

//#define MEASURE_TIME

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef MEASURE_TIME
    auto start = chrono::steady_clock::now();
#endif

    int t = 1;
    //cin >> t;
    while (t--) solve();

#ifdef MEASURE_TIME
    auto finish = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";
#endif
}