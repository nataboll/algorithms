#include <iostream>
#include <vector>

enum Color {
    WHITE,
    GRAY,
    BLACK,
};

int dfs_visit(std::vector<std::vector<int>> &g, int s, std::vector<Color> &color, int *counter_ptr) {
    (*counter_ptr)++;
    color[s] = GRAY;
    for (int i = 0; i < g[s].size(); i++) {
        if (color[g[s][i]] == WHITE) {
            dfs_visit(g, g[s][i], color, counter_ptr);
        }
    }
    color[s] = BLACK;
    return *counter_ptr;
}

int comp_size(std::vector<std::vector<int>> &g, int s) {
    std::vector<Color> color(g.size(), WHITE);
    int counter = 0;
    return dfs_visit(g, s, color, &counter);
}

int main() {
    int n = 0, s = 0;
    std::cin >> n >> s;
    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int edge = 0;
            std::cin >> edge;
            if (edge) {
                g[i].push_back(j);
            }
        }
    }
    
    std::cout << comp_size(g, s-1) << std::endl;
    return 0;
}
