#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include <cstdio>
#include <set>

template <class X, class Y>
class Treap : public std::enable_shared_from_this<Treap<X, Y> > {
public:  
    typedef std::shared_ptr<Treap> Ptr;
private:
  Y y;
  Ptr left;
  Ptr right;
  X sum;

public:
  X x;
  Ptr getptr() { return this->shared_from_this(); }

  Treap(X _x, Y _y) : x(_x), y(_y), left(Ptr()), right(Ptr()), sum(_x) {}

  Treap(const Treap<X, Y> &) = default;

  static void merge(Ptr &T, Ptr L, Ptr R) {
    if (!L || !R) {
      if (L)
        T = L;
      else
        T = R;
    } else if (L->y < R->y) {
      merge(L->right, L->right, R);
      T = L;
    } else {
      merge(R->left, L, R->left);
      T = R;
    }
    if (T) {
      T->updateSum();
    }
  }

  static void split(Ptr T, X x0, Ptr &T1, Ptr &T2) {
    if (!T)
      T1 = T2 = Ptr();
    else {
      if (x0 >= T->x) {
        split(T->right, x0, T->right, T2);
        T1 = T;
      } else {
        split(T->left, x0, T1, T->left);
        T2 = T;
      }
      T->updateSum();
    }
  }

  Ptr insert(X x0, Y y0) {
    Ptr L, R;
    split(getptr(), x0, L, R);
    auto xy = std::make_shared<Treap<X, Y> >(x0, y0);
    merge(L, L, xy);
    merge(L, L, R); 
    return L;
  }

  bool exists(X x0) {
    auto cur = getptr();
    while (cur) {
      if (x0 == cur->x)
        return true;
      cur = (x0 > cur->x) ? cur->right : cur->left;
    }
    return false;
  }

  std::pair<X, Ptr> getSum(X l, X r) {
        Ptr L, R, L1, R1, T;
        split(getptr(), l-1, L, R);
        split(R, r, L1, R1);
        X ans = L1 ? L1->sum : 0;
        merge(R, L1, R1);
        merge(T, L, R);
        return std::make_pair(ans, T);
   }

private:
  void updateSum() { sum = getLeftSum() + getRightSum() + x; }

  X getLeftSum() { return getSum(left); }

  X getRightSum() { return getSum(right); }

  static X getSum(Ptr node) { return node ? node->sum : 0; }
};

int main() {
    srand((size_t)time(0));
    std::ios::sync_with_stdio(false);
    std::shared_ptr<Treap<long long, size_t> > t;
    size_t n = 0;
    std::cin >> n;
    char task = 'n';
    long long ans = 0;
    for (size_t i = 0; i < n; i++) {
        std::cin >> task;
        if (task == '+') {
            long long data = 0;
            std::cin >> data;
            data += ans;
            size_t y = (rand()%(n * 1000))+1;
            if (!t) {
                t = std::make_shared<Treap<long long, size_t> >(data % 1000000000, y);
            } else {
                if (!t->exists(data % 1000000000)) {
                    t = t->insert(data % 1000000000, y);
                }
            }
            ans = 0;
        } else {
            long long l = 0, r = 0;
            std::cin >> l >> r;
            if (t && (l <= r)) {
                std::pair<long long, Treap<long long, size_t>::Ptr> res = t->getSum(l, r);
                ans = res.first;
                t = res.second;
                std::cout << ans << std::endl;
            } else 
                std::cout << 0 << std::endl;
        }
    }
    return 0;
}
