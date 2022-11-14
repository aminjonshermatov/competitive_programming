//
// Created by aminjon on 11/14/22.
//
#include <bits/stdc++.h>

using namespace std;

inline constexpr string_view JOIN = "join";
inline constexpr string_view ADD = "add";
inline constexpr string_view GET = "get";

class Dsu {
    vector<int> parent, last;
    vector<vector<int>> exp;
public:
    explicit Dsu(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        last.assign(n, 1);
        exp.assign(n, {0});
    }

    auto find(int a) -> int {
        if (parent[a] != a) parent[a] = find(parent[a]);
        return parent[a];
    }

    auto merge(int a, int b) {
        int pa = find(a);
        int pb = find(b);

        if (pa != pb) {
            if (exp[pa].back() < exp[pb].back()) swap(pa, pb);
            parent[pb] = pa;
            last[pb] = (int)exp[pa].size();
        }
    }

    auto add_exp(int a, int e) {
        int pa = find(a);
        exp[pa].emplace_back(exp[pa].back() + e);
    }

    auto get_exp(int a) -> int {
        int pa = find(a);
        return exp[pa].back() - exp[pa][last[a] - 1];
    }
};

auto solve() {
    int n, m;
    cin >> n >> m;

    Dsu dsu(n);
    while (m--) {
        string c;
        cin >> c;

        if (c == JOIN) {
            int p, q;
            cin >> p >> q;
            dsu.merge(--p, --q);
        } else if (c == ADD) {
            int p, e;
            cin >> p >> e;
            dsu.add_exp(--p, e);
        } else if (c == GET) {
            int p;
            cin >> p;
            cout << dsu.get_exp(--p) << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}