#include <iostream>
#include <vector>

template<class T>
class RSQ {
private:
	std::vector<T> A;
	std::vector<T> P;

public:
	RSQ(int n) : A(n, 0)
		   , P(n, 0)
	{}

	void update(int l, int r, T d) {
		A[l] += d;
		if (r+1 < A.size())
			A[r+1] -= d;
	}

	void prefix() {
		P[0] = A[0];
		T delta = A[0];
		for (int i = 1; i < A.size(); i++) {
			delta += A[i];
			P[i] = P[i-1] + delta;
		}
	}

	T rsq(int l, int r) const {
		if (l == 0)
			return P[r];
		return (P[r] - P[l-1]);
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
                           , curr(0)
        {}

        T next_rand() {
                curr = curr * a + b;
                return curr >> 8;
        }
};

int main() {
        int m = 0, q = 0;
        unsigned a = 0, b = 0;
        std::cin >> m >> q >> a >> b;

	RSQ<unsigned> rsq(1 << 24);

        unsigned res = 0;
        Random<unsigned> rand(a, b);

        for (int i = 0; i < m; i++) {
                unsigned add = rand.next_rand();
                int l = (int)rand.next_rand();
                int r = (int)rand.next_rand();
                if (l > r)
                        std::swap(l, r);
                rsq.update(l, r, add);
        }
	
	rsq.prefix();

	for (int i = 0; i < q; i++) {
                int l = (int)rand.next_rand();
                int r = (int)rand.next_rand();
                if (l > r)
                        std::swap(l, r);
                res += rsq.rsq(l, r);
        }

        std::cout << res << std::endl;
	
	return 0;
}
