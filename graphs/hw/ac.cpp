#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <utility>

static const long long INF = 100000000000001;

struct Edge {
	int num = 0;
	long long w = 0;

	Edge(int _num, long long _w) : num(_num), w(_w) {}
};

using Graph = std::vector<std::vector<Edge>>;

Graph get_graph(int n, int m, std::vector<int> &start_fires) {
	Graph g(n+1);
	for (int i = 0; i < m; i++) {
		int out = 0, in = 0;
		long long w = 0;
		std::cin >> out >> in >> w;
		g[out-1].emplace_back(in-1, w);
		g[in-1].emplace_back(out-1, w);
	}
	
	for (int i = 0; i < start_fires.size(); i++) {
		g[n].emplace_back(start_fires[i], 0);	
	}
	return g;
}

std::vector<long long> get_fire_times(Graph &g, std::vector<int> &start_fires) {
	std::vector<long long> fire_times(g.size());
	std::vector<bool> used(g.size());
	std::set<std::pair<long long, int>> q;	// d[number] and number

	for (int i = 0; i < g.size()-1; i++) {
		used[i] = false;
		fire_times[i] = INF;
		q.insert(std::make_pair(fire_times[i], i));
	}

	int src = g.size()-1;
	used[src] = false;
	fire_times[src] = 0;
	q.insert(std::make_pair(0, src));

	while (!q.empty()) {
		int current = (q.begin())->second;
		q.erase(q.begin());
		used[current] = true;
		for (auto neighbor : g[current]) {
			if (!used[neighbor.num]) {
				if (fire_times[neighbor.num] > fire_times[current] + neighbor.w) {
					q.erase(std::make_pair(fire_times[neighbor.num], neighbor.num));
					fire_times[neighbor.num] = fire_times[current] + neighbor.w;
					q.insert(std::make_pair(fire_times[neighbor.num], neighbor.num));
				}
			}
		}
	}

	return fire_times;
}

long long get_time(Graph &g, std::vector<int> &start_fires, int s, int f) {
	std::vector<long long> fire_times = get_fire_times(g, start_fires);
	std::vector<long long> d(g.size());
	std::vector<bool> used(g.size());
	std::vector<long long> current_time(g.size());
        std::set<std::pair<long long, int>> q;  // d[number] and number
        for (int i = 0; i < g.size(); i++) {
                used[i] = false;
                d[i] = INF;
                q.insert(std::make_pair(d[i], i));
		current_time[i] = INF;
        }

        q.erase(std::make_pair(d[s], s));
        d[s] = 0;
        q.insert(std::make_pair(d[s], s));
	current_time[s] = 0;

        while (!q.empty()) {
                int current = (q.begin())->second;
                q.erase(q.begin());
                used[current] = true;
		
		if (current_time[current] >= fire_times[current] || d[current] == INF)
			continue;

                for (auto neighbor : g[current]) {
			if (used[neighbor.num] || current_time[neighbor.num] < current_time[current] + neighbor.w
				|| current_time[current] + neighbor.w >= fire_times[neighbor.num])
				continue;

			current_time[neighbor.num] = current_time[current] + neighbor.w;
			if (d[neighbor.num] > d[current] + neighbor.w) {
				q.erase(std::make_pair(d[neighbor.num], neighbor.num));
				d[neighbor.num] = d[current] + neighbor.w;
				q.insert(std::make_pair(d[neighbor.num], neighbor.num));
			}
                }
        }
	
	if (d[f] == INF)
		return -1;
	return d[f];
}

int main() {
	int n = 0, m = 0, k = 0;
	std::cin >> n >> m >> k;
	std::vector<int> start_fires(k);
	for (int i = 0; i < k; i++) {
		std::cin >> start_fires[i];
		start_fires[i]--;
	}
	Graph g = get_graph(n, m, start_fires);
	int s = 0, f = 0;
	std::cin >> s >> f;
	std::cout << get_time(g, start_fires, s-1, f-1) << std::endl;
	return 0;
}
