#include <iostream>
#include <vector>

template<class Type>
class RSQ {
private:
	std::vector<Type> A;
	std::vector<Type> T;

public:
	RSQ(std::vector<Type> &_A) {
		A = _A;
		initialize_tree();
		A = _A;
	}

private:
	void initialize_tree() {
		T = std::vector<Type>(A.size());
		for (int i = 0; i < A.size(); i++) {
			T[i] = 0;
		}
		for (int i = 0; i < A.size(); i++) {
			update(i, A[i]);
		}
	}

	Type rsq(int k) const {
		Type result = 0;
		while (k >= 0) {
			result += T[k];
			k = (k & (k + 1)) - 1;
		}
		return result;
	}

public:
	void update(int k, Type d) {
		A[k] += d;
		while (k < A.size()) {
			T[k] += d;
			k = k | (k + 1);
		}
	}

	Type rsq(int i, int j) const {
		return rsq(j) - rsq(i-1);
	}

	std::vector<Type> get_tree() const {
		return T;
	}

	std::vector<Type> get_array() const {
		return A;
	}

	Type get_tree(int num) const {
                return T[num];
        }

	Type get_array(int num) const {
		return A[num];
	}
};

int main() {
	int n = 0;
	std::cin >> n;
	std::vector<long long> A(n);
	for (int i = 0; i < n; i++) {
		std::cin >> A[i];
	}
	RSQ<long long> rsq(A);
	int m = 0;
	std::cin >> m;
	std::vector<long long> res;
	for (int i = 0; i < m; i++) {
		char task = 'u';
		std::cin >> task;
		if (task == 's') {
			int s = 0, f = 0;
			std::cin >> s >> f;
			res.emplace_back(rsq.rsq(s-1, f-1));
		} else {
			int num = 0;
			long long val = 0;
			std::cin >> num >> val;
			rsq.update(num-1, val - rsq.get_array(num-1));	
		}
	}
	for (int i = 0; i < res.size(); i++) {
		std::cout << res[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}
