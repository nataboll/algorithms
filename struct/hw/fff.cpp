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

	Data() : open(0)
	       , close(0)
	       , max(0)
	{}

	Data(int _open, int _close, int _max) : open(_open)
                                        , close(_close)
						                , max(_max)
	{}
};

class segment_tree {
private:
	int n;
	std::vector<Data> tree;
	std::string s;

    int merge_open(const Data &left, const Data &right, int merge) const {
        return left.open + right.open - merge;
    }

    int merge_close(const Data &left, const Data &right, int merge) const {
        return left.close + right.close - merge;
    }

    int merge_max(const Data &left, const Data &right, int merge) const {
        return left.max + right.max + 2*merge;
    }

public:
	segment_tree(std::string &s) : tree(s.length())
	            			     , n(s.length())
	{
	    n = (1 << (int)(std::log2(n-1)+1));
        tree.resize(2*n);
        for (int i = n; i < n + s.length(); i++) {
            tree[i] = (s[i-n] == '(') ? Data(1, 0, 0) : Data(0, 1, 0);        
        }
		for (int i = n-1; i > 0; i--) {
			Data &left = tree[2*i], &right = tree[2*i+1];
			int merge = std::min(left.open, right.close);
			tree[i] = Data{merge_open(left, right, merge), merge_close(left, right, merge), merge_max(left, right, merge)};
		}
	}

	int rmq(int l, int r) {
		l += (n-1);
		r += (n-1);
		Data ansl, ansr;
		while (l <= r) {
			if (l&1) {
				int merge = std::min(ansl.open, tree[l].close);
				ansl = Data{merge_open(ansl, tree[l], merge), merge_close(ansl, tree[l], merge), merge_max(ansl, tree[l], merge)};
			}
			if (!(r&1)) {
				int merge = std::min(tree[r].open, ansr.close);
				ansr = Data{merge_open(tree[r], ansr, merge), merge_close(tree[r], ansr, merge), merge_max(tree[r], ansr, merge)};
			}
			l = ((l+1)/2);
			r = ((r-1)/2);
		}
		int merge = std::min(ansl.open, ansr.close);
		ansl = Data{merge_open(ansl, ansr, merge), merge_close(ansl, ansr, merge), merge_max(ansl, ansr, merge)};
		return ansl.max;
	}
};

int main() {
	std::string s;
	std::cin >> s;
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
