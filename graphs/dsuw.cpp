#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

struct Edge {
	int u;
	int v;
	int w;
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


std::vector<Edge> get_graph(int n) {
        int m = 0;
        std::cin >> m;
        std::vector<Edge> g(m);
        
        for (int i = 0; i < m; i++) {
                int out = 0, in = 0, w = 0;
                std::cin >> out >> in >> w;
                g[i] = Edge{out-1, in-1, w};
        }
        return g;
}

/*bool compare(Edge e1, Edge e2) {
        if (e1.w != e2.w) return e1.w < e2.w;
        return true;
}*/

class Fraction {
	int p, q;
public:
	Fraction operator+(const Fraction& other) const {
		return Fraction{this->p*other.q + this->q*other.p/(this->q * other.q)};
	}
};

void f()
{
	Fraction f{1,2}, g{3,4};
	Fraction x = f + g;
}

class EdgeCmp {
	public:

		bool operator() (const Edge& e1, const Edge& e2) const {
			return e1.w < e2.w;
		}
};

int get_mst_weight(std::vector<Edge> &g, int n) {
	DSU dsu(n);
	int w = 0;
	// sorting g
	std::sort(g.begin(), g.end(), [](const Edge&e1, Edge& e2){ return e1.w < e2.w; });
	for (int i = 0; i < g.size(); i++) {
		if (dsu.find_set(g[i].u) != dsu.find_set(g[i].v)) {
                	dsu.make_union(g[i].u, g[i].v);
                        w += g[i].w;
                }
	}
	return w;
}

int main() {

	int n = 0;
	std::cin >> n;
	std::vector<Edge> g = get_graph(n);	// get topology
	int w = get_mst_weight(g, n);
	std::cout << w << std::endl;
	return 0;
}
