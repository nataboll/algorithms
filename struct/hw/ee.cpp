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
	std::vector<int> count;

public:
	segment_tree(const std::vector<T> &_tree) : tree(_tree), count(_tree.size(), 0) {
		n = tree.size();
                n = (1 << (int)(std::log2(n-1)+1));
                tree.resize(2*n, 0);
		count.resize(2*n, 0);
                for (int i = n; i < 2*n; i++) {
                        tree[i] = tree[i-n];
			count[i] = 1;
                }
		for (int i = n-1; i > 0; i--) {
			tree[i] = std::max(tree[2*i], tree[2*i+1]);
			int ch = (tree[i] == tree[2*i]) ? count[2*i] : count[2*i+1];
			count[i] = (tree[2*i] == tree[2*i+1]) ? (count[2*i] + count[2*i+1]) : ch;
		}
	}

	std::pair<T, int> rmq(int l, int r) const {
		l += (n-1);
		r += (n-1);
		T ans1 = 0;
		int ans2 = 0;
		while (l <= r) {
			if (l&1) {
				ans2 = (ans1 == tree[l]) ? (ans2 + count[l]) : ans2;
				if (tree[l] > ans1) {
					ans1 = tree[l];
					ans2 = count[l];
				}
			}
			if (!(r&1)) {
				ans2 = (ans1 == tree[r]) ? (ans2 + count[r]) : ans2;
                                if (tree[r] > ans1) {
                                        ans1 = tree[r];
                                        ans2 = count[r];
                                }
			}
			l = ((l+1)/2);
			r = ((r-1)/2);
		}
		return std::make_pair(ans1, ans2);
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
	std::vector<std::pair<long long, int>> ans(k);
	segment_tree<long long, LLONG_MAX> tree(A);

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
