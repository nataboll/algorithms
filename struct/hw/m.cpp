#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>

template <class D, class Y>
class Treap : public std::enable_shared_from_this<Treap<D, Y> > {
  typedef std::shared_ptr<Treap> Ptr;
  Y y;
  Ptr left;
  Ptr right;
  size_t size;

public:
  D data;
  Ptr getptr() { return this->shared_from_this(); }

  Treap(D _d, Y _y) : data(_d), y(_y), left(Ptr()), right(Ptr()), size(1) {}

  Treap(const Treap<D, Y> &) = default;

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

  static void split(Ptr T, size_t key, Ptr &T1, Ptr &T2, size_t = 0) { 
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

  Ptr insert(D data, Y y0) {
    Ptr T;
    auto xy = std::make_shared<Treap<D, Y> >(data, y0);
    merge(T, getptr(), xy);
    return T;
  }

    Ptr toBegin(int l, int r) {
        Ptr L, R, L1, R1;
        split(getptr(), l, L, R);
        split(R, r-l+1, L1, R1);
        merge(L, L, R1);
        merge(L1, L1, L);
        return L1;
    }

    void getTreap(std::vector<D> &res, int add = 0) const {
        res[getLeftSize() + add] = data;
        if (left)
            left->getTreap(res, add);
        if (right)
            right->getTreap(res, add + 1 + getLeftSize());
    }

private:
  void updateSize() { size = getLeftSize() + getRightSize() + 1; }

  size_t getLeftSize() const { return getSize(left); }

  size_t getRightSize() const { return getSize(right); }

  static size_t getSize(Ptr node) { return node ? node->size : 0; }
};

int main() {
    srand((unsigned)time(0));
    std::shared_ptr<Treap<int, int> > t(new Treap<int, int>(1, (rand()%100000)+1));
    int n = 0, m = 0;
    std::cin >> n >> m;
    for (int i = 1; i < n; i++) {
        t->insert(i+1, (rand()%100000)+1);
    }
    std::vector<int> res(n);

    t->getTreap(res);
    for (int i = 0; i < n; i++) {
        std::cout << res[i] << " ";
    }
    std::cout << std::endl;

    for (int i = 1; i < m; i++) {
        int l = 0, r = 0;
        std::cin >> l >> r;
        t = t->toBegin(l-1, r-1);
    }

    t->getTreap(res);
    for (int i = 0; i < n; i++) {
        std::cout << res[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}

