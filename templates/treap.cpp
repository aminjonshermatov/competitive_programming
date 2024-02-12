//
// Created by aminjon on 10/6/22.
//
#include <bits/stdc++.h>

template <typename Node> struct TreapBase {
  using Ptr = Node*; // std::shared_ptr<Node>
  template <typename ...Args>
  inline Ptr make_node(Args&&... args) {
    // return std::make_shared<Node>(std::forward<Args...>(args...));
    return new Node(std::forward<Args...>(args...));
  }

  inline int size(Ptr ptr) {
    return ptr == nullptr ? 0 : ptr->size;
  }

  inline Ptr merge(Ptr lhs, Ptr rhs) {
    if (lhs == nullptr || rhs == nullptr) {
      return lhs == nullptr ? rhs : lhs;
    }
    if (lhs->priority > rhs->priority) {
      push(lhs);
      lhs->r = merge(lhs->r, rhs);
      return update(lhs);
    }
    push(rhs);
    rhs->l = merge(lhs, rhs->l);
    return update(rhs);
  }
  inline std::pair<Ptr, Ptr> split(Ptr ptr, int k) {
    assert(k <= size(ptr) && "Out of range");
    if (ptr == nullptr) {
      return {nullptr, nullptr};
    }
    push(ptr);
    if (size(ptr->l) >= k) {
      auto [ll, lr] = split(ptr->l, k);
      ptr->l = lr;
      return {ll, update(ptr)};
    }
    auto [rl, rr] = split(ptr->r, k - size(ptr->l) - 1);
    ptr->r = rl;
    return {update(ptr), rr};
  }
  /*
   * @brief Constructs node after `k` elements, i.e 0 means to the beginning
   */
  template <typename ...Args>
  inline void emplace(Ptr& ptr, int k, Args&&... args) {
    auto [l, r] = split(ptr, k);
    ptr = merge(l, merge(make_node(std::forward<Args...>(args...)), r));
  }
  /*
   * @brief Insert after `k` elements, i.e 0 means to the beginning
   */
  inline void insert(Ptr& ptr, int k, Ptr sub) {
    auto [l, r] = split(ptr, k);
    ptr = merge(l, merge(sub, r));
  }
  /*
   * @brief Erase sub range and return, `pos`, `k` - STL like [pos, pos + k)
   * @param pos zero indexed
   */
  inline Ptr erase(Ptr& ptr, int pos, int k) {
    auto [l, tmp] = split(ptr, pos);
    auto [mid, r] = split(tmp, k);
    ptr = merge(l, r);
    return mid;
  }

  inline virtual void push(Ptr) {}
  inline virtual Ptr update(Ptr) = 0;
};

static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template <typename TreapNode> struct TreapNodeBase {
  typename TreapBase<TreapNode>::Ptr l, r;
  int size;
  decltype(rng()) priority;
  bool reverse;
protected:
  TreapNodeBase()
    : l(nullptr)
    , r(nullptr)
    , size(1)
    , priority(rng())
    , reverse(false)
  { }
};
template <typename Info, typename Aggregator> struct TreapNode : TreapNodeBase<TreapNode<Info, Aggregator>> {
  using Base = TreapNodeBase<TreapNode<Info, Aggregator>>;
  Info info;
  Aggregator aggr;

  explicit TreapNode(const Info& info_ = Info(), const Aggregator& aggr_ = Aggregator())
    : Base()
    , info(info_)
    , aggr(aggr_)
  { }
};

template <typename Info, typename Aggregator> class Treap : protected TreapBase<TreapNode<Info, Aggregator>> {
  using Base = TreapBase<TreapNode<Info, Aggregator>>;
  using Base::merge;
  using Base::split;
public:
  using typename Base::Ptr;
  using Base::emplace;
  using Base::insert;
  using Base::erase;
  using Base::size;
  /*
   * @brief Returns info in [l, r)
   * @param l zero indexed
   * @param r zero indexed
   */
  inline decltype(auto) query(Ptr& ptr, int l, int r) {
    auto [L, tmp] = split(ptr, l);
    auto [mid, R] = split(tmp, r - l);
    std::pair<Info, Aggregator> ret{};
    if (mid != nullptr) {
      ret = {mid->info, mid->aggr};
    }
    ptr = merge(merge(L, mid), R);
    return ret;
  }
  /*
   * @brief Query at point
   * @param pos zero indexed
   */
  inline decltype(auto) query(Ptr& ptr, int pos) {
    auto [L, tmp] = split(ptr, pos);
    auto [el, R] = split(tmp, 1);
    std::pair<Info, Aggregator> ret{};
    if (el != nullptr) {
      ret = {el->info, el->aggr};
    }
    ptr = merge(merge(L, el), R);
    return ret;
  }
  /*
   * @param l zero indexed
   * @param r zero indexed
   */
  inline void reverse(Ptr& ptr, int l, int r) {
    auto [L, tmp] = split(ptr, l);
    auto [mid, R] = split(tmp, r - l);
    toggle(mid);
    ptr = merge(L, merge(mid, R));
  }

private:
  inline void toggle(Ptr ptr) {
    if (ptr == nullptr) {
      return;
    }
    std::swap(ptr->l, ptr->r);
    ptr->reverse ^= true;
  }
  inline Ptr update(Ptr ptr) override {
    ptr->size = 1;
    ptr->aggr = ptr->info;
    if (ptr->l != nullptr) {
      ptr->size += ptr->l->size;
      ptr->aggr = Aggregator::unite(ptr->l->aggr, ptr->aggr);
    }
    if (ptr->r != nullptr) {
      ptr->size += ptr->r->size;
      ptr->aggr = Aggregator::unite(ptr->aggr, ptr->r->aggr);
    }
    return ptr;
  };
  inline void push(Ptr ptr) override {
    assert(ptr != nullptr);
    if (ptr->reverse) {
      toggle(ptr->l);
      toggle(ptr->r);
      ptr->reverse = false;
    }
  }
};
struct Info {
  int val = 0;
  Info() = default;
  explicit Info(int val_)
    : val(val_)
  { }
};
struct SumAggregator {
  int sum = 0;
  SumAggregator() = default;
  explicit SumAggregator(int sum_)
    : sum(sum_)
  { }
  inline SumAggregator& operator=(const Info& info) {
    sum = info.val;
    return *this;
  }
  static inline SumAggregator unite(const SumAggregator& a, const SumAggregator& b) {
    return SumAggregator{a.sum + b.sum};
  }
};