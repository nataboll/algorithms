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

bool dfs_visit(Graph &g, int s, std::vector<Color> &color, int prev = -1) {
    color[s] = GRAY;
    for (int i = 0; i < g[s].size(); i++) {
        if (color[g[s][i]] == GRAY && g[s][i] != prev)
            return true;
        else if (color[g[s][i]] == WHITE) {
            if (dfs_visit(g, g[s][i], color, s))
                return true;
        }
    }
    color[s] = BLACK;
    return false;
}

std::pair<bool, std::list<int>> get_cycle(Graph &g) {
    std::list<int> cycle;
    bool is_cycle = false;
    std::vector<Color> color(g.size(), WHITE);
    is_cycle = dfs_visit(g, 0, color);

    if (!is_cycle) {
        for (int i = 0; i < color.size(); i++) {
            if (color[i] != BLACK) {
                is_cycle = true;
                break;
            }
        }
    }

    return std::make_pair(is_cycle, std::list<int>(g.size(), 0));
}

int main() {
    int n = 0, m = 0;
    std::cin >> n;// >> m;
    Graph g(n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int edge = 0;
            std::cin >> edge;
            if (edge) {
                m++;
                g[i].push_back(j);
            }
        }
    }
   
/*    for (int i = 0; i < m; i++) {
        int out = 0, in = 0;
        std::cin >> out >> in;
        g[out-1].push_back(in-1);
    } */

    std::pair<bool, std::list<int>> res = get_cycle(g);

    if (res.first) {
        std::cout << "NO" << std::endl;
/*        for (auto it = res.second.begin(); it != res.second.end(); ++it) {
            std::cout << *it+1 << " ";
        } */
    } else 
        std::cout << "YES";

    std::cout << std::endl;

    return 0;
}
