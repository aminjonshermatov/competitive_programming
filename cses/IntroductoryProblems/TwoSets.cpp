#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define all(x) (x).begin(), (x).end()

using namespace std;

void solve() {
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    uint64_t n; cin >> n;

    uint64_t sum = n * (n + 1) >> 1;

    if (sum & 1) cout << "NO";
    else {
        cout << "YES\n";
        auto part = sum >> 1;

        vector<int> nums(n);
        iota(all(nums), 1);

        int c = 0;
        uint64_t cur = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (cur == part) break;
            if (cur + nums[i] > part) continue;

            cur += nums[i];
            nums[i] *= -1;
            ++c;
        }

        cout << c << '\n';
        for (const auto num : nums) if (num < 0) cout << -num << ' ';
        cout << '\n';

        cout << n - c << '\n';
        for (const auto num : nums) if (num > 0) cout << num << ' ';
        cout << '\n';
    }
    cout << '\n';

    return 0;
}