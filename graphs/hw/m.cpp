#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <map>

using Graph = std::vector<std::vector<int>>;
using Edge = std::pair<int, int>;
using Edges = std::map<Edge, int>;

int timer = 0;

std::pair<Graph, Edges> get_data() {
	int n = 0, m = 0;
	std::cin >> n >> m;
	Graph g(n);
	Edges edges;
	for (int i = 0; i < m; i++) {
		int out = 0, in = 0;
		std::cin >> out >> in;
		const Edge e = std::make_pair(out-1, in-1);
		if (edges.find(e) != edges.end()) {
			edges[std::make_pair(out-1, in-1)] = edges[std::make_pair(in-1, out-1)] = -1;
			continue;
		}
		g[out-1].push_back(in-1);
		g[in-1].push_back(out-1);
		edges.insert(std::make_pair(std::make_pair(out-1, in-1), i+1));
		edges.insert(std::make_pair(std::make_pair(in-1, out-1), i+1));
	}
	return std::make_pair(g, edges);
}
 
void dfs(int v, int p, Graph &g, Edges &edges, std::vector<bool> &used, std::vector<int> &t_in, std::vector<int> &f_up, std::set<int> &bridges) {
	used[v] = true;
	t_in[v] = f_up[v] = ++timer;
	for (int i = 0; i < g[v].size(); i++) {
		int to = g[v][i];
		if (to == p) continue;
		if (used[to])
			f_up[v] = std::min(f_up[v], t_in[to]);
		else {
			dfs(to, v, g, edges, used, t_in, f_up, bridges);
			f_up[v] = std::min(f_up[v], f_up[to]);
			if (f_up[to] > t_in[v] && edges[std::make_pair(v ,to)] != -1) {
				bridges.insert(edges[std::make_pair(v, to)]);
			}
		}
	}
}
 
std::set<int> find_bridges(Graph &g, Edges &edges) {
	std::vector<bool> used(g.size());
	std::vector<int> t_in(g.size()), f_up(g.size());
	std::set<int> bridges;
	for (int i = 0; i < g.size(); i++) {
		used[i] = false;
	}
	for (int i = 0; i < g.size(); i++) {
		if (!used[i]) {
			dfs(i, -1, g, edges, used, t_in, f_up, bridges);
		}
	}
	return bridges;
}

int main() {
	std::pair<Graph, Edges> data = get_data();	
	Graph g = data.first;
	Edges edges = data.second;
	std::set<int> bridges = find_bridges(g, edges);

	std::cout << bridges.size() << std::endl;
	for (auto b : bridges) {
		std::cout << b << " ";
	}
	std::cout << std::endl;

	return 0;
}
