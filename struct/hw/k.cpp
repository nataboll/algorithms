#include <iostream>
#include <memory>
#include <string>
#include <cstdlib> 
#include <ctime> 

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

    Ptr exists(X x0) {
		Ptr L, R, L1, R1;
		split(getptr(), x0-1, L, R);
		split(R, x0, L1, R1);
        return L1;
    }

    Ptr next(X x0) {
        Ptr current = getptr(), ans;
        while (current) {
            if (current->x > x0) {
                ans = current;
                current = current->left;
            } else
                current = current->right;
        }
        return ans;
    }
};

int main() {
    srand((unsigned)time(0)); 
	std::string s;
    std::shared_ptr<Treap<int, int>> t;
	while (std::cin >> s) {
		if (s == "insert") {
			int data = 0;
			std::cin >> data;
            if (!t)
                t = std::make_shared<Treap<int, int>>(data, rand()%100000 + 1);
            else
			    t = t->insert(data, (rand()%100000)+1);

		} else if (s == "delete") {
			int data = 0;
			std::cin >> data;
			t = t->remove(data);
		} else if (s == "exists") {
			int data = 0; 
			std::cin >> data;
            bool ans = (t->exists(data)) ? true : false;
            std::cout << ans << std::endl;
		} else if (s == "next") {
			int data = 0;
            std::cin >> data;
            bool ans = (t->exists(data)) ? true : false;
            std::cout << ans << std::endl;
        } else if (s == "prev") {
			int data = 0;
            std::cin >> data;
        } else if (s == "kth") {
			int data = 0;
            std::cin >> data;
		}
	}
	return 0;
}
