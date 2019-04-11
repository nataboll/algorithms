#include <iostream>
#include <vector>
#include <list>

using Sequence = std::list<int>;
using Graph = std::vector<std::vector<int>>;

enum Color {
	WHITE,
	GRAY,
	BLACK,
};

Graph get_graph() {
	int n = 0, m = 0;
	std::cin >> n >> m;
	Graph g(n);
	for (int i = 0; i < m; i++) {
		int out = 0, in = 0;
		std::cin >> out >> in;
		g[out-1].push_back(in-1);
	}
	return g;
}

bool dfs_visit(int v, Graph &g, std::vector<Color> &color, Sequence &seq) {
	color[v] = GRAY;
	for (auto neighbor : g[v]) {
		if (color[neighbor] == WHITE) {
			if (!dfs_visit(neighbor, g, color, seq)) {
				return false;
			}
		} else if (color[neighbor] == GRAY) {
			return false;
		}
	}
	color[v] = BLACK;
	seq.push_front(v);
	return true;
}

Sequence get_seq(Graph &g) {
	std::vector<Color> color(g.size());
	Sequence seq;

	for (int i = 0; i < g.size(); i++) {
		color[i] = WHITE;
	}
	
	for (int i = 0; i < g.size(); i++) {
		if (color[i] == WHITE) {
			if (!dfs_visit(i, g, color, seq)) {
				Sequence empty_seq;
				return empty_seq;
			}
		}
	}
	return seq;
}

int main() {
	std::vector<std::vector<int>> g = get_graph();
	Sequence seq = get_seq(g);

	if (seq.empty()) {
		std::cout << -1 << std::endl;
	} else {
		for (auto i = seq.begin(); i != seq.end(); ++i) {
			std::cout << *i + 1 << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
