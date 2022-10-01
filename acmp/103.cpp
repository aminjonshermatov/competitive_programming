#include "bits/stdc++.h"

using namespace std;

using ll = long long;

int main() {
    string  a, b;
    cin >> a >> b;
    if (a.size() > b.size()) swap(a, b); // b.size() -> max

    const int N(a.size());
    const int M(b.size());

    int rem = 0;
    for (int i = N - 1, j = M - 1; j >= 0; --i, --j) {
        auto num = (b[j] - '0') + rem;
        if (i >= 0) num += (a[i] - '0');
        b[j] = char(num % 10) + '0';
        rem = num / 10;
    }

    if (rem != 0) b.insert(0, 1, char(rem) + '0');

    cout << b  << '\n';
    return 0;
}