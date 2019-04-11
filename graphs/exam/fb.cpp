#include <iostream>
#include <vector>

struct Edge {
    int out;
    int in;
    int w;

    Edge() = default;

    Edge(int _out, int _in, int _w) : out(_out), in(_in), w(_w)
    {}
};

using Edges = std::vector<Edge>;

Edges get_edges() {
    int m = 0;
    std::cin >> m;
    Edges edges(m);
    for (int i = 0; i < m; i++) {
        int out = 0, in = 0, w = 0;
        std::cin >> out >> in >> w;
        edges[i] = Edge(out-1, in-1, w);
    }
    return edges;
}

std::vector<int> get_d(Edges &g, int n) {
    std::vector<int> d(n, 30000);
    d[0] = 0;
    for (int i = 0; i < n-1; i++) {
        for (auto e : g) {
            if (d[e.in] > d[e.out] + e.w && d[e.out] < 30000) {
                d[e.in] = d[e.out] + e.w;
            }
        }
    }
    return d;
}

int main() {
    int n = 0;
    std::cin >> n;
    Edges g = get_edges();
    std::vector<int> d = get_d(g, n);
    for (int i = 0; i < d.size(); i++) {
        std::cout << d[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
