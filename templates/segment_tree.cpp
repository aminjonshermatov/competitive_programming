//
// Created by aminjon on 10/9/22.
//
#include <bits/stdc++.h>

namespace lazy_segment_tree {

template <typename Info, typename Tag>
class LazySegmentTree {
 public:
  static constexpr auto kNpos = static_cast<size_t>(-1);

 public:
  LazySegmentTree() = default;

  explicit LazySegmentTree(std::size_t n) {
    Init(std::vector(n, Info{}));
  }
  LazySegmentTree(std::size_t n, Info info) {
    Init(std::vector(n, info));
  }
  template <typename T>
  explicit LazySegmentTree(const std::vector<T>& init) {
    Init(init);
  }

  template <typename T>
  void Init(const std::vector<T>& init) {
    assert(!init.empty());
    N_ = 1u << (std::bit_width(2 * init.size() - 1) - 1);
    Infos_.assign(2 * N_ - 1, Info{});
    Tags_.assign(2 * N_ - 1, Tag{});

    auto build = [&](auto&& self, std::size_t x, std::size_t lx, std::size_t rx) -> void {
      if (rx - lx == 1u) {
        if (lx < init.size()) {
          Infos_[x] = {init[lx]};
        }
        return;
      }
      const auto mid = lx + (rx - lx) / 2;
      self(self, 2 * x + 1, lx, mid);
      self(self, 2 * x + 2, mid, rx);
      Infos_[x] = Infos_[2 * x + 1] + Infos_[2 * x + 2];
    };
    build(build, 0u, 0u, N_);
  }

  void Modify(std::size_t pos, Info info) {
    ModifyImpl(pos, info, 0u, 0u, N_);
  }
  void Modify(std::size_t ql, std::size_t qr, Tag tag) {
    ModifyImpl(ql, qr, tag, 0u, 0u, N_);
  }

  Info Query(std::size_t ql, std::size_t qr) {
    return QueryImpl(ql, qr, 0u, 0u, N_);
  }
  Info Query(std::size_t pos) {
    return QueryImpl(pos, pos + 1, 0u, 0u, N_);
  }

  template <typename Functor>
  std::size_t FindFirst(std::size_t ql, std::size_t qr, Functor&& functor) {
    return FindFirstImpl(ql, qr, std::move(functor), 0u, 0u, N_);
  }
  template <typename Functor>
  std::size_t FindLast(std::size_t ql, std::size_t qr, Functor&& functor) {
    return FindLastImpl(ql, qr, std::move(functor), 0u, 0u, N_);
  }

 private:
  void Apply(std::size_t x, Tag tag) {
    Infos_[x].Apply(tag);
    Tags_[x].Apply(tag);
  }

  void Push(std::size_t x) {
    Apply(2 * x + 1, Tags_[x]);
    Apply(2 * x + 2, Tags_[x]);
    Tags_[x] = Tag{};
  }

  void Pull(std::size_t x) {
    Infos_[x] = Infos_[2 * x + 1] + Infos_[2 * x + 2];
  }

  void ModifyImpl(std::size_t pos, Info info, std::size_t x, std::size_t lx, std::size_t rx) {
    if (rx - lx == 1u) {
      Infos_[x] = info;
      return;
    }
    Push(x);
    const auto mid = lx + (rx - lx) / 2;
    if (pos < mid) {
      ModifyImpl(pos, info, 2 * x + 1, lx, mid);
    } else {
      ModifyImpl(pos, info, 2 * x + 2, mid, rx);
    }
    Pull(x);
  }

  void ModifyImpl(std::size_t ql, std::size_t qr, Tag tag, std::size_t x, std::size_t lx, std::size_t rx) {
    if (ql >= rx || qr <= lx) {
      return;
    }
    if (ql <= lx && rx <= qr) {
      Apply(x, tag);
      return;
    }
    Push(x);
    const auto mid = lx + (rx - lx) / 2;
    ModifyImpl(ql, qr, tag, 2 * x + 1, lx, mid);
    ModifyImpl(ql, qr, tag, 2 * x + 2, mid, rx);
    Pull(x);
  }

  Info QueryImpl(std::size_t ql, std::size_t qr, std::size_t x, std::size_t lx, std::size_t rx) {
    if (ql >= rx || qr <= lx) {
      return {};
    }
    if (ql <= lx && rx <= qr) {
      return Infos_[x];
    }
    Push(x);
    const auto mid = lx + (rx - lx) / 2;
    return QueryImpl(ql, qr, 2 * x + 1, lx, mid) + QueryImpl(ql, qr, 2 * x + 2, mid, rx);
  }

  template <typename Functor>
  std::size_t FindFirstImpl(
    std::size_t ql, std::size_t qr, Functor&& functor,
    std::size_t x, std::size_t lx, std::size_t rx
  ) {
    if (lx >= qr || rx <= ql || !functor(Infos_[x])) {
      return kNpos;
    }
    if (rx - lx == 1u) {
      return lx;
    }
    Push(x);
    const auto mid = lx + (rx - lx) / 2;

    auto res = FindFirstImpl(ql, qr, std::move(functor), 2 * x + 1, lx, mid);
    if (res == kNpos) {
      res = FindFirstImpl(ql, qr, std::move(functor), 2 * x + 2, mid, rx);
    }
    return res;
  }
  template <typename Functor>
  std::size_t FindLastImpl(
    std::size_t ql, std::size_t qr, Functor&& functor,
    std::size_t x, std::size_t lx, std::size_t rx
  ) {
    if (lx >= qr || rx <= ql || !functor(Infos_[x])) {
      return kNpos;
    }
    if (rx - lx == 1u) {
      return lx;
    }
    Push(x);
    const auto mid = lx + (rx - lx) / 2;

    auto res = FindLastImpl(ql, qr, std::move(functor), 2 * x + 2, mid, rx);
    if (res == kNpos) {
      res = FindLastImpl(ql, qr, std::move(functor), 2 * x + 1, lx, mid);
    }
    return res;
  }

 private:
  std::size_t N_{0};
  std::vector<Info> Infos_;
  std::vector<Tag> Tags_;
};

class Tag {
 public:
  void Apply(auto&& tag) {
    Val += tag.Val;
  }

 public:
  int Val = 0;
};

class Info {
 public:
  void Apply(const Tag& tag) {
    Min += tag.Val;
  }

 public:
  int Min = std::numeric_limits<int>::max() / 2;
};
Info operator+(const Info& lhs, const Info& rhs) {
  return {std::min(lhs.Min, rhs.Min)};
}

} // namespace lazy_segment_tree


namespace segment_tree {

template <typename Info>
class SegmentTree {
 public:
  static constexpr auto kNpos = static_cast<size_t>(-1);

 public:
  SegmentTree() = default;

  explicit SegmentTree(std::size_t n) {
    Init(std::vector(n, Info{}));
  }
  SegmentTree(std::size_t n, Info info) {
    Init(std::vector(n, info));
  }
  template <typename T>
  explicit SegmentTree(const std::vector<T>& init) {
    Init(init);
  }

  template <typename T>
  void Init(const std::vector<T>& init) {
    assert(!init.empty());
    N_ = 1u << (std::bit_width(2 * init.size() - 1) - 1);
    Infos_.assign(2 * N_ - 1, Info{});

    auto build = [&](auto&& self, std::size_t x, std::size_t lx, std::size_t rx) -> void {
      if (rx - lx == 1u) {
        if (lx < init.size()) {
          Infos_[x] = {init[lx]};
        }
        return;
      }
      const auto mid = lx + (rx - lx) / 2;
      self(self, 2 * x + 1, lx, mid);
      self(self, 2 * x + 2, mid, rx);
      Infos_[x] = Infos_[2 * x + 1] + Infos_[2 * x + 2];
    };
    build(build, 0u, 0u, N_);
  }

  void Modify(std::size_t pos, Info info) {
    ModifyImpl(pos, info, 0u, 0u, N_);
  }

  Info Query(std::size_t ql, std::size_t qr) {
    return QueryImpl(ql, qr, 0u, 0u, N_);
  }
  Info Query(std::size_t pos) {
    return QueryImpl(pos, pos + 1, 0u, 0u, N_);
  }

  template <typename Functor>
  std::size_t FindFirst(std::size_t ql, std::size_t qr, Functor&& functor) {
    return FindFirstImpl(ql, qr, std::move(functor), 0u, 0u, N_);
  }
  template <typename Functor>
  std::size_t FindLast(std::size_t ql, std::size_t qr, Functor&& functor) {
    return FindLastImpl(ql, qr, std::move(functor), 0u, 0u, N_);
  }

 private:
  void ModifyImpl(std::size_t pos, Info info, std::size_t x, std::size_t lx, std::size_t rx) {
    if (rx - lx == 1u) {
      Infos_[x] = info;
      return;
    }
    const auto mid = lx + (rx - lx) / 2;
    if (pos < mid) {
      ModifyImpl(pos, info, 2 * x + 1, lx, mid);
    } else {
      ModifyImpl(pos, info, 2 * x + 2, mid, rx);
    }
    Infos_[x] = Infos_[2 * x + 1] + Infos_[2 * x + 2];
  }

  Info QueryImpl(std::size_t ql, std::size_t qr, std::size_t x, std::size_t lx, std::size_t rx) {
    if (ql >= rx || qr <= lx) {
      return {};
    }
    if (ql <= lx && rx <= qr) {
      return Infos_[x];
    }
    const auto mid = lx + (rx - lx) / 2;
    return QueryImpl(ql, qr, 2 * x + 1, lx, mid) + QueryImpl(ql, qr, 2 * x + 2, mid, rx);
  }

  template <typename Functor>
  std::size_t FindFirstImpl(
    std::size_t ql, std::size_t qr, Functor&& functor,
    std::size_t x, std::size_t lx, std::size_t rx
  ) {
    if (lx >= qr || rx <= ql || !functor(Infos_[x])) {
      return kNpos;
    }
    if (rx - lx == 1u) {
      return lx;
    }
    const auto mid = lx + (rx - lx) / 2;

    auto res = FindFirstImpl(ql, qr, std::move(functor), 2 * x + 1, lx, mid);
    if (res == kNpos) {
      res = FindFirstImpl(ql, qr, std::move(functor), 2 * x + 2, mid, rx);
    }
    return res;
  }
  template <typename Functor>
  std::size_t FindLastImpl(
    std::size_t ql, std::size_t qr, Functor&& functor,
    std::size_t x, std::size_t lx, std::size_t rx
  ) {
    if (lx >= qr || rx <= ql || !functor(Infos_[x])) {
      return kNpos;
    }
    if (rx - lx == 1u) {
      return lx;
    }
    const auto mid = lx + (rx - lx) / 2;

    auto res = FindLastImpl(ql, qr, std::move(functor), 2 * x + 2, mid, rx);
    if (res == kNpos) {
      res = FindLastImpl(ql, qr, std::move(functor), 2 * x + 1, lx, mid);
    }
    return res;
  }

 private:
  std::size_t N_{0};
  std::vector<Info> Infos_;
};

class Info {
 public:
  int Val = 0;
};
Info operator+(const Info& lhs, const Info& rhs) {
  return {std::max(lhs.Val, rhs.Val)};
}

} // namespace segment_tree


namespace bottom_up_segment_tree {

template <typename Info>
class BottomUpSegmentTree {
 public:
  BottomUpSegmentTree() = default;

  explicit BottomUpSegmentTree(std::size_t n) {
    Init(std::vector(n, Info{}));
  }
  BottomUpSegmentTree(std::size_t n, Info&& info) {
    Init(std::vector(n, std::forward<Info>(info)));
  }
  template <typename T>
  explicit BottomUpSegmentTree(const std::vector<T>& init) {
    Init(init);
  }

  template <typename T>
  void Init(const std::vector<T>& init) {
    assert(!init.empty());
    N_ = 1u << (std::bit_width(2 * init.size() - 1) - 1);
    Infos_.assign(2 * N_, Info{});
    for (std::size_t i{0}; i < init.size(); ++i) {
      Infos_[i + N_] = Info{init[i]};
    }
    for (std::size_t i = N_ - 1; i >= 1u; --i) {
      Infos_[i] = Infos_[i << 1] + Infos_[i << 1 | 1];
    }
  }

  void Modify(std::size_t pos, Info&& val) {
    Infos_[pos += N_] = val;
    for (pos >>= 1; pos >= 1; pos >>= 1) {
      Infos_[pos] = Infos_[pos << 1] + Infos_[pos << 1 | 1];
    }
  }

  Info Query(std::size_t l, std::size_t r) {
    auto retL = Info{}, retR = Info{};
    for (l += N_, r += N_; l < r; l >>= 1, r >>= 1) {
      if (l % 2 == 1u) {
        retL = retL + Infos_[l++];
      }
      if (r % 2 == 1u) {
        retR = Infos_[--r] + retR;
      }
    }
    return retL + retR;
  }

  Info Query(std::size_t pos) {
    return Query(pos, pos + 1);
  }

 private:
  std::size_t N_{0};
  std::vector<Info> Infos_;
};

class Info {
 public:
  int Val = 0;
};
Info operator+(const Info& lhs, const Info& rhs) {
  return {std::max(lhs.Val, rhs.Val)};
}

} // namespace bottom_up_segment_tree
