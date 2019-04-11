#include <iostream>
#include <vector>
#include <utility>

struct Edge {
        int out = 0;
        int in = 0;
        int w = 0;

	Edge(int _out, int _in, int _w) {
		out = _out;
		in = _in;
		w = _w;
	}
};

std::vector<Edge> get_graph(int n) {
	std::vector<Edge> g;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int w = 0;
			std::cin >> w;
			if (w != 100000) {
				g.push_back(Edge(i, j, w));
			}
		}
	}
	return g;
}

void initialize(std::vector<int> &d, std::vector<int> &p, int k) {
	for (int i = 0; i < d.size(); i++) {
		p[i] = 0;
		d[i] = 100000;
	}
	d[k] = 0;
}

int relax(Edge e, std::vector<int> &p, std::vector<int> &d, std::vector<bool> &used) {
	if ((d[e.in] > d[e.out] + e.w) && (d[e.out] < 100000)) {
                d[e.in] = d[e.out] + e.w;
		used[e.in] = true;
                p[e.in] = e.out;
		return e.in;
        }
	return -1;
}

std::pair<int, std::vector<int>> ford_bellman(std::vector<Edge> &g, int n) {
	std::vector<int> d(n);
	std::vector<int> p(n);
	std::vector<bool> used(n);

	for (int k = 0; k < n; k++) {
		used[k] = false;
	}

	int x = -1;
	for (int k = 0; k < n; k++) {
		if (!used[k]) {
			initialize(d, p, k);
			for (int i = 0; i < n - 1; i++) {
				for (int j = 0; j < g.size(); j++) {
					int r = relax(g[j], p, d, used);
				}
			}
			
			for (int j = 0; j < g.size(); j++) {
				x = relax(g[j], p, d, used);
				if (x != -1)
					return std::make_pair(x, p);
			}
		}
	}
	return std::make_pair(x, p);
}

int main() {
	int n = 0;
    std::cin >> n;
	std::vector<Edge> g = get_graph(n);
	std::pair<int, std::vector<int>> res = ford_bellman(g, n);
	if (res.first == -1) {
		std::cout << "NO" << std::endl;
	} else {
		std::cout << "YES" << std::endl;
		std::vector<int> &p = res.second;
		int x = res.first;
		std::vector<int> path(n+1);
		for (int i = n; i >= 0; i--) {
			path[i] = x;
			x = p[x];
		}
		std::vector<int> cycle;
		for (int i = 0; i < path.size(); i++) {
			cycle.push_back(path[i]);
			if (i && path[i] == path[0])
				break;
		}

		std::cout << cycle.size() << std::endl;
		for (int i = 0; i < cycle.size(); i++) {
			std::cout << cycle[i]+1 << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
