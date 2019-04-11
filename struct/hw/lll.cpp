#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include <cstdio>
#include <set>
#include <cassert>

template <class X, class Y>
class Treap {
private:
  Y y;
  Treap *left = nullptr;
  Treap *right = nullptr;
  X sum;

public:
  X x;
  Treap *getptr() { return this; }

  Treap(X _x, Y _y) : x(_x), y(_y), left(nullptr), right(nullptr), sum(_x) {}

  Treap() : x(0), y(0), left(nullptr), right(nullptr), sum(0) {}

  Treap(const Treap<X, Y> &) = default;

  ~Treap() {
      if (left)
          delete left;
      if (right)
          delete right;
  }

	static void merge(Treap *&T, Treap *L, Treap *R) {
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
            T->updateSum();
	}

	static void split(Treap *T, X x0, Treap *&T1, Treap *&T2) {
        if (!T)
            T1 = T2 = nullptr;
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

	Treap* insert(Treap *add) {
        if (!add)
            return this;

		Treap *L = nullptr, *R = nullptr, *T1 = nullptr, *T = nullptr;
		split(this, add->x, L, R);
		merge(T1, L, add);
		merge(T, T1, R); // T is a new treap
		return T;
	}

  bool exists(X x0) {
    Treap *cur = getptr();
    while (cur) {
      if (x0 == cur->x)
        return true;
      cur = (x0 > cur->x) ? cur->right : cur->left;
    }
    return false;
  }

  std::pair<X, Treap*> getSum(X l, X r) {
        Treap *L = nullptr, *R = nullptr, *L1 = nullptr, *R1 = nullptr, *T = nullptr;
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

  static X getSum(Treap *node) { return node ? node->sum : 0; }
};

int main() {
    srand((size_t)time(0));
    std::ios::sync_with_stdio(false);
    Treap<long long, size_t> treap;
    Treap<long long, size_t> *t = nullptr;
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
                treap = Treap<long long, size_t>(data % 1000000000, y);
                t = &treap;
            } else {
                if (!t->exists(data % 1000000000)) {
                    auto add = new Treap<long long, size_t>(data % 1000000000, y);
                    t = t->insert(add);
                }
            }
            ans = 0;
        } else {
            long long l = 0, r = 0;
            std::cin >> l >> r;
            if (t && (l <= r)) {
                std::pair<long long, Treap<long long, size_t> *> res = t->getSum(l, r);
                ans = res.first;
                t = res.second;
                std::cout << ans << std::endl;
            } else 
                std::cout << 0 << std::endl;
        }
    }
    return 0;
}
