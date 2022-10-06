//
// Created by aminjon on 10/6/22.
//
#include <bits/stdc++.h>

using namespace std;

struct Node {
    Node *left, *right;
    bool reverse;
    int32_t val;
    int32_t priority;
    int32_t size;
    int32_t sum;
    int32_t promise;

    explicit Node(int32_t val_ = 0)
            : val{val_}
            , left{nullptr}
            , right{nullptr}
            , size{1}
            , sum{val}
            , priority{(rand() << 16) ^ rand()}
            , promise{0}
            , reverse{false} {}
};

int32_t size(Node *node) {
    if (node == nullptr) return 0;
    return node->size;
}

int32_t sum(Node *node) {
    if (node == nullptr) return 0;
    return node->sum;
}

void add_promise(Node *node, int32_t p, bool reverse) {
    if (node == nullptr) return;
    node->promise += p;
    node->reverse ^= reverse;
}

void push(Node *node) {
    if (node == nullptr) return;
    node->sum += node->size * node->promise;
    node->val += node->promise;

    if (node->reverse) swap(node->left, node->right);
    add_promise(node->left, node->promise, node->reverse);
    add_promise(node->right, node->promise, node->reverse);
    node->promise = 0;
    node->reverse = false;
}

void update(Node *node) {
    if (node == nullptr) return;
    push(node->left);
    push(node->right);
    node->size = 1 + size(node->left) + size(node->right);
    node->sum = node->val + sum(node->left) + sum(node->right);
}

Node *merge(Node *root_l, Node *root_r) {
    push(root_l);
    push(root_r);
    if (root_l == nullptr) return root_r;
    if (root_r == nullptr) return root_l;

    if (root_l->priority < root_r->priority) {
        root_l->right = merge(root_l->right, root_r);
        update(root_l);
        return root_l;
    } else {
        root_r->left = merge(root_l, root_r->left);
        update(root_r);
        return root_r;
    }
}

pair<Node*, Node*> split(Node *root, int32_t sz) {
    if (root == nullptr) return {nullptr, nullptr};

    push(root);
    if (size(root->left) >= sz) {
        auto [ll, lr] = split(root->left, sz);
        root->left = lr;
        update(root);
        return {ll, root};
    } else {
        auto [rl, rr] = split(root->right, sz - size(root->left) - 1);
        root->right = rl;
        update(root);
        return {root, rr};
    }
}

void write(Node *node) {
    if (node == nullptr) return;
    push(node);
    write(node->left);
    cout << node->val << ' ';
    write(node->right);
}

Node *root = nullptr;

// [l, r), 0 based
void move(int32_t l, int32_t r) {
    auto [node_l, R] = split(root, r);
    auto [L, mid] = split(node_l, l);

    root = merge(merge(mid, L), R);
}

// [l, r), 0 based
int32_t range_sum(int32_t l, int32_t r) {
    auto [node_l, R] = split(root, r);
    auto [L, mid] = split(node_l, l);

    int32_t ans = sum(mid);
    root = merge(merge(L, mid), R);

    return ans;
}

// [l, r), 0 based
void range_add(int32_t l, int32_t r, int32_t q) {
    auto [node_l, R] = split(root, r);
    auto [L, mid] = split(node_l, l);
    add_promise(mid, q, false);
    root = merge(merge(L, mid), R);
}

// [l, r), 0 based
void range_reverse(int32_t l, int32_t r) {
    auto [node_l, R] = split(root, r);
    auto [L, mid] = split(node_l, l);
    add_promise(mid, 0, true);
    root = merge(merge(L, mid), R);
}

auto main() -> int32_t {
    int32_t N;
    cin >> N;

    for (int32_t i = 0; i < N; ++i) {
        int32_t a;
        cin >> a;
        root = merge(root, new Node{a});
    }

    int32_t M;
    cin >> M;
    for (int32_t i = 0; i < M; ++i) {
        char ch;
        cin >> ch;

        if (ch == '?') {
            int32_t l, r;
            cin >> l >> r;
            cout << range_sum(l - 1, r) << '\n';
        } else if (ch == '+') {
            int32_t l, r, q;
            cin >> l >> r >> q;
            range_add(l - 1, r, q);
        } else if (ch == 'r') {
            int32_t l, r;
            cin >> l >> r;
            range_reverse(l - 1, r);
        } else if (ch == 'w') {
            write(root);
            cout << endl;
        }
    }
}