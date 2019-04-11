#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <algorithm>
#include <functional>

static const long long INF = 3000000000;

enum Color {
	WHITE,
	GRAY, 
	BLACK,
};

struct Route {
	int source = 0;
	int destination = 0;
	long long capacity = 0;

	Route(int _source, int _destination, long long _capacity)
		: source(_source)
		, destination(_destination)
		, capacity(_capacity)
	{}

	Route() = default;
	Route(const Route&) = default;
};

struct compare {
	bool operator() (std::pair<long long, int> cross_1, std::pair<long long, int> cross_2) const {
		return cross_1.first > cross_2.first;
	}
};

using Neighbor = std::pair<int, long long>;	// number and distance
using Graph = std::vector<std::vector<Neighbor>>;

std::vector<long long> get_nearest_stations_dist(Graph g, std::vector<int> &stations) {
	std::vector<bool> used(g.size()+1);
	std::vector<long long> d(g.size()+1);
	std::set<std::pair<long long, int>> q; 

	std::vector<Neighbor> to_add(stations.size());
        for (int i = 0; i < stations.size(); i++) {
                to_add[i] = std::make_pair(stations[i], 0);
        }
        g.push_back(to_add);

	for (int i = 0; i < g.size(); i++) {
		used[i] = false;
		d[i] = INF;
		q.insert(std::make_pair(d[i], i));
	}

	q.erase(std::make_pair(d[g.size()-1], g.size()-1));
	d[g.size()-1] = 0;
	q.insert(std::make_pair(d[g.size()-1], g.size()-1));

        while (!q.empty()) { 
                int next = (q.begin())->second;
                q.erase(q.begin());
                used[next] = true; 
		if (d[next] == INF)
			continue;
                for (auto neighbor : g[next]) {
                        if (!used[neighbor.first]) {
                                if (d[neighbor.first] > d[next] + neighbor.second) {
                                        q.erase(std::make_pair(d[neighbor.first], neighbor.first));
					d[neighbor.first] = d[next] + neighbor.second;
                                        q.insert(std::make_pair(d[neighbor.first], neighbor.first));
                                }
                        }
                }
        }

	return d;
}

std::vector<bool> is_reachable(Graph &g, std::vector<Route> &routes, std::vector<int> &stations) {
	std::vector<bool> reachable(routes.size());
	std::vector<long long> nearest_stations_dist = get_nearest_stations_dist(g, stations);

	for (int i = 0; i < routes.size(); i++) {  // for every route
//		std::cout << "route " << i+1 << std::endl; 
		std::vector<bool> used(g.size());
		std::vector<long long> oil(g.size());
       		std::set<std::pair<long long, int>, compare> q; // (-oil, num)
		
	        for (int i = 0; i < g.size(); i++) {
                	used[i] = false;
			oil[i] = -1;
//			q.insert(std::make_pair(oil[i], i));
        	}

		int s = routes[i].source;
		int f = routes[i].destination;

//	        q.erase(std::make_pair(oil[s], s));
        	oil[s] = routes[i].capacity;
        	q.insert(std::make_pair(oil[s], s));

        	while (!q.empty()) {
                	int curr = (q.begin())->second;
                	q.erase(q.begin());
                	used[curr] = true;
//			std::cout << curr+1 << " : " << oil[curr] << std::endl;
                	for (auto neighbor : g[curr]) {
                        	if (!used[neighbor.first]) {
                                	if (oil[curr] >= neighbor.second) {
						q.erase(std::make_pair(oil[neighbor.first], neighbor.first));
						oil[neighbor.first] = oil[curr] - neighbor.second;
						if (nearest_stations_dist[neighbor.first] <= oil[neighbor.first]) {
							if (routes[i].capacity - nearest_stations_dist[neighbor.first] > oil[neighbor.first]) {
                              					oil[neighbor.first] = routes[i].capacity - nearest_stations_dist[neighbor.first];
                      					}
						}
						q.insert(std::make_pair(oil[neighbor.first], neighbor.first));
                                	}
                        	}
                	}
        	}

		reachable[i] = (oil[f] != -1);
	}
	
	return reachable;
}

int main() {
	int n = 0, s = 0, m = 0; 
	std::cin >> n >> s >> m;

	std::vector<int> stations(s);
	for (int i = 0; i < s; i++) {
		int st = 0;
		std::cin >> st;
		stations[i] = st-1;
	}

	Graph g(n);

        for (int i = 0; i < m; i++) {
        	int out = 0, in = 0;
		long long w = 0;
		std::cin >> out >> in >> w;
		g[out-1].push_back(std::make_pair(in-1, w));
		g[in-1].push_back(std::make_pair(out-1, w));
        }

	int q = 0;
	std::cin >> q;
	std::vector<Route> routes(q);
	for (int i = 0; i < q; i++) {
		int src = 0, dst = 0;
		long long cap  = 0;
		std::cin >> src >> dst >> cap;
		routes[i] = Route(src-1, dst-1, cap);
	}

	std::vector<bool> reachable = is_reachable(g, routes, stations);
	for (int i = 0; i < reachable.size(); i++) {
		if (reachable[i])
			std::cout << "TAK" << std::endl;
		else
			std::cout << "NIE" << std::endl;
	}
	
	return 0;
}
