#include <iostream>
#include <vector>
#include <list>
#include <cstdio>

template<class X, class Y>
class Treap {
public:
    X x;
	Y y;
	Treap *left;
	Treap *right;
	int l_size;
    int r_size;

	Treap(X _x, Y _y) : y(_y)
                , x(_x)
				, left(nullptr)
				, right(nullptr)
				, l_size(0)
                , r_size(0)
	{}

	Treap(const Treap<X, Y> &) = default;

	static void merge(Treap *&T, Treap *L, Treap *R) { // writes in T
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
	}

	static void split(Treap *T, X x0, Treap *&T1, Treap *&T2) {
        if (!T)
            T1 = T2 = nullptr;
    	else {
        	if (x0 >= T->data) {
                split(T->right, x0, T->right, T2);
            	T1 = T;
			} else {
                split(T->left, x0, T1, T->left);
            	T2 = T;
            }
        }
	}

	Treap* insert(Treap *add) {
		Treap *L = nullptr, *R = nullptr, *T1 = nullptr, *T = nullptr;
		split(this, add->x, L, R);
		merge(T1, L, add);
		merge(T, T1, R); // T is a new treap
		return T;
	}

	Treap* remove(X x0) {
		Treap *L = nullptr, *R = nullptr, *L1 = nullptr, *R1 = nullptr, *T = nullptr;
		split(this, x0-1, L, R);
		split(R, x0, L1, R1);
		merge(T, L, R1);
    	return T;
	}	
};

int main() {
	std::string s;
    Treap<int, int> treap(0, 0);
    Treap<int, int> *t = &treap;
    bool empty = true;
	while (std::cin >> s) {
		if (s == "insert") {
			int data = 0;
			std::cin >> data;
			srand((unsigned)time(0)); 
            if (empty) {
                empty = false;
                t->x = data;
                t->y = rand()%100000 + 1;
            } else {
                Treap<int, int> add(data, (rand()%100000)+1);
			    t->insert(&add);
            }
		} else if (s == "delete") {
			int data = 0;
			std::cin >> data;
			t->remove(data);
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
