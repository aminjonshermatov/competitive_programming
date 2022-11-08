//
// Created by aminjon on 11/8/22.
//
#include <bits/stdc++.h>

using namespace std;

inline constexpr int MAXN = 10'000;
inline constexpr int MAXK = 6;

void make_poss(int x, array<int, MAXK> &poss) {
    fill(poss.begin(), poss.end(), MAXN);
    int i = 0;
    //if (int h = x / 1'000; h < 9) poss[i++] = (h + 1) * 1'000 + x % 1'000;
    if (x % 10 < 9) poss[i++] = x + 1;
    if (x % 10 > 1) poss[i++] = x - 1;
    poss[i++] = (x % 10) * 1'000 + x / 10;
    poss[i++] = (x % 1'000) * 10 + x / 1'000;
    poss[i++] = ((x / 100) % 10) * 1'000 + (x / 1'000) * 100 + (x % 10) * 10 + ((x / 10) % 10);
}

auto solve() {
    int start, end;
    cin >> start >> end;

    array<bool, MAXN> used{};
    fill(used.begin(), used.end(), false);
    array<int, MAXN> p{};
    fill(p.begin(), p.end(), -1);
    queue<int> q;
    q.emplace(start);
    used[start] = true;
    p[start] = -1;

    array<int, MAXK> poss{};

    vector<int> ans;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        if (cur == end) {
            vector<int> temp;
            int x = end;
            while (x != -1) {
                temp.emplace_back(x);
                x = p[x];
            }
            reverse(temp.begin(), temp.end());
            if (ans.empty() || (temp.size() < ans.size()) || (temp.size() == ans.size() && temp < ans)) {
                ans = temp;
            }
            continue;
        }

        make_poss(cur, poss);
        sort(poss.begin(), poss.end());
        for (auto x : poss) {
            if (x == MAXN) break;

            if (!used[x]) {
                used[x] = true;
                p[x] = cur;
                q.emplace(x);
            }
        }
    }

    for (auto x : ans) cout << x << '\n';
}

int main() {
    solve();
}