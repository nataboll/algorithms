#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <cstdio>

template<class ForwardIt, class T, class Compare=std::less<int>>
ForwardIt binary_find(ForwardIt first, ForwardIt last, const T& value, Compare comp={})
{
    first = std::lower_bound(first, last, value, comp);
    return first != last && !comp(value, *first) ? first : last;
}

static const long long INF = 2000000000000;

struct Neighbor {
	int num = 0;
	long long w = 0;

	Neighbor(int _num, long long _w) {
		num = _num;
		w = _w;
	}
};

using Graph = std::vector<std::vector<int>>;

std::pair<std::vector<std::vector<int>>, int> get_data(int N) {
	int L = 0;
	std::cin >> L;
	int floors = N;	
	Graph elevators(L);
	for (int i = 0; i < L; i++) {
		int K_i = 0;
		std::cin >> K_i;
		elevators[i] = std::vector<int>(K_i);
		for (int j = 0; j < K_i; j++) {
			std::cin >> elevators[i][j];
			floors = std::max(floors, elevators[i][j]);
			elevators[i][j]--;
		}
	}
	return std::make_pair(elevators, floors);
}

std::vector<Neighbor> get_neighbors(int v, std::vector<std::vector<int>> &elevators, int floors, int U, int D, int I, int J) {
	std::vector<Neighbor> neighbors;
	if (v > 0) {
		neighbors.emplace_back(v-1, D);
	}
	if (v < floors-1) {
		neighbors.emplace_back(v+1, U);
	}
	for (int i = 0; i < elevators.size(); i++) {
		auto it = binary_find(elevators[i].cbegin(), elevators[i].cend(), v);
		if (it != elevators[i].cend()) {
			int index = std::distance(elevators[i].cbegin(), it);
			for (int k = index+1; k < elevators[i].size(); k++)	{	
				neighbors.emplace_back(elevators[i][k], I+J);
			}
			for (int k = 0; k < index; k++) {
				neighbors.emplace_back(elevators[i][k], I+J);
			}
		}
	}
	return neighbors;
}

long long get_cost(std::vector<std::vector<int>> &elevators, int floors, int N, int U, int D, int I, int J) {
        std::vector<bool> used(floors);
        std::vector<long long> d(floors);

        std::set<std::pair<long long, int>> q;     

        for (int i = 0; i < floors; i++) {
                used[i] = false;
                d[i] = INF;
                q.insert(std::make_pair(d[i], i));
        }

        q.erase(std::make_pair(d[0], 0));
	d[0] = 0;
        q.insert(std::make_pair(d[0], 0));

        while (!q.empty()) {
                int next = (q.begin())->second;
                q.erase(q.begin());
                used[next] = true;
		std::vector<Neighbor> neighbors = get_neighbors(next, elevators, floors, U, D, I, J);
                for (auto neighbor : neighbors) {
                        if (!used[neighbor.num]) {
                                if (d[neighbor.num] > d[next] + neighbor.w) {
                                        q.erase(std::make_pair(d[neighbor.num], neighbor.num));
					d[neighbor.num] = d[next] + neighbor.w;
                                        q.insert(std::make_pair(d[neighbor.num], neighbor.num));
                                }
                        }
                }
	}
	return d[N];
}

int main() {
	std::ios::sync_with_stdio(false);
	int N = 0, U = 0, D = 0, I = 0, J = 0;
	std::cin >> N >> U >> D >> I >> J;
	std::pair<std::vector<std::vector<int>>, int> data = get_data(N);
	std::cout << get_cost(data.first, data.second, N-1, U, D, I, J) << std::endl;
	return 0;
}
