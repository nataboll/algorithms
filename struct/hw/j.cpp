#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <cstdio>

template<class Ptr>
class Tree {
public:
	std::list<Ptr> tree;

	Tree(int n) : tree(n)
	{}

	Tree() = default;
};

template<class X, class Y>
class Treap: public std::enable_shared_from_this<Treap<X, Y>> {
public:
	typedef std::shared_ptr<Treap> Ptr;

	X x;
	Y y;
	int num;
	Ptr left;
	Ptr right;
	Ptr parent;

        Ptr getptr() {
                return this->shared_from_this();
        }

	Treap(int _num, X _x, Y _y) : num(_num)
				, x(_x)
				, y(_y)
				, left(Ptr())
				, right(Ptr())
				, parent(Ptr())
	{}

	Treap(const Treap<X, Y> &) = default;

	static void merge(Ptr &T, Ptr L, Ptr R) { // writes in T
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

	Ptr insert(int num, X x0, Y y0, Tree<Ptr> &tree) {
		Ptr L, R, T1, T;
		split(getptr(), x0, L, R);
		auto xy = std::make_shared<Treap<X, Y>>(num, x0, y0);
		tree.tree.push_back(xy);
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
	std::ios::sync_with_stdio(false);
	int n = 0;
	std::cin >> n;
	Tree<std::shared_ptr<Treap<int, int>>> tree;
	int a1 = 0, b1 = 0;
	std::cin >> a1 >> b1;
	auto t = std::make_shared<Treap<int, int>>(0, a1, b1);
	tree.tree.push_back(t);
	for (int i = 1; i < n; i++) { // change to linear time
		int ai = 0, bi = 0;
		std::cin >> ai >> bi;
		t = t->insert(i, ai, bi, tree);
	}
	std::cout << "YES" << std::endl;
	for (auto i = (tree.tree).begin(); i != (tree.tree).end(); ++i) {
		int par = ((*i)->parent) ? (*i)->parent->num+1 : 0;
                int l_num = ((*i)->left) ? (*i)->left->num+1 : 0;
                int r_num = ((*i)->right) ? (*i)->right->num+1 : 0;

		std::cout << par << " " << l_num << " " << r_num << std::endl;
	}	
	return 0;
}
