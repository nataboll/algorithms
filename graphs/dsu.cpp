#include <iostream>
#include <vector>

struct Edge {
	int u;
	int v;
};

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
			int tmp = x;
			x = y;
			y = tmp;
		}	// now w[x]<w[y]
		parent[x] = y;
		w[y]+=w[x];
 	}

	std::vector<int> get_parents() {
		return parent;
	}

	std::vector<int> get_weights() {
		return w;
	}
};

int main() {
	int n = 0, m = 0;
	std::cin >> n >> m;
	std::vector<Edge> g(m);
	for (int i = 0; i < m; i++) {
		int in = 0, out = 0;
		std::cin >> out >> in;
		g[i] = Edge{out-1, in-1};
	}
	DSU dsu(n);
	std::vector<Edge> tree;

	for (int i = 0; i < m; i++) {
		if (dsu.find_set(g[i].u) != dsu.find_set(g[i].v)) {
			tree.push_back(g[i]);
			dsu.make_union(g[i].u, g[i].v);
		}
	}

	for (int i = 0; i < tree.size(); i++) {
		std::cout << tree[i].u+1 << " " << tree[i].v+1 << std::endl;
	}
	return 0;
}
