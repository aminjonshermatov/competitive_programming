//
// Created by aminjon on 8/30/22.
//
#include "bits/stdc++.h"

using namespace std;

const int MAX_N = 501;
vector<int> adj[MAX_N];

enum class State : uint8_t {
    UNVISITED, ACTIVE, SEEN
};

vector<State> state;
int N, M;
bool has_cycle = false;

void dfs(int prev, int from) {
    state[from] = State::ACTIVE;

    for (auto to : adj[from]) {
        if (state[to] == State::ACTIVE && to != prev) {
            has_cycle = true;
            return;
        }
        if (state[to] == State::UNVISITED) dfs(from, to);
    }
    state[from] = State::SEEN;
}

auto main() -> int32_t {
    cin >> N >> M;

    state.assign(N + 1, State::UNVISITED);
    for (int i = 0; i < M; ++i) {
        int p, q; cin >> p >> q;

        adj[p].emplace_back(q);
        adj[q].emplace_back(p);
    }

    for (int i = 1; i <= N && !has_cycle; ++i) {
        dfs(-1, i);
    }

    cout << (has_cycle ? "YES" : "NO");
}