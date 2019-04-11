#include <iostream>
#include <vector>
#include <queue>
#include <utility>

enum Color {
	WHITE,
	GRAY,
	BLACK,
};

using Graph = std::vector<std::vector<std::vector<int>>>;
using Vertex = std::pair<int, int>;

std::pair<Graph, std::vector<int>> get_graph() {
	int n = 0, m = 0;
	std::cin >> n >> m;
	Graph g(n);
	for (int i = 0; i < n; i++) {
		g[i] = std::vector<std::vector<int>>(m);
		for (int j = 0; j < m; j++) {
			g[i][j] = std::vector<int>(4);
                        g[i][j][0] = i; // up
                        g[i][j][1] = n-i-1; // down
                        g[i][j][2] = j; // left
                        g[i][j][3] = m-j-1; // right
		}
	}

	std::vector<int> dest(4);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c = '.';
			std::cin >> c;
			if (c == 'S') {
				dest[0] = i;
				dest[1] = j;
			} else if (c == 'T') {
				dest[2] = i;
				dest[3] = j;
			} else if (c == '#') {
				for (int k = 0; k < 4; k++) {
					g[i][j][k] = -1;
				}
				for (int k = j+1; k < m; k++) {
					if (g[i][k][2] > k-j-1) 
						g[i][k][2] = k-j-1;
				}
				for (int k = 0; k < j; k++) {
					if (g[i][k][3] > j-k-1)
						g[i][k][3] = j-k-1;
				}
				for (int k = i+1; k < n; k++) {
					if (g[k][j][0] > k-i-1)
						g[k][j][0] = k-i-1;
				}
				for (int k = 0; k < i; k++) {
					if (g[k][j][1] > i-k-1)
						g[k][j][1] = i-k-1;
				}
			}
			
		}
	}
	return std::make_pair(g, dest);
}

int get_steps(Graph &g, std::vector<int> &dest) {
	int n = g.size();
	int m = g[0].size();
	std::vector<std::vector<Color>> color(n);
	std::vector<std::vector<int>> p_i(n), p_j(n);
	for (int i = 0; i < n; i++) {
		color[i] = std::vector<Color>(m);
		p_i[i] = std::vector<int>(m);
		p_j[i] = std::vector<int>(m);
		for (int j = 0; j < m; j++) {
			color[i][j] = WHITE;
			p_i[i][j] = -1;
			p_j[i][j] = -1;
		}
	}
	std::queue<Vertex> q;
	q.push(std::make_pair(dest[0], dest[1]));
	color[dest[0]][dest[1]] = GRAY;

	while (!q.empty()) {
		Vertex current = q.front();
		q.pop();
		int i = current.first;
		int j = current.second;

		if (i == dest[2] && j == dest[3]) {
			break;
		}

		color[i][j] = BLACK;
		
		std::vector<int> new_i(4), new_j(4);

		new_i[0] = i - g[i][j][0] / 2 - g[i][j][0] % 2;
		new_j[0] = j;

		new_i[1] = i + g[i][j][1] / 2 + g[i][j][1] % 2;
                new_j[1] = j;

		new_i[2] = i;
                new_j[2] = j - g[i][j][2] / 2 - g[i][j][2] % 2;

		new_i[3] = i;
                new_j[3] = j + g[i][j][3] / 2 + g[i][j][3] % 2;

		for (int k = 0; k < 4; k++) {
			if (new_i[k] < 0 || new_i[k] >= n || new_j[k] < 0 || new_j[k] >= m)
				continue;
			if (color[new_i[k]][new_j[k]] == WHITE) {
				q.push(std::make_pair(new_i[k], new_j[k]));
				color[new_i[k]][new_j[k]] = GRAY;
				p_i[new_i[k]][new_j[k]] = i;
				p_j[new_i[k]][new_j[k]] = j;
			}
		}
	}
	if (color[dest[2]][dest[3]] == WHITE) 
		return -1;
	else {
		int steps = -1;
		int i = dest[2], j = dest[3];
		while (i != -1 && j != -1) {
			steps++;
			Vertex p = std::make_pair(p_i[i][j], p_j[i][j]);
			i = p.first;
			j = p.second;
		}
		return steps;
	}

}

int main() {
	std::pair<Graph, std::vector<int>> res = get_graph();
	Graph &g = res.first;
	std::vector<int> &dest = res.second;
	std::cout << get_steps(g, dest) << std::endl;
	return 0;
}
