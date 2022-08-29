#include "bits/stdc++.h"

using namespace std;

int main() {
    int N, M; cin >> N >> M;

    map<int, set<int>> ms;
    for (int i = 0; i < M; ++i) {
        int p, q; cin >> p >> q;
        ms[q].insert(p);
        ms[p].insert(q);
    }

    for (int i = 1; i <= N; ++i) {
        cout << ms[i].size() << ' ';
        for (auto ff : ms[i]) cout << ff << ' ';
        cout << '\n';
    }
}