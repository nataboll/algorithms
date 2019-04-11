#include <iostream>
#include <vector>
#include <set>
#include <utility>

#define MAX 2009000999;

using Neighbor = std::pair<int, int>;
using Graph = std::vector<std::vector<Neighbor>>;

std::vector<std::vector<int>> get_distances(std::vector<Graph> &graphs, std::vector<int> &starts) {
	std::vector<std::vector<int>> distances(graphs.size());
	for (int i = 0; i < graphs.size(); i++) {	// every graph
		std::vector<bool> used(graphs[i].size());
                std::vector<int> d(graphs[i].size());

		std::set<std::pair<int, int>> q;	// <d, v>

		for (int j = 0; j < graphs[i].size(); j++) {
			used[i] = false;
			d[j] = MAX;
			q.insert(std::make_pair(d[j], j));
		}

		d[starts[i]] = 0;
		q.erase(std::make_pair(d[starts[i]], starts[i]));
		q.insert(std::make_pair(d[starts[i]], starts[i]));

		while (!q.empty()) {	// remaining vertexes
			int next = (*q.begin()).second;
			q.erase(*q.begin());
			used[next] = true; // is in S
			for (auto neighbor : graphs[i][next]) {
				if (!used[neighbor.first]) {
					if (d[neighbor.first] > d[next] + neighbor.second) {
						d[neighbor.first] = d[next] + neighbor.second;
						q.erase(std::make_pair(d[neighbor.first], neighbor.first));
						q.insert(std::make_pair(d[neighbor.first], neighbor.first));
					}
				}
			}
		}

		distances[i] = d;
	}
	return distances;
}

int main() {
	int num = 0; 
	std::cin >> num;
	std::vector<Graph> graphs(num);
	std::vector<int> starts(num);
        for (int i = 0; i < num; i++) {
        	int n_i = 0, m_i = 0;
		std::cin >> n_i >> m_i;
		graphs[i] = Graph(n_i);
		for (int j = 0; j < m_i; j++) {
			int out = 0, in = 0, w = 0;
			std::cin >> out >> in >> w;
			graphs[i][out].push_back(std::make_pair(in, w));
			graphs[i][in].push_back(std::make_pair(out, w));
		}
		int s = 0;
		std::cin >> s;
		starts[i] = s;
        }

	std::vector<std::vector<int>> distances = get_distances(graphs, starts);
	for (int i = 0; i < distances.size(); i++) {
		for (int j = 0; j < distances[i].size(); j++) {
			std::cout << distances[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
	return 0;
}
