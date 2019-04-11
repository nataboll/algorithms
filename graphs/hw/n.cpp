#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <map>

using Graph = std::vector<std::vector<int>>;

int timer = 0;

Graph get_graph() {
	int n = 0, m = 0;
	std::cin >> n >> m;
	Graph g(n);
	for (int i = 0; i < m; i++) {
		int out = 0, in = 0;
		std::cin >> out >> in;
		g[out-1].push_back(in-1);
		g[in-1].push_back(out-1);
	}
	return g;
}
 
void dfs(int v, int p, Graph &g, std::vector<bool> &used, std::vector<int> &t_in, std::vector<int> &f_up, std::set<int> &cut_points) {
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
			dfs(to, v, g, used, t_in, f_up, cut_points);
			f_up[v] = std::min(f_up[v], f_up[to]);
			if (f_up[to] >= t_in[v] && p != -1) {
				cut_points.insert(v+1);
			}
		}
	}
	if (p == -1 && children > 1) {
		cut_points.insert(v+1);
	}
}
 
std::set<int> find_cut_points(Graph &g) {
	std::vector<bool> used(g.size());
	std::vector<int> t_in(g.size()), f_up(g.size());
	std::set<int> cut_points;
	for (int i = 0; i < g.size(); i++) {
		used[i] = false;
	}
	for (int i = 0; i < g.size(); i++) {
		if (!used[i]) {
			dfs(i, -1, g, used, t_in, f_up, cut_points);
		}
	}
	return cut_points;
}

int main() {
	Graph g = get_graph();
	std::set<int> cut_points = find_cut_points(g);

	std::cout << cut_points.size() << std::endl;
	for (auto p : cut_points) {
		std::cout << p << std::endl;
	}

	return 0;
}
