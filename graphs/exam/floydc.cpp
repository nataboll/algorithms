#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

Graph get_graph() {
    int n = 0; 
    std::cin >> n;
    Graph g(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> g[i][j];
        }
    }
    return g;
}

int get_min(Graph &g) {
    for (int k = 0; k < g.size(); k++) {
        for (int i = 0; i < g.size(); i++) {
            for (int j = 0; j < g.size(); j++) {
                if (g[i][j] > g[i][k] + g[k][j])
                    g[i][j] = g[i][k] + g[k][j];
            }
        }
    }
    for (int i = 0; i < g.size(); i++) {
        if (g[i][i] < 0)
            return -1;
    }
    int min = g[0][1];
    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g.size(); j++) {
            if (i != j && g[i][j] < min)
                min = g[i][j];
        }
    }
    return min;
}

int main() {
    Graph g = get_graph();
    std::cout << get_min(g) << std::endl;
    return 0;
}
