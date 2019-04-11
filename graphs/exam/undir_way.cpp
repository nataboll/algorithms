#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <list>

using Graph = std::vector<std::vector<int>>;

enum Color {
    WHITE,
    GRAY,
    BLACK,
};

Graph get_graph() {
    int n = 0;
    std::cin >> n;
    Graph g(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int edge = 0;
            std::cin >> edge;
            if (edge)
                g[i].push_back(j);
        }
    }
    return g;
}

std::pair<bool, std::list<int>> get_path(Graph &g, int s, int f) {
    std::vector<Color> color(g.size(), WHITE);
    std::queue<int> q;
    q.push(s);
    color[s] = GRAY;
    std::vector<int> p(g.size(), -1);
    while(!q.empty()) {
        int curr = q.front();
        q.pop();
        color[curr] = BLACK;
        for (int i = 0; i < g[curr].size(); i++) {
            if (g[curr][i] == f) {
                p[f] = curr;
                std::list<int> path;
                int curr = f;
                while (curr != s) {
                    path.push_front(curr+1);
                    curr = p[curr];
                }        
                path.push_front(s+1);
                return std::make_pair(true, path);
            }
            if (color[g[curr][i]] == WHITE) {
                q.push(g[curr][i]);
                color[g[curr][i]] = GRAY;
                p[g[curr][i]] = curr;
            }
        }
    }
    return std::make_pair(false, std::list<int>());
}

int main() {
    Graph g = get_graph();
    int s = 0, f = 0;
    std::cin >> s >> f;
    if (s == f) {
        std::cout << 0 << std::endl;
        return 0;
    }
    std::pair<bool, std::list<int>> res = get_path(g, s-1, f-1);
    if (res.first) {
        std::cout << res.second.size()-1 << std::endl;    
        for (auto it = res.second.begin(); it != res.second.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    } else 
        std::cout << "-1" << std::endl;
    return 0;
}
