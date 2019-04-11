#include <iostream>
#include <vector>
#include <list>
#include <cstdio>

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

	int find_set(int x) {
		if (x == parent[x]) return x;
		return parent[x] = find_set(parent[x]);
	}

	void make_union(int x, int y, int _w) {
                x = find_set(x);
                y = find_set(y);
                if (x == y) {
                        w[x] += _w;
                        return;
                }
                if (w[x] > w[y]) {
                        std::swap(x, y);
                }
                parent[x] = y;
                w[y] = w[y] + w[x] + _w;
        }


	int get_weight(int v) {
		return w[find_set(v)];
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	int n = 0, m = 0;
	std::cin >> n >> m;
	DSU dsu(n);
	std::list<int> weights;
	for (int i = 0; i < m; i++) {
		int task = 0;
		std::cin >> task;
		if (task == 1) {
			int in = 0, out = 0, w = 0;
			std::cin >> out >> in >> w;
			dsu.make_union(out-1, in-1, w);
		} else {
			int v = 0;
			std::cin >> v;
			weights.push_back(dsu.get_weight(v-1));
		}
	}

	for (auto i = weights.begin(); i != weights.end(); ++i) {
		std::cout << *i << std::endl;
	}

	return 0;
}
