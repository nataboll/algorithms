#include <iostream>
#include <set>
#include <vector>
#include <utility>

static const int MAX = 30001;

using Neighbor = std::pair<int, int>;
using Graph = std::vector<std::vector<Neighbor>>;

int get_mst_weight(const Graph &g) {
    std::vector<bool> used(g.size(), false);
    std::vector<int> key(g.size(), MAX);
    std::set<std::pair<int, int>> q;

    q.insert(std::make_pair(0, 0));
    key[0] = 0;
    int w = 0;

    while(!q.empty()) {
        int cur = (q.begin())->second;
        q.erase(q.begin());
        used[cur] = true;
        for (auto next : g[cur]) {
            if (!used[next.first] && (key[next.first] > next.second)) {
                q.erase(std::make_pair(key[next.first], next.first));
                int delta = 0;
                if (key[next.first] < MAX)
                    delta = key[next.first];
                w += (next.second - delta);
                key[next.first] = next.second;
                q.insert(std::make_pair(key[next.first], next.first));
            }
        }
    }
    
    return w;
}

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        int out = 0, in = 0, w = 0;
        std::cin >> out >> in >> w;
        g[out-1].push_back(std::make_pair(in-1, w));
        g[in-1].push_back(std::make_pair(out-1, w));
    }
    std::cout << get_mst_weight(g) << std::endl;
    return 0;
}

