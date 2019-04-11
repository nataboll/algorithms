#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

template<class T>
class segment_tree {
private:
	int n;
	std::vector<T> tree;

public:
	segment_tree(const std::vector<T> &_tree) : tree(_tree) {
		n = tree.size();
                n = (1 << (int)(std::log2(n-1)+1));
                tree.resize(2*n, 0);
                for (int i = n; i < 2*n; i++) {
                        tree[i] = tree[i-n];
                }
		for (int i = n-1; i > 0; i--) {
			tree[i] = 0;	// updates
		}
	}

	void update(int l, int r, T d) {
		l += (n-1);
		r += (n-1);
		while (l <= r) {
			if (l&1) {
				tree[l] += d;
			}
			if (!(r&1)) {
				tree[r] += d;
			}
			l = ((l+1)/2);
			r = ((r-1)/2);
		}
	}

	T get_value(int i) const {
		i += (n-1);
		T ans = 0;
		while (i) {
			ans += tree[i];
			i /= 2;
		}
		return ans;
	}
};

int main() {
	int n = 0;
	std::cin >> n;
	std::vector<long long> A(n);
	for (int i = 0; i < n; i++) {
		std::cin >> A[i];
	}
	int k = 0;
	std::cin >> k;
	std::vector<long long> ans;
	segment_tree<long long> tree(A);

	for (int i = 0; i < k; i++) {
		char task = 'n';
		std::cin >> task;
		if (task == 'g') {
			int num = 0;
			std::cin >> num;
			ans.push_back(tree.get_value(num));
		} else if (task == 'a') {
			int l = 0, r = 0;
			long long d = 0;
			std::cin >> l >> r >> d;
			tree.update(l, r, d);
		}
	}
	for (int i = 0; i < ans.size(); i++) {
		std::cout << ans[i] << std::endl;
	}
	return 0;
}
