//
// Created by aminjon on 11/14/22.
//
#include <bits/stdc++.h>

using namespace std;

class Dsu {
    vector<int> parent, rank, size_;
    vector<pair<int, int>> min_max;
public:
    explicit Dsu(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        rank.assign(n, 0);
        size_.assign(n, 1);
        min_max.resize(n);
        for (int i = 0; i < n; ++i) min_max[i] = make_pair(i, i);
    }

    auto find(int a) -> int {
        if (parent[a] != a) parent[a] = find(parent[a]);
        return parent[a];
    }

    auto merge(int a, int b) {
        int pa = find(a);
        int pb = find(b);

        if (pa != pb) {
            if (rank[pa] < rank[pb]) swap(pa, pb);
            parent[pb] = pa;
            size_[pa] += size_[pb];
            min_max[pa].first = min(min_max[pa].first, min_max[pb].first);
            min_max[pa].second = max(min_max[pa].second, min_max[pb].second);
            if (rank[pa] == rank[pb]) ++rank[pa];
        }
    }

    auto get_info(int a) -> tuple<int, int, int> {
        int pa = find(a);
        return {min_max[pa].first + 1, min_max[pa].second + 1, size_[pa]};
    }
};

auto solve() {
    int n, m;
    cin >> n >> m;

    Dsu dsu(n);
    for (int i = 0; i < m; ++i) {
        string c;
        cin >> c;

        if (c.front() == 'u') {
            int p, q; cin >> p >> q;
            --p, --q;
            dsu.merge(p, q);
        } else {
            int p; cin >> p;
            --p;

            auto res = dsu.get_info(p);
            cout << get<0>(res) << ' ' << get<1>(res) << ' ' << get<2>(res) << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}