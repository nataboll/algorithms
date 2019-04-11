#include <iostream>
#include <vector>

template<class Type>
class RSQ {
private:
	std::vector<Type> T;

public:
	RSQ(int n) : T(n, 0) 
	{}

private:
	Type rsq(int k) const {
		Type result = 0;
		while (k >= 0) {
			result += T[k];
			k = (k & (k + 1)) - 1;
		}
		return result;
	}

public:
	void resize_tree(int m) {
		T.resize(m);
	}

	void update(int k, Type d) {
		while (k < T.size()) {
			T[k] += d;
			k = k | (k + 1);
		}
	}

	Type rsq(int i, int j) const {
		j = (j >= T.size()) ? T.size()-1 : j;
		i = (i >= T.size()) ? T.size()-1 : i;
		return rsq(j) - rsq(i-1);
	}
};

template<class T>
class Random {
private:
	T curr;
	T a;
	T b;

public:
	Random(T _a, T _b) : a(_a)
			   , b(_b)
			   , curr((T)0)
	{}

	T next_rand() {
		curr = curr * a + b;
		return curr >> 8;
	}	
};

int main() {
	int n = (1 << 24), m = 0, q = 0;
	unsigned a = 0, b = 0;
	std::cin >> m >> q >> a >> b;

	RSQ<unsigned> rsq(n);
	unsigned res = 0;
	Random<unsigned> rand(a, b);
	
	int max = 0;
	for (int i = 0; i < m; i++) { // m*n*log(n)
		unsigned add = rand.next_rand();
		int l = (int)rand.next_rand(); 
		int r = (int)rand.next_rand(); 
		if (l > r) 
			std::swap(l, r);
		max = std::max(max, r);
		for (int j = l; j < r+1; j++) {
			rsq.update(j-1, add);
		}
	}

	rsq.resize_tree(max);

	for (int i = 0; i < q; i++) {	// q*log(n)
		int l = (int)rand.next_rand();
                int r = (int)rand.next_rand();
                if (l > r)
                        std::swap(l, r);
		res += rsq.rsq(l-1, r-1);
	}

	std::cout << res << std::endl;

	return 0;
}
