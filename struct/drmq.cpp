#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <climits>
#include <algorithm>

template<class T, long long INF = LLONG_MAX>
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
			tree[i] = std::max(tree[2*i], tree[2*i+1]);
		}
	}

	std::pair<T, int> rmq(int l, int r) const {
		l += (n-1);
		r += (n-1);
		T ans = 0;
		while (l <= r) {
			if (l&1) {
				ans = std::max(ans, tree[l]);
			}
			if (!(r&1)) {
				ans = std::max(ans, tree[r]);
			}
			l = ((l+1)/2);
			r = ((r-1)/2);
		}
		return std::make_pair(ans, 0);
	}
};

int main() {
	int n = 0;
	std::cin >> n;
	std::vector<int> A(n);
	for (int i = 0; i < n; i++) {
		std::cin >> A[i];
	}
	int k = 0;
	std::cin >> k;
	std::vector<std::pair<int, int>> ans(k);
	segment_tree<int, INT_MAX> tree(A);

	for (int i = 0; i < k; i++) {
		int l = 0, r = 0;
		std::cin >> l >> r;
		ans[i] = tree.rmq(l, r);
	}
	for (int i = 0; i < ans.size(); i++) {
		std::cout << ans[i].first << " " << ans[i].second << std::endl;
	}
	return 0;
}
