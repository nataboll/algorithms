#include <iostream>
#include <vector>
#include <queue>

enum Color {
	WHITE,
	GRAY,
	BLACK,
};

using Graph = std::vector<std::vector<int>>;

Graph get_graph() {
	int n = 0;
	std::cin >> n;

	Graph g(n);
	for (int i = 0; i < n; i++) {
		int out = 0;
		std::cin >> out;
		g[out-1].push_back(i);
		g[i].push_back(out-1);
	}
	return g;
}

int count_broken(Graph &g) {
	int counter_broken = 0;
	std::vector<Color> color(g.size());

	for (int i = 0; i < color.size(); i++) {
		color[i] = WHITE;
	}
	
	std::queue<int> q;
	for (int i = 0; i < g.size(); i++) {
		if (color[i] == WHITE) {
			counter_broken++;
			q.push(i);
			color[i] = GRAY;
			while (!q.empty()) {
				int current = q.front();
				color[current] = BLACK;
				q.pop();
				for (auto neighbor : g[current]) {
					if (color[neighbor] == WHITE) {
						q.push(neighbor);
						color[neighbor] = GRAY;
					}
				}
			}
		}
	}
	return counter_broken;
}

int main() {
	Graph g = get_graph();
	std::cout << count_broken(g) << std::endl;
}
