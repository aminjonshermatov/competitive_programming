//
// Created by aminjon on 11/14/22.
//
#include <bits/stdc++.h>

using namespace std;

class Dsu {
    vector<int> parent, rank;
public:
    explicit Dsu(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        rank.assign(n, 0);
    }

    auto find(int a) -> int {
        if (parent[a] == a) return a;
        return parent[a] = find(parent[a]);
    }

    auto merge(int a, int b) {
        int pa = find(a);
        int pb = find(b);

        if (pa != pb) {
            if (rank[pa] < rank[pb]) swap(pa, pb);
            parent[pb] = pa;
            if (rank[pa] == rank[pb]) ++rank[pa];
        }
    }
};

auto solve() {
    int n, m;
    cin >> n >> m;

    Dsu dsu(n);
    for (int i = 0; i < m; ++i) {
        string c;
        int p, q;
        cin >> c >> p >> q;
        --p, --q;

        if (c.front() == 'u') {
            dsu.merge(p, q);
        } else {
            cout << (dsu.find(p) == dsu.find(q) ? "YES" : "NO") << '\n';
        }
    }
}

int main() {
    solve();
}