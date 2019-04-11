#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <map>
#include <queue>

enum Color {
	WHITE,
	GRAY,
	BLACK
};

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
		g[out-1].push_back(in-1);
		g[in-1].push_back(out-1);
		edges.insert(std::make_pair(std::make_pair(out-1, in-1), i+1));
		edges.insert(std::make_pair(std::make_pair(in-1, out-1), i+1));
	}
	return std::make_pair(g, edges);
}
 
void dfs(int v, int p, Graph &g, Edges &edges, std::vector<bool> &used, std::vector<int> &t_in, std::vector<int> &f_up, std::set<Edge> &bridges) {
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
			if (f_up[to] > t_in[v]) {
				bridges.insert(std::make_pair(v, to));
			}
		}
	}
}
 
Graph get_bridge_tree(Graph &g, Edges &edges, std::set<Edge> &bridges) {
	std::vector<Color> color(g.size());
	for (int i = 0; i < color.size(); i++) {
		color[i] = WHITE;
	}
	std::vector<int> components(g.size());
	int counter = -1;
	std::queue<int> q;
	for (int i = 0; i < g.size(); i++) {
		if (color[i] == WHITE) {
			counter++;
			q.push(i);
			color[i] = GRAY;
			while(!q.empty()) {
				int next = q.front();
				q.pop();
				color[next] = BLACK;
				components[next] = counter;
				for (auto neighbor : g[next]) {
					if (color[neighbor] == WHITE && (edges[std::make_pair(next, neighbor)] != -1)) {
						q.push(neighbor);
						color[neighbor] = GRAY;
					}
				}		
			}
		}
	}
	Graph tree(counter+1);
	for (auto b : bridges) {
		tree[components[b.first]].push_back(components[b.second]);
		tree[components[b.second]].push_back(components[b.first]);
	}
	return tree;
}

int get_leaves_number(Graph &tree) {
	int counter = 0;
        for (int i = 0; i < tree.size(); i++) {
		if (tree[i].size() == 1)
			counter++;
	}
	return counter;
}

int get_roads_number(Graph &g, Edges &edges) {
	std::vector<bool> used(g.size());
	std::vector<int> t_in(g.size()), f_up(g.size());
	std::set<Edge> bridges;
	for (int i = 0; i < g.size(); i++) {
		used[i] = false;
	}
	dfs(0, -1, g, edges, used, t_in, f_up, bridges); // get bridges
	for (auto b : bridges) {
		edges[b] = -1;
		edges[std::make_pair(b.second, b.first)] = -1;
	}
	
	Graph bridge_tree = get_bridge_tree(g, edges, bridges);

	if (g.size() == 1)
		return 0;
	int ans = get_leaves_number(bridge_tree);
	if (ans % 2 == 0)
		return ans/2;
	return (ans/2 + 1);
}

int main() {
	std::pair<Graph, Edges> data = get_data();	
	Graph g = data.first;
	Edges edges = data.second;
	std::cout << get_roads_number(g, edges) << std::endl;
	return 0;
}
