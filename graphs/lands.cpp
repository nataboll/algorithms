#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <set>
#include <algorithm>

class DSU {
private:
	std::vector<int> parent;
	std::vector<int> w;

public:
	DSU(int n)
		: parent(n)
		, w(n)
	{
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			w[i] = 0;
		}
	}

	void make_set() {
		parent.push_back(parent.size());

	}

	int find_set(int x) {
		if (x == parent[x]) return x;
		return parent[x] = find_set(parent[x]);
	}

	void make_union(int x, int y) {	
		x = find_set(x);
		y = find_set(y);
		if (w[x] > w[y]) {
			std::swap(x, y);
		}	// now w[x]<w[y]
		parent[x] = y;
		w[y]+=w[x];
 	}

	std::vector<int> get_parents() const {
		return parent;
	}

	std::vector<int> get_weights() const {
		return w;
	}
};

int main() {
	int n = 0, m = 0, k = 0;
	std::cin >> n >> m >> k;

	DSU dsu(n);
	for (int i = 0; i < m; i++) {
		int in = 0, out = 0;
		std::cin >> out >> in;
//		g.insert(std::make_pair(out-1, in-1));
	}

	std::vector<int> answers;
	std::vector<std::string> tasks(k);
	std::vector<int> outs(k);
	std::vector<int> ins(k);
	
	for (int i = 0; i < k; i++) {
		std::string task;
                int out = 0, in = 0;
                std::cin >> task >> out >> in;
		tasks[i] = task;
		outs[i] = out-1;
		ins[i] = in-1;
	}
	
	for (int i = k-1; i >= 0; i--) {
		if (tasks[i] == "cut") {
			dsu.make_union(outs[i], ins[i]);
		} else {
			if (dsu.find_set(outs[i]) == dsu.find_set(ins[i])) {
				answers.push_back(1);
			} else {
				answers.push_back(0);
			}
		}
	}

	for (int i = answers.size()-1; i >= 0; i--) {
		if (answers[i])
			std::cout << "YES" << std::endl;
		else std::cout << "NO" << std::endl;
	}

	return 0;
}
