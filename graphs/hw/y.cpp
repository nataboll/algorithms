#include <iostream>
#include <vector>
#include <utility>
#include <map>

#define INT_MAX 1000000001

using Edge = std::pair<int, int>;
using Graph = std::vector<std::vector<int>>;
using Edges = std::map<Edge, int>;

std::pair<Graph, Edges> get_data(int n, int m) {
        Graph g(n);
        Edges e;
        for (int i = 0; i < n; i++) {
                g[i] = std::vector<int>(n);
                for (int j = 0; j < n; j++) {
                        g[i][j] = INT_MAX;
                }
        }
        for (int i = 0; i < m; i++) {
                int out = 0, in = 0, w = 0;
                std::cin >> out >> in >> w;
		if (g[out-1][in-1] > -w) {
                	g[out-1][in-1] = -w;
                	e.insert(std::make_pair(std::make_pair(out-1, in-1), i));
		}
        }
        for (int i = 0; i < n; i++) {
                g[i][i] = 0;
        }
        return std::make_pair(g, e);
}

void restore_path(Graph &p, int s, int f, std::vector<int> &path) {
	int k = p[s][f];
//	std::cout << k+1 << " ";
	if (k == -1)
		return;
	restore_path(p, s, k, path);
	path.push_back(k);
	restore_path(p, k, f, path);
}

std::vector<int> get_path(Graph &g, std::vector<int> &cities) {
	std::vector<std::vector<int>> p(g.size());
	for (int i = 0; i < g.size(); i++) {
		p[i] = std::vector<int>(g.size());
		for (int j = 0; j < g.size(); j++) {
			p[i][j] = -1;
		}
	}
	for (int k = 0; k < g.size(); k++) {
		for (int i = 0; i < g.size(); i++) {
			for (int j = 0; j < g.size(); j++) {
				if (i != cities[cities.size()-1] && j != cities[cities.size()-1] && g[i][j] > g[i][k] + g[k][j] && g[i][k] < INT_MAX && g[k][j] < INT_MAX) {
					g[i][j] = g[i][k] + g[k][j];
					p[i][j] = k;
				}
			}
		}
	}

	p[cities[cities.size()-1]][cities[cities.size()-1]] = -1;

	for (int i = 0; i < cities.size()-1; i++) {
		if (p[cities[i]][cities[i]] != -1) {
			std::vector<int> err_path;
			err_path.push_back(-1);
			return err_path;
		}
	}

	std::vector<int> path;
        for (int j = 0; j < cities.size()-1; j++) {
		path.push_back(cities[j]);
		restore_path(p, cities[j], cities[j+1], path);
        }
	path.push_back(cities[cities.size()-1]);
	return path;
}

int main() {
	int n = 0, m = 0, k = 0;
        std::cin >> n >> m >> k;
	std::pair<Graph, Edges> data = get_data(n, m);
        Graph g = data.first;
        Edges e = data.second;
        std::vector<int> cities(k);
        for (int i = 0; i < k; i++) {
                std::cin >> cities[i];
                cities[i]--;
        }

	std::vector<int> path = get_path(g, cities);

	if (path[0] == -1) 
		std::cout << "infinitely kind" << std::endl;
	else {
		std::cout << path.size()-1 << std::endl;
		for (int j = 0; j < path.size()-1; j++) {
			std::cout << e[std::make_pair(path[j], path[j+1])]+1 << " ";
		}
	}
	return 0;
}
