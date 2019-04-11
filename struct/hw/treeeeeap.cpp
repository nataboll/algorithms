#include <iostream>
#include <vector>
#include <list>
#include <cstdio>

template<class X, class Y, class D>
class Treap {
public:
	X x;
	Y y;
	D data;
	Treap *left;
	Treap *right;
	Treap *parent;

	Treap(D _data, X _x, Y _y) : data(_data)
				, x(_x)
				, y(_y)
				, left(nullptr)
				, right(nullptr)
				, parent(nullptr)
	{}

	Treap(const Treap<X, Y, D> &) = default;

	static void merge(Treap *&T, Treap *L, Treap *R) { // writes in T
        	if (!L || !R) {
                	if (L) 
                        	T = L;
                	else
                	        T = R;
        	} else if (L->y < R->y) {
                	merge(L->right, L->right, R);
			L->right->parent = L;
                	T = L;
        	} else {
                	merge(R->left, L, R->left);
			R->left->parent = R;
			T = R;
        	}
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
	;	return T;
	}	
};

int main() {
	std::ios::sync_with_stdio(false);
	int n = 0;
	std::cin >> n;
	std::list<Treap<int, int, int> *> tree;
	int a = 0, b = 0;
	std::cin >> a >> b;
	Treap<int, int, int> *t = new Treap<int, int, int>(0, a, b);
	tree.push_back(t);
	for (int i = 1; i < n; i++) {
		std::cin >> a >> b;
		Treap<int, int, int> *add = new Treap<int, int, int>(i, a, b);
		tree.push_back(add);
		t = t->insert(add);
	}
	std::cout << "YES" << std::endl;
	for (auto i = tree.begin(); i != tree.end(); ++i) {
		int par = ((*i)->parent) ? (*i)->parent->data+1 : 0;
                int l_num = ((*i)->left) ? (*i)->left->data+1 : 0;
                int r_num = ((*i)->right) ? (*i)->right->data+1 : 0;

		std::cout << par << " " << l_num << " " << r_num << std::endl;
	}
	for (auto i = tree.begin(); i != tree.end(); ++i) {
		delete [] (*i);
	}
	return 0;
}
