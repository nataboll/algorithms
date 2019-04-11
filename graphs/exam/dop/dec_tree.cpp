#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

template <class X, class Y>
class Treap : public std::enable_shared_from_this<Treap<X, Y> > {
  typedef std::shared_ptr<Treap> Ptr;
  Y y;
  Ptr left;
  Ptr right;
  size_t size;

public:
  X x;

  Ptr getptr() { return this->shared_from_this(); }

  Treap(X _x, Y _y) : x(_x), y(_y), left(Ptr()), right(Ptr()), size(1) {}

  Treap(const Treap<X, Y> &) = default;

  void printTreap() const {
    printNode();
    if (left)
      left->printTreap();
    if (right)
      right->printTreap();
  }

  void printNode() const {
    static const std::string emph("----------------------------");
    std::cout << emph << std::endl;
    std::cout << this << ": " << x << " " << y << " " << size << std::endl;
    std::cout << left.get() << " " << right.get() << std::endl;
    std::cout << emph << std::endl;
  }

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
    auto xy = std::make_shared<Treap<X, Y> >(x0, y0);
    merge(T1, L, xy);
    merge(T, T1, R); // T is a new treap
    return T;
  }

  Ptr remove(X x0) {
    Ptr L, R, L1, R1, T;
    split(getptr(), x0 - 1, L, R);
    split(R, x0, L1, R1);
    merge(T, L, R1);
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

  std::pair<X, bool> next(X x0) {
    if (!left && !right && x <= x0)
      return std::make_pair(X(), false);

    if (x > x0 && (!left || left->x < x0))
      return std::make_pair(x, true);

    if (x <= x0 && right)
      return right->next(x0);
    else if (left)
      return left->next(x0);

    return std::make_pair(X(), false);
  }

  std::pair<X, bool> prev(X x0) {
    if (!left && !right && x >= x0)
      return std::make_pair(X(), false);

    if (x < x0 && (!right || right->x > x0))
      return std::make_pair(x, true);

    if (x < x0 && right)
      return right->prev(x0);
    else if (left)
      return left->prev(x0);

    return std::make_pair(X(), false);
  }

  std::pair<X, bool> kth(size_t k) {
    if (k >= size)
      return std::make_pair(X(), false);

    size_t root_number = getLeftSize();
    if (root_number == k)
      return std::make_pair(x, true);
    if (k < root_number)
      return left->kth(k);
    else
      return right->kth(k - root_number - 1);
  }

private:
  void updateSize() { size = getLeftSize() + getRightSize() + 1; }

  size_t getLeftSize() { return getSize(left); }

  size_t getRightSize() { return getSize(right); }

  static size_t getSize(Ptr node) { return node ? node->size : 0; }
};

int main() {
  srand((unsigned)time(0));
  std::string s;
  std::shared_ptr<Treap<int, int> > t;
  while (std::cin >> s) {
    if (s == "insert") {
      int data = 0;
      int y = rand() % 100000 + 1;
      std::cin >> data;//  >> y;
      if (!t)
        t = std::make_shared<Treap<int, int> >(data, y);
      else
        t = t->insert(data, y);

      //t->printTreap();

    } else if (s == "delete") {
      int data = 0;
      std::cin >> data;
      if (t)
        t = t->remove(data);
    } else if (s == "exists") {
      int data = 0;
      std::cin >> data;
      if (!t) {
          std::cout << "false" << std::endl;
          continue;
      }
      std::string ans = (t->exists(data)) ? "true" : "false";
      std::cout << ans << std::endl;
      //t->printTreap();
    } else if (s == "next") {
      int data = 0;
      std::cin >> data;
      if (!t) {
        std::cout << "none" << std::endl;
        continue;
      }
      auto next = t->next(data);
      std::string ans = next.second ? std::to_string(next.first) : "none";
      std::cout << ans << std::endl;
    } else if (s == "prev") {
      int data = 0;
      std::cin >> data;
      if (!t) {
        std::cout << "none" << std::endl;
        continue;
      }
      auto next = t->prev(data);
      std::string ans = next.second ? std::to_string(next.first) : "none";
      std::cout << ans << std::endl;
    } else if (s == "kth") {
      int data = 0;
      std::cin >> data;
      if (!t) {
        std::cout << "none" << std::endl;
        continue;
      }
      auto next = t->kth(--data);
      std::string ans = next.second ? std::to_string(next.first) : "none";
      std::cout << ans << std::endl;
    }
  }
  return 0;
}
