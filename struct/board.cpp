#include <iostream>
#include <vector>
#include <string>

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
			T[i] = std::vector<Type>(A[i].size(), 0);
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
		int x_1 = std::min(x1, x2);
		int x_2 = std::max(x1, x2);
		int y_1 = std::min(y1, y2);
		int y_2 = std::max(y1, y2);
		return rsq(x_2, y_2) - rsq(x_1-1, y_2) - rsq(x_2, y_1-1) + rsq(x_1-1, y_1-1);
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
	int n = 0, q = 0;
	std::cin >> n >> q;
	std::vector<std::vector<int>> A(n);
	for (int i = 0; i < n; i++) {
		A[i] = std::vector<int>(n);
		for (int j = 0; j < n; j++) {
			A[i][j] = 0;
		}
	}
	RSQ<int> rsq(A);
	std::vector<int> res;
	for (int i = 0; i < q; i++) {
		std::string task = "NO";
		std::cin >> task;
		if (task == "GET") {
			int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
			std::cin >> x1 >> y1 >> x2 >> y2;
			res.emplace_back(rsq.rsq(x1-1, y1-1, x2-1, y2-1));
		} else if (task == "ADD") {
			int x = 0, y = 0;
			std::cin >> x >> y;
			rsq.update(x-1, y-1, 1);	
		}
	}
	for (int i = 0; i < res.size(); i++) {
		std::cout << res[i] << std::endl;
	}

	return 0;
}
