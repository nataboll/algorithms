#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <climits>
#include <algorithm>
#include <string>

struct Data {
	int open = 0;
	int close = 0;
	int max = 0;
};

class segment_tree {
private:
	int n;
	std::vector<Data> tree;
	std::string s;

	int merge;

	int mergeOpen(const Data &left, const Data &right) const {
		return left.open + right.open - merge;
	}

	int mergeClose(const Data &left, const Data &right) const {
		return left.close + right.close - merge;
	}

	int mergeMax(const Data &left, const Data &right) const {
		if (merge) {
			return 0;
		}

		if ((left.flags & right) && (right.flags & left))
			return left.max + right.max;

		return std::max(left.max, right.max);
	}

public:
	segment_tree(std::string &s) : tree(s.length()), merge(0), n(s.length()) {
		for (int i = 0; i < n; i++) {
			tree[i] = (s[i] == '(') ? Data{1, 0, 0, 0} : Data{0, 1, 0, 0};	
		}
                n = (1 << (int)(std::log2(n-1)+1));
                tree.resize(2*n, Data{0, 0, 0, 0});
                for (int i = n; i < 2*n; i++) {
                        tree[i] = tree[i-n];
                }
		for (int i = n-1; i > 0; i--) {
			Data &left = tree[2*i], &right = tree[2*i+1];
			merge = std::min(left.open, right.close);
			tree[i] = Data{mergeOpen(left, right), mergeClose(left, right), mergeMax(left, right), mergeFlags(left, right)};
		}
	}

	int rmq(int l, int r) const {
		int len = r - l + 1;
		l += (n-1);
		r += (n-1);
		Data ans_l = Data{0, 0, 0};
		Data ans_r = Data{0, 0, 0};
		while (l <= r) {
			if (l&1) {
				int delta = ans_l.open - tree[l].close;
				if (delta == 0) {
	                                ans_l = Data{tree[l].open, ans_l.close, 0};
                        	} else if (delta > 0) {
                                	ans_l = Data{tree[l].open + delta, ans_l.close, 0};
                        	} else {
                                	ans_l = Data{tree[l].open, ans_l.close - delta, 0};
                        	}
			}
			if (!(r&1)) {
				int delta = tree[r].open - ans_r.close;
                                if (delta == 0) {
                                        ans_r = Data{ans_r.open, tree[r].close, 0};
                                } else if (delta > 0) {
                                        ans_l = Data{ans_r.open + delta, tree[r].close, 0};
                                } else {
                                        ans_l = Data{ans_r.open, tree[r].close - delta, 0};
                                }
			}
			l = ((l+1)/2);
			r = ((r-1)/2);
		}

		Data ans = Data{0, 0, 0};

		int delta = ans_l.open - ans_r.close;
                if (delta == 0) {
                        ans = Data{ans_r.open, ans_l.close, 0};
                } else if (delta > 0) {
                        ans = Data{ans_r.open + delta, ans_l.close, 0};
                } else {
                        ans = Data{ans_r.open, ans_l.close - delta, 0};
                }
			
		int count = len - ans.open - ans.close;
		if (count&1)
			count++;
		return count;
	}
};

int main() {
	std::string s;
	std::getline(std::cin, s);
	int k = 0;
	std::cin >> k;
	std::vector<int> ans(k);
	segment_tree tree(s);

	for (int i = 0; i < k; i++) {
		int l = 0, r = 0;
		std::cin >> l >> r;
		ans[i] = tree.rmq(l, r);
	}
	for (int i = 0; i < ans.size(); i++) {
		std::cout << ans[i] << std::endl;
	}
	return 0;
}
