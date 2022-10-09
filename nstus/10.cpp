//
// Created by aminjon on 10/9/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll inf = 1e15;

struct Node {
    Node *left, *right;
    ll val;
    ll priority;
    ll size;
    bool ok;
    ll mn, mx;

    explicit Node(ll val_ = 0)
            : val{val_}
            , left{nullptr}
            , right{nullptr}
            , size{1}
            , ok{true}
            , priority{(rand() << 16) ^ rand()}
            , mn{inf}
            , mx{-inf} {}
};

ll size(Node *node) {
    if (node == nullptr) return 0;
    return node->size;
}

ll min_(Node *node) {
    if (node == nullptr) return inf;
    return node->mn;
}

ll max_(Node *node) {
    if (node == nullptr) return -inf;
    return node->mx;
}

bool is_sorted(Node* node) {
    if (node == nullptr) return true;
    return node->ok;
}

void push(Node *node) {
    if (node == nullptr) return;
    node->mn = min(min(node->val, min_(node->left)), min_(node->right));
    node->mx = max(max(node->val, max_(node->left)), max_(node->right));
}

void update(Node *node) {
    if (node == nullptr) return;
    push(node->left);
    push(node->right);
    node->size = 1 + size(node->left) + size(node->right);
    node->ok = max_(node->left) <= min_(node->right)
            && (node->left == nullptr || node->left->ok)
            && (node->right == nullptr || node->right->ok);
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

pair<Node*, Node*> split(Node *root, ll sz) {
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
ll N;
vector<ll> A, left_, right_;

void inorder(Node* node, vector<ll> &to) {
    if (node == nullptr) return;
    inorder(node->left, to);
    to.emplace_back(node->val);
    inorder(node->right, to);
}

// [l, r), 0 based
bool range_is_sorted(ll l, ll r) {
    auto [node_l, R] = split(root, r);
    auto [L, mid] = split(node_l, l);

    bool ans = is_sorted(mid);

    if (!ans) {
        left_.clear();
        inorder(mid->left, left_);
        right_.clear();
        inorder(mid->right, right_);

//        cout << "left: ";
//        for(auto a : left_) cout << a << ' ';
//        cout << '\n';
//        cout << "right: ";
//        for(auto a : right_) cout << a << ' ';
//        cout << '\n';

        bool r_ = false;
        if (!left_.empty() && !mid->left->ok) {
            r_ = true;
            left_.emplace_back(mid->val);
            sort(left_.begin(), left_.end());
        }
        if (!right_.empty() && !mid->right->ok) {
            r_ = true;
            right_.emplace_back(mid->val);
            sort(right_.begin(), right_.end());
        }

        ll i = 0, j = 0;
        const ll n_l(left_.size());
        const ll n_r(right_.size());

        Node* newR = nullptr;
        while (i < n_l && j < n_r) {
            if (r_) {
                if (left_[i] < right_[j])   newR = merge(newR, new Node{left_[i++]});
                else                        newR = merge(newR, new Node{right_[j++]});
            } else {
                auto mn = min(min(mid->val, left_[i]), right_[j]);
                if (mn == mid->val) {
                    r_ = true;
                    newR = merge(newR, new Node{mid->val});
                } else if (mn == left_[i]) newR = merge(newR, new Node{left_[i++]});
                else newR = merge(newR, new Node{right_[j++]});
            }
        }
        while (i < n_l) {
            if (r_ || left_[i] < mid->val) newR = merge(newR, new Node{left_[i++]});
            else {
                r_ = true;
                newR = merge(newR, new Node{mid->val});
            }
        }
        while (j < n_r) {
            if (r_ || right_[j] < mid->val) newR = merge(newR, new Node{right_[j++]});
            else {
                r_ = true;
                newR = merge(newR, new Node{mid->val});
            }
        }

        mid = newR;
    }

    root = merge(merge(L, mid), R);

    return ans;
}

auto main() -> int {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll M;
    cin >> N >> M;
    A.resize(N);

    for (ll i = 0; i < N; ++i) {
        cin >> A[i];
        root = merge(root, new Node{A[i]});
    }

    for (ll i = 0; i < M; ++i) {
        ll l, r;
        cin >> l >> r;
        write(root);
        cout << '\n';
        cout << (range_is_sorted(l - 1, r) ? "YES" : "NO") << '\n';
        write(root);
        cout << "\n\n";
    }
}