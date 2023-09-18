#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<ld>::max();
inline constexpr auto ninf = numeric_limits<ld>::min();

using pii = pair<int, int>;

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

void solve() {
    int n; cin >> n;

    char cmd;
    while (cin >> cmd) {
        if (cmd == '+') {
            int i; cin >> i;
            root = merge(root, new Node(i));
        } else if (cmd == '*') {
            int i; cin >> i;
            auto [l, r] = split(root, (size(root) + 1) / 2);
            root = merge(l, new Node(i));
            root = merge(root, r);
        } else {
            auto [l, r] = split(root, 1);
            root = r;
            cout << l->val << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}