//
// Created by aminjon on 8/4/23.
//
#include <bits/stdc++.h>

template <size_t kSigma = 26, char kMinAlpha = 'a'>
class AhoCorasick {
 public:
  static constexpr int kRoot{0};

 public:
  AhoCorasick()
    : Nodes_(1u)
  { }

  void AddWord(std::string_view s, const int idx = kEmpty) {
    assert(std::ranges::all_of(s, [](auto c) { return std::clamp<char>(c, kMinAlpha, kMinAlpha + kSigma - 1) == c; }));

    auto v = kRoot;
    for (auto c : s) {
      if (Nodes_[v].Next[c - kMinAlpha] == kEmpty) {
        Nodes_[v].Next[c - kMinAlpha] = static_cast<int>(Nodes_.size());
        Nodes_.emplace_back();
      }
      v = Nodes_[v].Next[c - kMinAlpha];
    }
    Nodes_[v].Indices.emplace_back(idx);
  }

  int Go(const int curState, const char c) noexcept {
    assert(std::clamp<int>(curState, 0, Nodes_.size() - 1) == curState);
    assert(std::clamp<char>(c, kMinAlpha, kMinAlpha + kSigma - 1) == c);
    return Nodes_[curState].Go[c - kMinAlpha];
  }
  int SufLink(const int curState) noexcept {
    assert(std::clamp<int>(curState, 0, Nodes_.size() - 1) == curState);
    return Nodes_[curState].SufLink;
  }
  int TermSufLink(const int curState) noexcept {
    assert(std::clamp<int>(curState, 0, Nodes_.size() - 1) == curState);
    return Nodes_[curState].TermSufLink;
  }
  std::vector<int>& GetIndices(const int curState) noexcept {
    assert(std::clamp<int>(curState, 0, Nodes_.size() - 1) == curState);
    return Nodes_[curState].Indices;
  }

  void Build() {
    Nodes_[kRoot].SufLink = kRoot;
    Nodes_[kRoot].TermSufLink = kRoot;
    for (int ch = 0; ch < kSigma; ++ch) {
      if (Nodes_[kRoot].Next[ch] != kEmpty) {
        Nodes_[kRoot].Go[ch] = Nodes_[kRoot].Next[ch];
      } else {
        Nodes_[kRoot].Go[ch] = kRoot;
      }
    }

    std::queue<int> q;
    for (q.push(kRoot); !q.empty(); q.pop()) {
      const auto v = q.front();
      for (int ch = 0; ch < kSigma; ++ch) {
        const auto u = Nodes_[v].Next[ch];
        if (u == kEmpty) {
          continue;
        }
        Nodes_[u].SufLink = v == kRoot ? kRoot : Nodes_[Nodes_[v].SufLink].Go[ch];
        Nodes_[u].TermSufLink = !Nodes_[Nodes_[u].SufLink].Indices.empty()
                                  ? Nodes_[u].SufLink
                                  : Nodes_[Nodes_[u].SufLink].TermSufLink;
        for (int d = 0; d < kSigma; ++d) {
          if (Nodes_[u].Next[d] != kEmpty) {
            Nodes_[u].Go[d] = Nodes_[u].Next[d];
          } else {
            Nodes_[u].Go[d] = Nodes_[Nodes_[u].SufLink].Go[d];
          }
        }
        q.emplace(u);
      }
    }
  }

 private:
  static constexpr int kEmpty{-1};

  class Node {
   public:
    Node() {
      Next.fill(kEmpty);
      Go.fill(kEmpty);
    }

   public:
    int SufLink{kRoot}, TermSufLink{kRoot};
    std::vector<int> Indices;
    std::array<int, kSigma> Next{}, Go{};
  };

  std::vector<Node> Nodes_;
};