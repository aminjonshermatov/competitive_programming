//
// Created by aminjon on 8/30/22.
//
#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
vector<vector<ll>> g;
vector<ll> parent;
vector<char> used;

ll c_start, c_end;

bool dfs(int v) {
    used[v] = '1';

    for(const auto &to : g[v]) {
        if(used[to] == '1' && parent[v] != to) {
            c_start = to;
            c_end = v;
            return true;
        }
        else if(!used[to]){
            parent[to] = v;
            if(dfs(to))
                return true;
        }
    }
    used[v] = '2';
    return false;
}

int main(){
    int n, m;
    cin >> n >> m;
    g.resize(n + 1);
    parent.resize(n + 1);
    used.resize(n + 1);
    for(int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for(int i = 1; i <= n; ++i) {
        if(!used[i] && dfs(i)) goto cycle;
    }

    cout << "NO";
    return 0;
cycle:
    cout << "YES\n";
    vector<ll> ans;
    ans.reserve(n + 1);

    for(ll v = c_end; v != c_start; v = parent[v]) {
        ans.emplace_back(v);
    }
    ans.emplace_back(c_start);
    cout << ans.size() << '\n';
    for(auto it: ans) cout << it << ' ';
}