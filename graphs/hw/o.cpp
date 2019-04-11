#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using Graph = std::vector<std::vector<int>>;

int timer = 0;

Graph get_graph(int n, int m) {
	Graph g(n+m);
	for (int i = 0; i < m; i++) {
		int v[3];
		std::cin >> v[0] >> v[1] >> v[2];
		for (int j = 0; j < 3; j++) {
			g[n+i].push_back(v[j]-1);
			g[v[j]-1].push_back(n+i);
		}
	}
	return g;
}
 
void dfs(int v, int p, Graph &g, int n, std::vector<bool> &used, std::vector<int> &t_in, std::vector<int> &f_up, std::set<int> &cut_points) {
	used[v] = true;
	t_in[v] = f_up[v] = ++timer;
	int children = 0;
	for (int i = 0; i < g[v].size(); i++) {
		int to = g[v][i];
		if (to == p) continue;
		if (used[to])
			f_up[v] = std::min(f_up[v], t_in[to]);
		else {
			children++;
			dfs(to, v, g, n, used, t_in, f_up, cut_points);
			f_up[v] = std::min(f_up[v], f_up[to]);
			if (f_up[to] >= t_in[v] && p != -1 && v >= n) {
				cut_points.insert(v-n+1);
			}
		}
	}
	if (p == -1 && children > 1 && v >= n) {
		cut_points.insert(v-n+1);
	}
}
 
std::set<int> find_cut_points(Graph &g, int n) {
	std::vector<bool> used(g.size());
	std::vector<int> t_in(g.size()), f_up(g.size());
	std::set<int> cut_points;
	for (int i = 0; i < g.size(); i++) {
		used[i] = false;
	}
	for (int i = 0; i < g.size(); i++) {
		if (!used[i]) {
			dfs(i, -1, g, n, used, t_in, f_up, cut_points);
		}
	}
	return cut_points;
}

int main() {
	int n = 0, m = 0;
	std::cin >> n >> m;
	Graph g = get_graph(n, m);
	std::set<int> cut_points = find_cut_points(g, n);

	std::cout << cut_points.size() << std::endl;
	for (auto p : cut_points) {
		std::cout << p << " ";
	}
	std::cout << std::endl;

	return 0;
}
