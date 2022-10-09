#include "bits/stdc++.h"

using namespace std;

using ll = long long;

int main() {
    ll N;
    cin >> N;

    for (ll i = 0; i < N; ++i) {
        ll a, b, c;
        char op, eq;
        cin >> a >> op >> b >> eq >> c;
        ll ex;
        if (op == '+') ex = a + b;
        else if (op == '-') ex = a - b;
        else if (op == '*') ex = a * b;

        if (ex == c) cout << "correct";
        else cout << "incorrect\n" << a << ' ' << op << ' ' << b << " = " << ex;
        cout << '\n';
    }

    return 0;
}