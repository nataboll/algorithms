#include <iostream>
#include <vector>
#include <bitset>

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
	for (int i = 0; i < n-1; i++) {
		for (int j = i+1; j < n; j++) {
			char color = 'R';
			std::cin >> color;
			if (color == 'B') {
				g[i].push_back(j);	// blue edges remain right
			} else {
				g[j].push_back(i);	// reversing red edges
			}
		}
	}
	return g;
}


bool dfs_visit(int v, Graph &g, std::vector<Color> &color) {
        color[v] = GRAY;
        for (auto neighbor : g[v]) {
                if (color[neighbor] == WHITE) {
                        if (!dfs_visit(neighbor, g, color)) {
                                return false;
                        }
                } else if (color[neighbor] == GRAY) {
                        return false;
                }
        }
        color[v] = BLACK;
        return true;
}

bool is_monotone(Graph &g) {
        std::vector<Color> color(g.size());

        for (int i = 0; i < g.size(); i++) {
                color[i] = WHITE;
        }

        for (int i = 0; i < g.size(); i++) {
                if (color[i] == WHITE) {
                        if (!dfs_visit(i, g, color)) {
                                return false;
                        }
                }
        }
        return true;
}

int main() {
	Graph g = get_graph();

//	for (int i = 0; i < g.size(); i++) {
//		for (int j = 0; j < g[i].size(); j++) {
//			std::cout << g[i][j];
//		}
//		std::cout << std::endl;
//	}
	if (is_monotone(g))
		std::cout << "YES" << std::endl;
	else 
		std::cout << "NO" << std::endl;
	return 0;
}




