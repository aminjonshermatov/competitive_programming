//
// Created by aminjon on 8/30/22.
//
#include "bits/stdc++.h"

using namespace std;

const int MAX_N = 501;
vector<int> adj[MAX_N];
vector<int> prev_, next_;

enum class State : uint8_t {
    UNVISITED, ACTIVE, SEEN
};

vector<State> state;
int N, M;
bool has_cycle = false;

void dfs(int from) {
    state[from] = State::ACTIVE;

    for (auto to : adj[from]) {
        if (state[to] == State::ACTIVE) {
            if (!has_cycle) next_[from] = to;
            has_cycle = true;
            return;
        }
        if (state[to] == State::UNVISITED) {
            next_[from] = to;
            prev_[to] = from;
            dfs(to);
        }
    }
    state[from] = State::SEEN;
}

auto main() -> int32_t {
    cin >> N >> M;

    state.assign(N + 1, State::UNVISITED);
    for (int i = 0; i < M; ++i) {
        int p, q; cin >> p >> q;

        if (p == q) {
            cout << "YES\n1\n" << p << '\n';
            return 0;
        }
        adj[p].emplace_back(q);
    }

    int i;
    for (i = 1; i <= N && !has_cycle; ++i) {
        prev_.assign(N + 1, -1);
        next_.assign(N + 1, -1);
        dfs(i);
    }

    cout << (has_cycle ? "YES" : "NO") << '\n';
    if (has_cycle) {
        vector<int> ans;
        int k = i;
        do {
            ans.push_back(k);
            k = next_[k];
        } while (k != i);

        cout << ans.size() << '\n';
        for (auto it : ans) cout << it << ' ';
    }
}