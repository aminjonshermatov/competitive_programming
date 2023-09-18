#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<ld>::max();
inline constexpr auto ninf = numeric_limits<ld>::min();

using pii = pair<int, int>;

void solve() {
    int n; cin >> n;
    vector<int> A(n);
    for (auto &a : A) cin >> a;

    auto heapify = [&](auto f, int len, int idx) -> void {
        int mx = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < len && A[left] > A[mx]) mx = left;
        if (right < len && A[right] > A[mx]) mx = right;

        if (mx != idx) {
            swap(A[idx], A[mx]);
            f(f, len, mx);
        }
    };

    for (int i = n / 2 - 1; i >= 0; i--) heapify(heapify, n, i);
    for (int i = n - 1; i >= 0; i--) {
        swap(A[0], A[i]);
        heapify(heapify, i, 0);
    }
    for (auto a : A) cout << a << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}