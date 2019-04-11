#include <iostream>
#include <vector>

int MAX = 100000000;

using Graph = std::vector<std::vector<int>>;

Graph get_graph(int n) {
    Graph g(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int w = 0;
            std::cin >> w;
            if (w != -1)
                g[i][j] = w;
            else 
                g[i][j] = MAX;
        }
    }
    return g;
}

int get_d(Graph &g, int s, int f) {
    for (int i = 0; i < g.size(); i++)
        g[i][i] = 0;
    for (int k = 0; k < g.size(); k++) {
        for (int i = 0; i < g.size(); i++) {
            for (int j = 0; j < g.size(); j++) {
                if (g[i][j] > g[i][k] + g[k][j])
                    g[i][j] = g[i][k] + g[k][j];
            }
        }
    }
    return g[s][f];
}

int main() {
    int n = 0, s = 0, f = 0;
    std::cin >> n >> s >> f;
    Graph g = get_graph(n);
    int d = get_d(g, s-1, f-1);
    if (d < MAX)
        std::cout << d << std::endl;
    else
        std::cout << -1 << std::endl;
    return 0;
}
