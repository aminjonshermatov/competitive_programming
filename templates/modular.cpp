//
// Created by aminjon on 1/1/23.
//
#include <bits/stdc++.h>

using namespace std;

const ::int64_t MOD = 1e9 + 7;

template<::int64_t mod = MOD> struct mint {
    ::int64_t x;

    mint() : x(0) { }
    explicit mint(::int64_t _x) {
        _x %= mod;
        if (_x < 0) _x += mod;
        x = _x;
    }

    mint& operator += (const mint &other) {
        x += other.x;
        if (x >= mod) x -= mod;
        return *this;
    }

    mint& operator -= (const mint &other) {
        x += mod - other.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    mint& operator *= (const mint &other) {
        x = x * other.x % mod;
        return *this;
    }
    mint pow(::int64_t pw) const {
        mint res = 1;
        mint cur = *this;
        while(pw) {
            if (pw & 1) res *= cur;
            cur *= cur;
            pw >>= 1;
        }
        return res;
    }
    mint inv() const {
        assert(x != 0);
        ::int64_t t = x;
        ::int64_t res = 1;
        while(t != 1) {
            ::int64_t z = mod / t;
            res = res * (mod - z) % mod;
            t = mod - t * z;
        }
        return res;
    }
    mint& operator /= (const mint &other) { return *this *= other.inv(); }

    mint operator + (const mint &other) const { return mint(*this) += other; }
    mint operator - (const mint &other) const { return mint(*this) -= other; }
    mint operator * (const mint &other) const { return mint(*this) *= other; }
    mint operator / (const mint &other) const { return mint(*this) /= other; }

    bool operator == (const mint &other) const { return x == other.x; }
    bool operator != (const mint &other) const { return x != other.x; }
    bool operator <  (const mint &other) const { return x < other.x; }
};

template<::int64_t mod = MOD> struct Factorials {
    using Mint = mint<mod>;
    vector<Mint> fact, tcaf;

    Factorials() : fact(), tcaf() { }
    explicit Factorials(int n) {
        n += 10;
        fact.assign(n);
        tcaf.assign(n);
        fact[0] = 1;
        for (int i = 1; i < n; i++) fact[i] = fact[i - 1] * i;
        tcaf[n - 1] = fact[n - 1].inv();
        for (int i = n - 1; i > 0; i--) tcaf[i - 1] = tcaf[i] * i;
    }

    Mint C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * tcaf[k] * tcaf[n - k];
    }
};
template<::int64_t mod = MOD> struct Powers {
    using Mint = mint<mod>;
    vector<Mint> pw, wp;

    Powers() : pw(), wp() { }
    Powers(int n, Mint x) {
        n += 10;
        if (x == 0) {
            pw.resize(n);
            pw[0] = 1;
        } else {
            pw.resize(n);
            wp.resize(n);
            pw[0] = wp[0] = 1;
            Mint xi = x.inv();
            for (int i = 1; i < n; i++) {
                pw[i] = pw[i - 1] * x;
                wp[i] = wp[i - 1] * xi;
            }
        }
    }

    Mint pow(int n) { return (n >= 0 ? pw : wp)[abs(n)]; }
};
using Mint = mint<>;