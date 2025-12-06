//
// Created by Aminjon Shermatov on 06.12.2025.
//

#include <bits/stdc++.h>

template <typename T, template <typename> typename Aggregation>
class AggregateQueue final {
 public:
  explicit AggregateQueue(const std::size_t n)
    : Bwd_(n), Fwd_(n)
  { }

  auto Push(const T& t) noexcept {
    Fwd_[FwdPtr_] = std::pair(
      (FwdPtr_ > 0 ? Fwd_[FwdPtr_ - 1].first : Aggregation<T>::E()) + Aggregation(t),
      t
    );
    ++FwdPtr_;
  }
  auto Pop() noexcept {
    assert(BwdPtr_ + FwdPtr_ > 0);
    if (BwdPtr_ == 0) {
      for (; FwdPtr_ > 0; --FwdPtr_, ++BwdPtr_) {
        Bwd_[BwdPtr_] = std::pair(
          (BwdPtr_ > 0 ? Bwd_[BwdPtr_ - 1].first : Aggregation<T>::E()) + Aggregation(Fwd_[FwdPtr_ - 1].second),
          Fwd_[FwdPtr_ - 1].second
        );
      }
    }
    --BwdPtr_;
  }

  auto Query() const {
    auto ret = Aggregation<T>::E();
    if (BwdPtr_ > 0) {
      ret = Bwd_[BwdPtr_ - 1].first + ret;
    }
    if (FwdPtr_ > 0) {
      ret = ret + Fwd_[FwdPtr_ - 1].first;
    }
    return ret;
  }

 private:
  int BwdPtr_ = 0, FwdPtr_ = 0;
  std::vector<std::pair<Aggregation<T>, T>> Bwd_, Fwd_;
};

template <typename T>
struct Aggregation final {
  T Min = std::numeric_limits<T>::max();
  T Max = std::numeric_limits<T>::min();

  Aggregation() = default;
  explicit Aggregation(const T& x) : Min(x), Max(x) { }

  static inline constexpr Aggregation<T> E() {
    return {};
  }
};
template <typename T>
Aggregation<T> operator+(const Aggregation<T>& a, const Aggregation<T>& b) {
  auto ret = Aggregation<T>::E();
  ret.Min = std::min(a.Min, b.Min);
  ret.Max = std::max(a.Max, b.Max);
  return ret;
}
