//
// Created by aminjon on 10/15/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using mat_t = array<array<ll, 2>, 2>;

ll mod;

struct segtree {

	ll size;
	vector<mat_t> tree;

	static constexpr mat_t ZERO = {1,0,0,1};

	void init(ll n) {
		size = 1;
		while (size < n) size <<= 1;
		tree.assign(2 * size - 1, ZERO);
	}

	mat_t mult_m(const mat_t &l, const mat_t &r) {
        mat_t res = {0,0,0,0};
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    res[i][j] += (l[i][k] * r[k][j]) % mod;
                    res[i][j] %= mod;
                }
            }
        }

		return res;
	}

	void build(vector<mat_t> &a, ll x, ll lx, ll rx) {
		if (rx - lx == 1) {
			if (lx < a.size()) tree[x] = a[lx];
			return;
		}

		ll mid = lx + (rx - lx) / 2;
		build(a, 2 * x + 1, lx, mid);
		build(a, 2 * x + 2, mid, rx);
		tree[x] = mult_m(tree[2 * x + 1], tree[2 * x + 2]);
	}

	void build(vector<mat_t> &a) {
		init((ll)a.size());
		build(a, 0, 0, size);
	}

	mat_t mult(ll l, ll r, ll x, ll lx, ll rx) {
		if (l >= rx || r <= lx) return ZERO;
		if (l <= lx && rx <= r) return tree[x];

		ll mid = lx + (rx - lx) / 2;
        auto lm = mult(l, r, 2 * x + 1, lx, mid);
        auto rm = mult(l, r, 2 * x + 2, mid, rx);
		return mult_m(lm, rm);
	}

	mat_t mult(ll l, ll r) {
		return mult(l, r, 0, 0, size);
	}

};

void print_m(const mat_t &m) {
	for (auto &r : m) {
		for (auto c : r) {
			cout << c << ' ';
		}
		cout << '\n';
	}
}

auto solve() {
	ll n, m;
	cin >> mod >> n >> m;

	vector<mat_t> A(n), res(m);

	for (auto &mat : A) {
		for (auto &r : mat)
			for (auto &c : r) cin >> c;
	}

	segtree st;
	st.build(A);

	/*
	print_m(st.ZERO);
	cout << "\n\n";

	for (auto &ma : st.tree) {
		print_m(ma);
		cout << '\n';
	}
	cout << "\n\n";
	*/

	for (int i = 0; i < m; ++i) {
		int l, r;
		cin >> l >> r;

		res[i] = st.mult(--l, r);
	}

    for (auto &mat : res) {
        for (auto &row : mat) {
            for (auto &c : row) {
                cout << c << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    solve();
}
