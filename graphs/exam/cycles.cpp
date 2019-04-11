#include <iostream>
#include <vector>
#include <utility>
#include <list>

enum Color {
    WHITE,
    GRAY,
    BLACK,
};

using Graph = std::vector<std::vector<int>>;

bool dfs_visit(Graph &g, int s, std::vector<Color> &color, std::list<int> &cycle) {
    color[s] = GRAY;
    for (int i = 0; i < g[s].size(); i++) {
        if (color[g[s][i]] == GRAY) {
            cycle.push_front(g[s][i]);
            cycle.push_front(s);
            return true;
        } 
        if (color[g[s][i]] == WHITE) {
            if (dfs_visit(g, g[s][i], color, cycle)) {
                cycle.push_front(s);
                return true;
            }
        }
    }
    color[s] = BLACK;
    return false;
}

std::pair<bool, std::list<int>> get_cycle(Graph &g) {
    std::list<int> cycle;
    std::vector<Color> color(g.size(), WHITE);
    for (int i = 0; i < g.size(); i++) {
        if (color[i] == WHITE) {
            if (dfs_visit(g, i, color, cycle)) 
                return std::make_pair(true, cycle);
        }
    }
    return std::make_pair(false, cycle);
}

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    Graph g(n);

    for (int i = 0; i < m; i++) {
        int out = 0, in = 0;
        std::cin >> out >> in;
        g[out-1].push_back(in-1);
    }

    std::pair<bool, std::list<int>> res = get_cycle(g);

    if (res.first) {
        std::cout << "YES" << std::endl;
        int s_cycle = *res.second.rbegin();
        auto it = res.second.begin();
        while (*it != s_cycle)
            ++it;
        ++it;
        for (; it != res.second.end(); ++it) {
            std::cout << *it+1 << " ";
        }
    } else 
        std::cout << "NO";

    std::cout << std::endl;

    return 0;
}
