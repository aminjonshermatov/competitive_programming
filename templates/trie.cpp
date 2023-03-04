//
// Created by aminjon on 2/21/23.
//

#include <bits/stdc++.h>

using namespace std;

template<size_t N = 26> struct Node {
    array<Node*, N> go{};
    int terminate_count;

    Node() : terminate_count(0) { fill(go.begin(), go.end(), nullptr); }
};

auto *root = new Node();

void add(string_view s) {
    auto cur = root;
    for (auto ch : s) {
        if (cur->go[ch - 'a'] == nullptr) cur->go[ch - 'a'] = new Node();
        cur = cur->go[ch - 'a'];
    }
    ++cur->terminate_count;
}

bool contains(string_view s) {
    auto cur = root;
    for (auto ch : s) {
        if (cur->go[ch - 'a'] == nullptr) return false;
        cur = cur->go[ch - 'a'];
    }
    return cur->terminate_count > 0;
}

void erase(string_view s) {
    auto cur = root;
    for (auto ch : s) {
        if (cur->go[ch - 'a'] == nullptr) return;
        cur = cur->go[ch - 'a'];
    }
    cur->terminate_count = max(0, cur->terminate_count - 1);
}