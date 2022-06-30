#include "bits/stdc++.h"

using namespace std;

template <typename T>
istream& operator>>(istream &in, vector<T> &arr) {
    for (auto &it : arr) in >> it;
    return in;
}

template <typename T>
ostream& operator<<(ostream &out, vector<T> &arr) {
    cout << '[';
    for (auto &it : arr) out << it << ' ';
    return out << ']';
}

void solve() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (auto &num : nums) cin >> num;

    int i = 0;
    while (i < n) {
        if (i + 1 < n and nums[i + 1] < nums[i]) {
            if (i + 2 < n and nums[i + 2] < nums[i]) {
                if (nums[i + 1] < nums[i + 2] and ((nums[i] + nums[i + 1]) & 1)) {
                    swap(nums[i], nums[i + 1]);
                } else if (((nums[i + 1] + nums[i + 2]) & 1) and ((nums[i] + nums[i + 1]) & 1)) {
                    swap(nums[i + 2], nums[i + 1]);
                    swap(nums[i], nums[i + 1]);
                }
            } else {
                if ((nums[i] + nums[i + 1]) & 1) swap(nums[i], nums[i + 1]);
            }
        }
        ++i;
    }

    bool isOk = true;
    for (i = 0; i + 1 < n and isOk; ++i) {
        if (nums[i] > nums[i + 1]) isOk = false;
    }

    cout << (isOk ? "YES" : "NO") << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc = 1;
    cin >> tc;

    while (tc--) solve();
}