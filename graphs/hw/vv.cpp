#include <iostream>
#include <vector>

struct Edge {
	int out = 0;
	int in = 0;
	int w = 0;
};

std::vector<Edge> get_graph(int m) {
	std::vector<Edge> g(m);
	for (int i = 0; i < m; i++) {
		int out = 0, in = 0, w = 0;
		std::cin >> out >> in >> w;
		Edge e;
		e.out = in - 1;	// reversed graph
		e.in = out - 1;
		e.w = w;
		g[i] = e;
	}
	return g;
}

void initialize(std::vector<int> &d, std::vector<int> &p, std::vector<int> &e, int f) {
	for (int i = 0; i < d.size(); i++) {
		p[i] = -1;
		d[i] = 100000;
		e[i] = 101;
	}
	d[f] = 0;
	e[f] = 0;
}

int ford_bellman(std::vector<Edge> &g, int n, int k, int s, int f) {
	std::vector<int> d(n);
	std::vector<int> p(n);
	std::vector<int> e(n);	// numbers of edges from start vertex
	initialize(d, p, e, f);

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < g.size(); j++) {
			if ((d[g[j].in] > d[g[j].out] + g[j].w) && (d[g[j].out] != 100000)) {
				if (e[g[j].out] <= i) {
					d[g[j].in] = d[g[j].out] + g[j].w;
					p[g[j].in] = g[j].out;
					e[g[j].in] = e[g[j].out] + 1;
				}
			}
		}
	}
	if (p[s] != -1) return d[s];
	else return -1;
}

int main() {
	int n = 0, m = 0, k = 0, s = 0, f = 0;
	std::cin >> n >> m >> k >> s >> f;
	std::vector<Edge> g = get_graph(m);
	std::cout << ford_bellman(g, n, k, s-1, f-1) << std::endl;
	return 0;
}
