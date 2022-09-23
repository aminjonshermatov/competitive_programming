//
// Created by aminjon on 9/23/22.
//
#include "bits/stdc++.h"

using namespace std;

int main() {
    int T; cin >> T;

    while (T--) {
        int N; cin >> N;
        string S; cin >> S;

        int mn = 0, pl = 0;
        priority_queue<char> pq;

        for (auto ch : S) {
            if (ch == '+') ++pl;
            else if (ch == '-') ++mn;
            else pq.push(ch);
        }

        while (pq.size() > pl + mn) cout << pq.top(), pq.pop();

        while (!pq.empty()) {
            if (pl > 0) cout << '+', --pl;
            else cout << '-', --mn;

            cout << pq.top(), pq.pop();
        }
        cout << '\n';
    }

    return 0;
}
