#include <iostream>
#include <memory>

template<class X, class Y>
class Treap: public std::enable_shared_from_this<Treap<X, Y>> {
public:
	typedef std::shared_ptr<Treap> Ptr;

	X x;
	Y y;
	Ptr left;
	Ptr right;

        Ptr getptr() {
                return this->shared_from_this();
        }

	Treap(X _x, Y _y) : x(_x)
				, y(_y)
				, left(Ptr())
				, right(Ptr())
	{}

	Treap(const Treap<X, Y> &) = default;

	static void merge(Ptr &T, Ptr L, Ptr R) { // writes in T
        	if (!L || !R) {
                	if (L) 
                        	T = L;
                	else
                	        T = R;
        	} else if (L->y > R->y) {
                	merge(L->right, L->right, R);
                	T = L;
        	} else {
                	merge(R->left, L, R->left);
                	T = R;
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
        	}
	}

	Ptr insert(X x0, Y y0) {
		Ptr L, R, T1, T;
		split(getptr(), x0, L, R);
		auto xy = std::make_shared<Treap<X, Y>>(x0, y0);
		merge(T1, L, xy);
		merge(T, T1, R); // T is a new treap
		return T;
	}

	Ptr remove(X x0) {
		Ptr L, R, L1, R1, T;
		split(getptr(), x0-1, L, R);
		split(R, x0, L1, R1);
		merge(T, L, R1);
		return T;
	}	
};

int main() {
	auto t = std::make_shared<Treap<int, int>>(7, 1);
	t = t->insert(2, 3);
	t = t->insert(5, 2);
	auto tt = t;
	while (tt) {
		std::cout << tt->x << " ";
		tt = tt->right;
	}
	t = t->remove(2);
	std::cout << std::endl;
	while (t) {
                std::cout << t->x << " ";
                t = t->right;
        }
	return 0;
}
