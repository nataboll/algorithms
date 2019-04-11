#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <set>
#include <utility>

template <class D, class Y>
class Treap : public std::enable_shared_from_this<Treap<D, Y> > {
public:
  typedef std::shared_ptr<Treap> Ptr;
private:
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

  std::pair<D, Ptr> getSum(int l, int r) {
        Ptr L, R, L1, R1, T;
        split(getptr(), l, L, R);
        split(R, r-l+1, L1, R1);
        D ans = L1 ? L1->sum : 0;
        merge(R, L1, R1);
        merge(T, L, R);
        return std::make_pair(ans, T);
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
  std::set<int> storage;
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
            t = std::make_shared<Treap<int, int> >(data, y);
            storage.insert(data);
        } else {
            size_t y = (rand()%100000)+1;
            if (prev == '+') {
                if (storage.find(data) == storage.end()) {
                    t = t->insert(data, y);
                    storage.insert(data);
                }
            } else if (prev == '?') {
                if (storage.find(data + prev_res) == storage.end()) {
                    t = t->insert(data + prev_res, y);        
                    storage.insert(data + prev_res);
                }
            }
        }
        prev = '+';
      } else {
            int l = 0, r = 0;
            std::cin >> l >> r;
            if (t && l <= r) {
                std::pair<int, Treap<int, int>::Ptr> res = t->getSum(l-1, r-1);
                prev_res = res.first;
                t = res.second;
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

