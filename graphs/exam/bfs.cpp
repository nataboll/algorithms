#include <iostream>
#include <vector>
#include <queue>

enum Color {
    WHITE,
    GRAY,
    BLACK,
};

int comp_size(std::vector<std::vector<int>> &g, int s) {
    int counter = 1;
    std::vector<Color> color(g.size(), WHITE);
    std::queue<int> q;
    color[s] = GRAY;
    q.push(s);
    while (!q.empty()) {
        int curr = q.front();
        color[curr] = BLACK;
        q.pop();
        for (int i = 0; i < g[curr].size(); i++) {
            if (color[g[curr][i]] == WHITE) {
                counter++;
                q.push(g[curr][i]);
                color[g[curr][i]] = GRAY;
            }
        }
    }
    return counter;
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
