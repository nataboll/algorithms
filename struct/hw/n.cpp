#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include <cstdio>

template <class Y>
class Treap : public std::enable_shared_from_this<Treap<Y> > {
public:  
    typedef std::shared_ptr<Treap> Ptr;
private:
  Y y;
  Ptr left;
  Ptr right;
  size_t size;

public:
  Ptr getptr() { return this->shared_from_this(); }

  Treap(Y _y) : y(_y), left(Ptr()), right(Ptr()), size(1) {}

  Treap(const Treap<Y> &) = default;

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
      T->updateSize();
    }
  }

  static void split(Ptr T, size_t key, Ptr &T1, Ptr &T2, size_t add = 0) { 
    if (!T)
      T1 = T2 = Ptr();
    else {
      size_t cur_key = add + T->getLeftSize();
      if (key > cur_key) {
        split(T->right, key, T->right, T2, add + 1 + T->getLeftSize());
        T1 = T;
      } else {
        split(T->left, key, T1, T->left, add);
        T2 = T;
      }
      T->updateSize();
    }
  }

  Ptr insert(Y y0, size_t idx) {
    Ptr L, R, T, T1;
    auto xy = std::make_shared<Treap<Y> >(y0);
    split(getptr(), idx+1, L, R);
    merge(T1, L, xy);
    merge(T, T1, R);
    return T;
  }

  std::pair<Y, Ptr> getMin(size_t l, size_t r) {
    Ptr L, R, L1, R1, T;
    split(getptr(), l, L, R);
    split(R, r-l+1, L1, R1);
    Y ans = L1->y;
    merge(R, L1, R1);
    merge(T, L, R);
    return std::make_pair(ans, T); 
  }

private:
  void updateSize() { size = getLeftSize() + getRightSize() + 1; }

  size_t getLeftSize() const { return getSize(left); }

  size_t getRightSize() const { return getSize(right); }

  static size_t getSize(Ptr node) { return node ? node->size : 0; }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::shared_ptr<Treap<int> > t;
    int n = 0;
    std::cin >> n;
    char s = 'n';
    for (int i = 0; i < n; i++) {
        std::cin >> s;
        if (s == '+') {
            int data = 0, index = 0;
            std::cin >> index >> data;
            if (!t) 
                t = std::make_shared<Treap<int> >(data);
            else
                t = t->insert(data, index-1);
        } else if (s == '?') {
            int l = 0, r = 0;
            std::cin >> l >> r;
            std::pair<int, Treap<int>::Ptr> res = t->getMin(l-1, r-1);
            t = res.second;
            std::cout << res.first << std::endl;
        }
    }
    return 0;
}

