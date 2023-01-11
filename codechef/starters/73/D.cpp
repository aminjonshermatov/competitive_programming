#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

i64 gcd(i64 a, i64 b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

i64 extended_gcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    i64 x1, y1;
    i64 g = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

void solveDiophantine(i64 a, i64 b, i64 c, i64 &x, i64 &y) {
    i64 g = extended_gcd(a, b, x, y);
    if (c % g != 0) {
        puts("Impossible");
        exit(0);
    }

    c /= g;
    x = x * c; y = y * c;
}

int main() {
    auto solve = []() -> void {
        i64 a, b, c;
        cin >> a >> b;
        c = b - a;

        i64 x, y;
        b *= -1;
        solveDiophantine(a, b, c, x, y);

        i64 g = gcd(a, b);
        i64 add = b / g;
        i64 num;

        if (add < 0) num = -x / add;
        else num = (add - x - 1) / add;

        x = x + b / g * num;
        y = y - a / g * num;

        i64 n = abs(x*a + b);
        b *= -1;
        if (n <= 0) n = (a-1)*b + (b-1)*a;
        if (n <= 0 || (n+a)%b || (n+b)%a) n = a*b-a-b;
        if (n <= 0 || (n+a)%b || (n+b)%a) n += a*b;
        assert(n > 0);
        assert((n + a) % b == 0);
        assert((n + b) % a == 0);

        cout << n << '\n';
    };

    int t; cin >> t;
    while (t--) solve();
    return 0;
}
