#include <iostream>
#include <vector>

template<class Type>
class RSQ {
private:
	std::vector<std::vector<std::vector<Type>>> A;
	std::vector<std::vector<std::vector<Type>>> T;

public:
	RSQ(std::vector<std::vector<std::vector<Type>>> &_A) {
		A = _A;
		initialize_tree();
		A = _A;
	}

private:
	void initialize_tree() {
		T = A;	// zeros
		for (int i = 0; i < A.size(); i++) {
			for (int j = 0; j < A[i].size(); j++) {
				for (int k = 0; k < A[i][j].size(); k++) {
					update(i, j, k, A[i][j][k]);
				}
			}
		}
	}

	Type rsq(int x, int y, int z) const {
		Type result = 0;
		for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
			for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
				for (int k = z; k >= 0; k = (k & (k + 1)) - 1) {
					result += T[i][j][k];
				}
			}
		}
		return result;
	}

public:
	void update(int x, int y, int z, Type d) {
		A[x][y][z] += d;
		for (int i = x; i < A.size(); i = (i | (i + 1))) {
			for (int j = y; j < A[i].size(); j = (j | (j + 1))) {
				for (int k = z; k < A[i][j].size(); k = (k | (k + 1))) {
					T[i][j][k] += d;
				}
			}
		}
	}

	Type rsq(int x1, int y1, int z1, int x2, int y2, int z2) const {
		return rsq(x2, y2, z2) - rsq(x1-1, y2, z2) - rsq(x2, y1-1, z2) - rsq(x2, y2, z1-1) +
			 rsq(x1-1, y1-1, z2) + rsq(x1-1, y2, z1-1) + rsq(x2, y1-1, z1-1) -
			 rsq(x1-1, y1-1, z1-1); 
	}

	std::vector<std::vector<std::vector<Type>>> get_tree() const {
		return T;
	}

	std::vector<std::vector<std::vector<Type>>> get_array() const {
		return A;
	}

	Type get_tree(int x, int y, int z) const {
                return T[x][y][z];
        }

	Type get_array(int x, int y, int z) const {
		return A[x][y][z];
	}
};

int main() {
	int n = 0;
	std::cin >> n;
	std::vector<std::vector<std::vector<int>>> A(n);
	for (int i = 0; i < n; i++) {
		A[i] = std::vector<std::vector<int>>(n);
		for (int j = 0; j < n; j++) 
			A[i][j] = std::vector<int>(n, 0);
	}
	RSQ<int> rsq(A);
	std::vector<int> res;
	int task = -1;
	while (1) {
		std::cin >> task;
		if (task == 2) {
			int x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0;
			std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
			res.emplace_back(rsq.rsq(x1, y1, x2, y2, x3, y3));
		} else if (task == 1) {
			int x = 0, y = 0, z = 0, delta = 0;
			std::cin >> x >> y >> z >> delta;
			rsq.update(x, y, z, delta);	
		} else if (task == 3)
			break;
	}
	for (int i = 0; i < res.size(); i++) {
		std::cout << res[i] << std::endl;
	}

	return 0;
}
