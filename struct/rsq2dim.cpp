#include <iostream>
#include <vector>

template<class Type>
class RSQ {
private:
	std::vector<std::vector<Type>> A;
	std::vector<std::vector<Type>> T;

public:
	RSQ(std::vector<std::vector<Type>> &_A) {
		A = _A;
		initialize_tree();
		A = _A;
	}

private:
	void initialize_tree() {
		T = std::vector<std::vector<Type>>(A.size());
		for (int i = 0; i < A.size(); i++) {
			T[i] = std::vector<Type>(A[i].size());
			for (int j = 0; j < A[i].size(); j++) {
				T[i][j] = 0;
			}
		}
		for (int i = 0; i < A.size(); i++) {
			for (int j = 0; j < A[i].size(); j++) {
				update(i, j, A[i][j]);
			}
		}
	}

	Type rsq(int x, int y) const {
		Type result = 0;
		for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
			for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
				result += T[i][j];
			}
		}
		return result;
	}

public:
	void update(int x, int y, Type d) {
		A[x][y] += d;
		for (int i = x; i < A.size(); i = (i | (i + 1))) {
			for (int j = y; j < A[i].size(); j = (j | (j + 1))) {
				T[i][j] += d;
			}
		}
	}

	Type rsq(int x1, int y1, int x2, int y2) const {
		return rsq(x2, y2) - rsq(x1-1, y2) - rsq(x2, y1-1) + rsq(x1-1, y1-1);
	}

	std::vector<std::vector<Type>> get_tree() const {
		return T;
	}

	std::vector<std::vector<Type>> get_array() const {
		return A;
	}

	Type get_tree(int x, int y) const {
                return T[x][y];
        }

	Type get_array(int x, int y) const {
		return A[x][y];
	}
};

int main() {
	int m = 0, n = 0;
	std::cin >> m >> n;
	std::vector<std::vector<long long>> A(m);
	for (int i = 0; i < m; i++) {
		A[i] = std::vector<long long>(n);
		for (int j = 0; j < n; j++) {
			std::cin >> A[i][j];
		}
	}
	RSQ<long long> rsq(A);
	int q = 0;
	std::cin >> q;
	std::vector<long long> res;
	for (int i = 0; i < q; i++) {
		char task = 'n';
		std::cin >> task;
		if (task == 's') {
			int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
			std::cin >> x1 >> y1 >> x2 >> y2;
			res.emplace_back(rsq.rsq(x1-1, y1-1, x2-1, y2-1));
		} else {
			int x = 0, y = 0;
			long long val = 0;
			std::cin >> x >> y >> val;
			rsq.update(x-1, y-1, val - rsq.get_array(x-1, y-1));	
		}
	}
	for (int i = 0; i < res.size(); i++) {
		std::cout << res[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}
