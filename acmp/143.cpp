#include "bits/stdc++.h"

using namespace std;

using ll = long long;

int main() {
    string  a, b;
    cin >> a >> b;

    array<string_view, 2> ss = {a, b};
    if (a.size() == b.size()) sort(ss.begin(), ss.end());
    else if (a.size() > b.size()) swap(ss[0], ss[1]);

    const int N(ss[0].size());
    const int M(ss[1].size());
    stack<char> st;
    bool debt = false;

    for (int i = N - 1, j = M - 1; j >= 0; --i, --j) {
        int num = ss[1][j] - '0';
        if (i >= 0) num -= (ss[0][i] - '0');
        if (debt) --num;

        if (num < 0) num += 10, debt = true;
        else debt = false;

        st.push(char(num) + '0');
    }
    while (st.size() > 1 && st.top() == '0') st.pop();

    if (!st.empty() && st.top() != '0' && a != ss[1]) st.push('-');

    string res;
    while(!st.empty()) res.push_back(st.top()), st.pop();

    cout << res << '\n';

    return 0;
}