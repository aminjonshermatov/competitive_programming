#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

struct Info {
  std::array<int64_t, 2> Sum{0, 0};
  int64_t Count = 0;
};
Info operator+(const Info& lhs, const Info& rhs) {
  Info ret{};
  for (std::size_t i = 0; i < 2; ++i) {
    ret.Sum[i] = lhs.Sum[i] + rhs.Sum[(lhs.Count & 1) ^ i];
  }
  ret.Count = lhs.Count + rhs.Count;
  return ret;
}

class Block {
 public:

  auto Back() const {
    return !Values_.empty() ? Values_.back() : std::numeric_limits<int64_t>::max() / 2;
  }

  auto Recalc() {
    BlockInfo = {};
    for (std::size_t i = 0; i < Values_.size(); ++i) {
      BlockInfo.Sum[i % 2] += Values_[i];
    }
    BlockInfo.Count = Values_.size();
  }

  auto Insert(const int64_t value) {
    if (Values_.empty()) {
      Values_.emplace_back(value);
    } else {
      Values_.reserve(Values_.size() + 1);
      Values_.insert(std::ranges::upper_bound(Values_, value), value);
    }
    Recalc();
  }

  auto InsertMany(const std::vector<int64_t>& buf) {
    std::vector<int64_t> tmp;
    tmp.reserve(Values_.size() + buf.size());
    std::ranges::merge(Values_, buf, std::back_inserter(tmp));
    std::swap(tmp, Values_);
    Recalc();
  }

  auto Truncate(const std::size_t newSize) {
    assert(BlockInfo.Count >= newSize);
    std::vector<int64_t> buf;
    while (Values_.size() > newSize) {
      buf.emplace_back(Values_.back());
      Values_.pop_back();
    }
    Recalc();
    return buf;
  }

 public:
  Info BlockInfo{};

 private:
  std::vector<int64_t> Values_;
};

void Solve() {
  int q;
  Scan(q);

  constexpr int64_t kMod = 1E9;
  constexpr int64_t kBlockWidth = 600;

  std::vector<Block> blocks(1);

  auto rebalance = [&](const std::size_t id) {
    if (id + 1 == blocks.size()) {
      blocks.emplace_back();
    }
    auto values = blocks[id].Truncate(kBlockWidth);
    std::ranges::reverse(values);
    blocks[id + 1].InsertMany(values);
  };

  int64_t z = 0;
  while (q-- > 0) {
    int64_t y;
    Scan(y);

    const auto x = ((y + z) % kMod + kMod) % kMod + 1;
    dbg(x);

    auto blockId = std::optional<std::size_t>{};
    for (std::size_t i = 0; i < blocks.size() && !blockId.has_value(); ++i) {
      if (blocks[i].Back() >= x) {
        blockId.emplace(i);
      }
    }

    const auto id = blockId.value_or(blocks.size() - 1);
    blocks[id].Insert(x);
    if (blocks[id].BlockInfo.Count > kBlockWidth * 2) {
      rebalance(id);
    }

    Info info{};
    for (const auto& block : blocks) {
      info = info + block.BlockInfo;
    }
    Println(z = info.Sum[0]);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
