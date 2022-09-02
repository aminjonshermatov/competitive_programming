//
// Created by aminjon on 9/2/22.
//
#include "bits/stdc++.h"

using namespace std;

class Stack {
    static inline constexpr size_t N = 101u;
    int len = 0, st[N]{};

public:
    void push(int v) { st[len++] = v; }
    int pop() { return st[--len]; }
    [[nodiscard]] int back() const { return st[len - 1]; }
    [[nodiscard]] size_t size() const { return len; }
    void clear() { len = 0; }
};

auto main() -> int32_t {
    string cmd;

    Stack st{};
    while (cin >> cmd) {
        if (cmd == "push") {
            int v; cin >> v;
            st.push(v);
            cout << "ok";
        } else if (cmd == "pop") cout << st.pop();
        else if (cmd == "back") cout << st.back();
        else if (cmd == "size") cout << st.size();
        else if (cmd == "clear") {
            st.clear();
            cout << "ok";
        } else if (cmd == "exit") { cout << "bye"; break; }
        cout << '\n';
    }
}