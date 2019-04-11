#include <iostream>
#include <vector>

struct Edge {
	int out = 0;
	int in = 0;
	int w = 0;
};

std::vector<Edge> get_graph() {
	int m = 0;
	std::cin >> m;
	std::vector<Edge> g(m);
	for (int i = 0; i < m; i++) {
		int out = 0, in = 0, w = 0;
		std::cin >> out >> in >> w;
		Edge e;
		e.out = out - 1;
		e.in = in - 1;
		e.w = w;
		g[i] = e;
	}
	return g;
}

void initialize(std::vector<int> &d, std::vector<int> &p) {
	for (int i = 0; i < d.size(); i++) {
		p[i] = 0;
		d[i] = 30000;
	}
	d[0] = 0;
}

std::vector<int> ford_bellman(std::vector<Edge> &g, int n) {
	std::vector<int> d(n);
	std::vector<int> p(n);
	initialize(d, p);
	for (int i = 0; i < n - 2; i++) {
//		std::cout << "iter " << i+1 << std::endl;
		for (int j = 0; j < g.size(); j++) {
//			std::cout << "edge " << g[j].out << g[j].in << std:endl;
			if ((d[g[j].in] > d[g[j].out] + g[j].w) && (d[g[j].out] != 30000)) {
				d[g[j].in] = d[g[j].out] + g[j].w;
				p[g[j].in] = g[j].out;
			}
		}
	}
	return d;
}

int main() {
	int n = 0;
	std::cin >> n;
	std::vector<Edge> g = get_graph();
	std::vector<int> d = ford_bellman(g, n);
//	for (int i = 0; i < g.size(); i++) {
//		std::cout << g[i].out << g[i].in << g[i].w << std::endl;
//	}
	for (int i = 0; i < d.size(); i++) {
		std::cout << d[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}
