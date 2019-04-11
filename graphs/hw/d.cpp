#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <utility>

using Cycle = std::unique_ptr<std::list<int>>;

enum Color {
	WHITE,
	GRAY,
	BLACK,
};

std::vector<std::vector<int>> get_graph() {
	int n = 0, m = 0;
	std::cin >> n >> m;
	std::vector<std::vector<int>> g(n);
	for (int i = 0; i < m; i++) {
		int out = 0, in = 0;
		std::cin >> out >> in;
		g[out-1].push_back(in-1);
	}
	return g;
}

Cycle dfs_visit(int v, std::vector<std::vector<int>> &g, std::vector<Color> &color) {
	Cycle res;
	color[v] = GRAY;
	for (auto neighbor : g[v]) {
		if (color[neighbor] == WHITE) {
			res = dfs_visit(neighbor, g, color);	
			if (res.get()) {
//				std::cout << v+1 << " ";
				if (res->front() != res->back()) {
					res->push_back(v);
				}
				return res;
			}
		} else if (color[neighbor] == GRAY) {
//			std::cout << v+1 << " ";
			res.reset(new std::list<int>);
			res->push_back(neighbor);
			res->push_back(v);
			return res;
		}
	}
	color[v] = BLACK;
	return res;
}

Cycle get_cycle(std::vector<std::vector<int>> &g) {
	std::vector<Color> color(g.size());
	Cycle res;

	for (int i = 0; i < g.size(); i++) {
		color[i] = WHITE;
	}
	
	for (int i = 0; i < g.size(); i++) {
		if (color[i] == WHITE) {
			res = dfs_visit(i, g, color);
			if (res.get()) {
				break;
			}
		}
	}
	return res;
}

int main() {
	std::vector<std::vector<int>> g = get_graph();
	Cycle cycle = get_cycle(g);

	if (!cycle.get()) {
		std::cout << "NO" << std::endl;
	} else {
		std::cout << "YES" << std::endl;
		auto i = cycle->rbegin();
		++i;
		for (i; i != cycle->rend(); ++i) {
			std::cout << *i + 1 << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
