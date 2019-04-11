#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <set>

typedef std::pair<int, int> Edge;

struct VertexProps {
	bool used = false;
	int in_time = 0;
	int up_steps = 0;
};

typedef std::vector<std::vector<int>> Graph;

typedef std::map<Edge, int> NumeratedEdges;

int cur_time = 0;

void make_structures(Graph &g, NumeratedEdges &edges) {
	int n = 0, m = 0;
	std::cin >> n >> m;
	for (int i = 0; i < n; i++) {
		std::vector<int> to_add;
		g.push_back(to_add);
	}
	for (int j = 0; j < m; j++) {
		int in_ver = 0, out_ver = 0;
		std::cin >> out_ver >> in_ver;
		g.at(--out_ver).push_back(--in_ver);
		g.at(in_ver).push_back(out_ver);
		Edge edge(out_ver, in_ver);
		edges.insert(std::pair<Edge, int>(edge, j));		
	}
}

void find_bridges_visit(int v, int p, Graph &g, NumeratedEdges &edges, std::vector<VertexProps> &props, std::vector<bool> is_used, std::set<int> &bridges) {
	props[v].used = true;
	props[v].in_time = ++cur_time;
	props[v].up_steps = cur_time;

	std::vector<int> neighbors = g.at(v);
	for (auto neighbor : neighbors) {
//		if (neighbor == v) continue;
		Edge current(v, neighbor);
		if (!props[neighbor].used) {
			find_bridges_visit(neighbor, v, g, edges, props, is_used, bridges);
			props[v].up_steps = std::min(props[v].up_steps, props[neighbor].up_steps);
		} else if (neighbor != p) {
			props[v].up_steps = std::min(props[v].up_steps, props[neighbor].in_time);
		}
	}
	if ((p != -1) && (props[v].in_time == props[v].up_steps)) {
		Edge pv(p, v); 
		bridges.insert(edges[pv]);
	}
}

std::set<int> find_bridges(Graph &g, NumeratedEdges &edges) {
	std::vector<VertexProps> props(g.size());

	std::vector<bool> is_used;
        for (int i = 0; i < edges.size(); i++) {
                is_used.push_back(false);
        }

	std::set<int> bridges;

	for (int i = 0; i < g.size(); i++) {
		if (!props[i].used) {
			find_bridges_visit(i, -1, g, edges, props, is_used, bridges);
		}

	}
	return bridges;
}

int main() {
	NumeratedEdges edges;
	Graph g;
	make_structures(g, edges);
/*	for (int i = 0; i < g.size(); i++) {
		std::vector<int> &to_print = g[i];
		std::cout << i+1 << ": ";
		for (int j = 0; j < to_print.size(); j++) {
			std::cout << to_print[j]+1 << " ";
		}
		std::cout << std::endl;
	}	*/
	std::set<int> all_bridges = find_bridges(g, edges);
	std::cout << all_bridges.size() << std::endl;
	for (auto e : all_bridges) {
		std::cout << e + 1 << " ";
	}
	std::cout << std::endl;
//	std::cout << edges[std::pair<int, int>(1, 2)] << " " << edges[std::pair<int, int>(2, 1)];
	return 0;
}
