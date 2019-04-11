#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
 
struct Edge {
    int u;
    int v;
    int w;
};
 
class DSU {
private:
    std::vector<int> parent;
    std::vector<int> w;
 
public:
    DSU(int n)
        : parent(n)
        , w(n)
    {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            w[i] = 0;
        }
    }
 
    int find_set(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find_set(parent[x]);
    }
 
    void make_union(int x, int y, int _w) {
        x = find_set(x);
        y = find_set(y);
        if (w[x] > w[y]) {
            int tmp = x;
            x = y;
            y = tmp;
        }
        parent[x] = y;
        w[y] += (w[x] + _w);
    }
 
    std::vector<int> get_parents() const {
        return parent;
    }
 
    std::vector<int> get_weights() const {
        return w;
    }
};
 
class compare {
public:
    bool operator() (Edge &e1, Edge &e2) {
        return e1.w < e2.w;
    }
};
 
std::vector<Edge> get_graph(int n) {
        int m = 0;
        std::cin >> m;
        std::vector<Edge> g(m);
       
        for (int i = 0; i < m; i++) {
                int out = 0, in = 0, w = 0;
                std::cin >> out >> in >> w;
                g[i] = Edge{out-1, in-1, w};
        }
        return g;
}
 
int get_mst_weight(std::vector<Edge> &g, int n) {
    DSU dsu(n);
    int w = 0;
    std::sort(g.begin(), g.end(), compare());
    for (int i = 0; i < g.size(); i++) {
        if (dsu.find_set(g[i].u) != dsu.find_set(g[i].v)) {
                    dsu.make_union(g[i].u, g[i].v, g[i].w);
                    w += g[i].w;
                }
    }
    return w;
}
 
int main() {
    int n = 0;
    std::cin >> n;
    std::vector<Edge> g = get_graph(n); // get topology
    int w = get_mst_weight(g, n);
    std::cout << w << std::endl;
    return 0;
}
