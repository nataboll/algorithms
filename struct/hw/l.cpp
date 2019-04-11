#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

template <class X, class Y>
class sortedTreap : public std::enable_shared_from_this<sortedTreap<X, Y> > {
  typedef std::shared_ptr<sortedTreap> Ptr;
  Y y;
  Ptr left;
  Ptr right;
  size_t size;

public:
  X x;

  Ptr getptr() { return this->shared_from_this(); }

  sortedTreap(X _x, Y _y) : x(_x), y(_y), left(Ptr()), right(Ptr()), size(1) {}

  sortedTreap(const sortedTreap<X, Y> &) = default;

  static void merge(Ptr &T, Ptr L, Ptr R) { // writes in T
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

    if (T)
      T->updateSize();
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
      T->updateSize();
    }
  }

  Ptr insert(X x0, Y y0) {
    Ptr L, R, T1, T;
    split(getptr(), x0, L, R);
    auto xy = std::make_shared<sortedTreap<X, Y> >(x0, y0);
    merge(T1, L, xy);
    merge(T, T1, R); // T is a new treap
    return T;
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

private:
  void updateSize() { size = getLeftSize() + getRightSize() + 1; }

  size_t getLeftSize() { return getSize(left); }

  size_t getRightSize() { return getSize(right); }

  static size_t getSize(Ptr node) { return node ? node->size : 0; }
};

///////////////////////////////////////////////////////////////////////////////////////

template <class D, class Y>
class Treap : public std::enable_shared_from_this<Treap<D, Y> > {
  typedef std::shared_ptr<Treap> Ptr;
  Y y;
  Ptr left;
  Ptr right;
  size_t size;
  D sum;

public:
  D data;
  Ptr getptr() { return this->shared_from_this(); }

  Treap(D _d, Y _y) : data(_d), y(_y), left(Ptr()), right(Ptr()), size(1), sum(_d) {}

  Treap(const Treap<D, Y> &) = default;

  static void merge(Ptr &T, Ptr L, Ptr R) { // writes in T
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
      T->updateSum();
    }
  }

  static void split(Ptr T, size_t key, Ptr &T1, Ptr &T2, int add = 0) { 
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
      T->updateSum();
    }
  }

  Ptr insert(D data, Y y0) {
    Ptr T;
    auto xy = std::make_shared<Treap<D, Y> >(data, y0);
    merge(T, getptr(), xy);
    return T;
  }

   D get_sum(int l, int r) {
        Ptr L, R, L1, R1, T;
        split(getptr(), l, L, R);
        split(R, r-l+1, L1, R1);
        D ans = L1->sum;
        merge(R, L1, R1);
        merge(T, L, R);
        this->data = T->data;
        this->y = T->y;
        this->left = T->left;
        this->right = T->right;
        this->sum = T->sum;
        this->size = T->size;
        return ans;
   }

private:
  void updateSize() { size = getLeftSize() + getRightSize() + 1; }

  size_t getLeftSize() { return getSize(left); }

  size_t getRightSize() { return getSize(right); }

  static size_t getSize(Ptr node) { return node ? node->size : 0; }

  void updateSum() { sum = getLeftSum() + getRightSum() + data; }

  D getLeftSum() { return getSum(left); }

  D getRightSum() { return getSum(right); }

  static D getSum(Ptr node) { return node ? node->sum : 0; }
};

int main() {
  srand((unsigned)time(0));
  std::shared_ptr<Treap<int, int> > t;
  std::shared_ptr<sortedTreap<int, int> > storage;
  int n = 0;
  std::cin >> n;
  char s = 'n';
  char prev = 'n';
  int prev_res = 0;
  for (int i = 0; i < n; i++) {
      std::cin >> s;
      if (s == '+') {
        int data = 0;
        std::cin >> data;
        if (!t) {
            size_t y = (rand()%100000)+1;
            storage = std::make_shared<sortedTreap<int, int> >(data, y);
            t = std::make_shared<Treap<int, int> >(data, y);
        } else {
            size_t y = (rand()%100000)+1;
            if (prev == '+') {
                if (!storage->exists(data)) {
                    t = t->insert(data, y);
                    storage = storage->insert(data, y);
                }
            } else if (prev == '?') {
                if (!storage->exists(data + prev_res)) {
                    t = t->insert(data + prev_res, y);        
                    storage = storage->insert(data + prev_res, y);
                }
            }
        }
        prev = '+';
      } else {
            int l = 0, r = 0;
            std::cin >> l >> r;
            if (t && l <= r) {
                prev_res = t->get_sum(l-1, r-1);
                std::cout << prev_res << std::endl;
            }
            else {
                prev_res = 0;
                std::cout << 0 << std::endl;
            }
            prev = '?';
      }
  }
  return 0;
}
