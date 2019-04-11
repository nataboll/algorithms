#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <map>
#include <cstdio>
#include <limits>
#include <list>

using Graph = std::map<int, std::vector<int>>;

uint32_t get_cost(Graph &g, std::vector<std::vector<int>> &elevators, int floors, int N, int U, int D, int LC) {
	std::vector<bool> used(floors);
	std::vector<uint32_t> d(floors);

	std::set<std::pair<uint32_t, int>> q;     

	for (int i = 0; i < floors; i++) {
		used[i] = false;
		d[i] = UINT32_MAX;
	}

	d[0] = 0;
	q.insert(std::make_pair(d[0], 0));

	while (!q.empty()) {
		int next = (q.begin())->second;
		q.erase(q.begin());
		used[next] = true;
		auto it = g.find(next);
		if (it != g.end()) {
			for (int i = 0; i < g[next].size(); i++) {	// g[next] contains numbers of elevators
				std::vector<int> &elevator = elevators[g[next][i]];
				for (int j = 0; j < elevator.size(); j++) {
					int &neigh = elevator[j];
					if (!used[neigh]) {
                                		if (d[neigh] > d[next] + LC) {
                                        		q.erase(std::make_pair(d[neigh], neigh));
                                        		d[neigh] = d[next] + LC;
                                        		q.insert(std::make_pair(d[neigh], neigh));
                                		}
					}
                        	}

			}
		}
		if (next > 0) {
			if (!used[next-1]) {
                                if (d[next-1] > d[next] + D) {
                                        q.erase(std::make_pair(d[next-1], next-1));
                                        d[next-1] = d[next] + D;
                                        q.insert(std::make_pair(d[next-1], next-1));
        	                }
                        }
		}
		if (next < floors-1) {
			if (!used[next+1]) {
                                if (d[next+1] > d[next] + U) {
                                        q.erase(std::make_pair(d[next+1], next+1));
                                        d[next+1] = d[next] + U;
                                        q.insert(std::make_pair(d[next+1], next+1));
                                }
                        }
		}
	}
	return d[N];
}

int main() {
	std::ios::sync_with_stdio(false);
	int N = 0, U = 0, D = 0, I = 0, J = 0, L = 0;
	std::cin >> N >> U >> D >> I >> J >> L;
        int floors = N;
        Graph g;
	std::vector<std::vector<int>> elevators(L);
        for (int i = 0; i < L; i++) {
                int K_i = 0;
                std::cin >> K_i;
                elevators[i] = std::vector<int>(K_i);
                for (int j = 0; j < K_i; j++) {
                        std::cin >> elevators[i][j];
                        floors = std::max(floors, elevators[i][j]);
                        elevators[i][j]--;
                }
                for (int j = 0; j < elevators[i].size(); j++) {
                        g[elevators[i][j]].emplace_back(i);
                }
        }

	std::cout << get_cost(g, elevators, floors, N-1, U, D, I+J) << std::endl;
	return 0;
}
