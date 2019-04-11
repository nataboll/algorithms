#include <iostream>
#include <vector>
#include <list>
#include <utility>

using Graph = std::vector<std::vector<int>>;

enum Color {
    WHITE,
    GRAY,
    BLACK,
};

void visit(int i, Graph &g, std::vector<Color> &color, std::list<int> &order) {
   color[i] = GRAY;
   for (int j = 0; j < g[i].size(); j++) {
        if (color[g[i][j]] == WHITE) {
            visit(g[i][j], g, color, order);
        }
    }
    color[i] = BLACK;
    order.push_front(i);
}

std::list<int> get_order(Graph &g) {
    std::vector<Color> color(g.size(), WHITE);
    std::list<int> order;
    for (int i = 0; i < g.size(); i++) {
        if (color[i] == WHITE) {
            visit(i, g, color, order);
        }
    }
    return order;
}

void visit(int i, Graph &g, std::vector<Color> &color, std::vector<int> &components, int counter) {
    color[i] = GRAY;
    for (int j = 0; j < g[i].size(); j++) {
        if (color[g[i][j]] == WHITE) {
            visit(g[i][j], g, color, components, counter);
        }
    }
    components[i] = counter;
    color[i] = BLACK;
}

std::pair<int, std::vector<int>> condence(Graph &g, Graph &g_t) {
    std::list<int> order = get_order(g);
    std::vector<int> components(g.size());
    int counter = 0;
    std::vector<Color> color(g.size(), WHITE);
    for (auto i = order.begin(); i != order.end(); ++i) {
        if (color[*i] == WHITE) {
            counter++;
            visit(*i, g_t, color, components, counter);
        }
    }
    return std::make_pair(counter, components);
}

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    Graph g(n), g_t(n);
    for (int i = 0; i < m; i++) {
        int out = 0, in = 0;
        std::cin >> out >> in;
        g[out-1].push_back(in-1);
        g_t[in-1].push_back(out-1);
    }

    std::pair<int, std::vector<int>> res = condence(g, g_t);
    
    std::cout << res.first << std::endl;
    for (int i = 0; i < res.second.size(); i++) {
        std::cout << res.second[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
