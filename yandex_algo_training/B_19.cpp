#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<ld>::max();
inline constexpr auto ninf = numeric_limits<ld>::min();

using pii = pair<int, int>;

struct heap {
    int len = 0;
    vector<int> vals;

    void insert(int x) {
        if (len >= vals.size()) vals.emplace_back();
        vals[len] = x;
        sift_up(len++);
    }

    int erase() {
        assert(!vals.empty());
        auto res = vals.front();
        swap(vals[0], vals[--len]);
        sift_down(0);
        return res;
    }

    void sift_up(int idx) {
        while (idx > 0 && vals[(idx - 1) / 2] < vals[idx]) {
            swap(vals[(idx - 1) / 2], vals[idx]);
            idx = (idx - 1) / 2;
        }
    }

    void sift_down(int idx) {
        int maxIdx = idx;

        int l = idx * 2 + 1;
        if (l < len && vals[l] > vals[maxIdx])
            maxIdx = l;

        int r = idx * 2 + 2;
        if (r < len && vals[r] > vals[maxIdx])
            maxIdx = r;

        if (maxIdx != idx) {
            swap(vals[idx], vals[maxIdx]);
            sift_down(maxIdx);
        }
    }
};

void solve() {
    int n; cin >> n;
    heap hp;
    while (n--) {
        char cmd; cin >> cmd;
        if (cmd == '0') {
            int x; cin >> x;
            hp.insert(x);
        } else {
            cout << hp.erase() << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}