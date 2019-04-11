#include <iostream>
#include <vector>
#include <list>

int MAX = 100000000;

struct Edge {
    int out;
    int in;
    int w;

    Edge() = default;

    Edge(int _out, int _in, int _w) : out(_out), in(_in), w(_w)
    {}
};

using Edges = std::list<Edge>;

Edges get_edges(int m) {
    Edges g;
    for (int i = 0 ; i < m; i++) {
        int out, in, w;
        std::cin >> out >> in >> w;
        g.push_back(Edge(in-1, out-1, w)); // transposed graph
    }
    return g;
}

int get_d(Edges &g, int n, int k, int s, int f) {
    std::vector<int> d(n, MAX), steps(n, 101);
    d[s] = 0;
    steps[s] = 0;
    for (int i = 0; i < k; i++) {
        for (auto e : g) {
            if (d[e.in] > d[e.out] + e.w && d[e.out] < MAX && steps[e.out] <= i) {
                d[e.in] = d[e.out] + e.w;
                steps[e.in] = steps[e.out] + 1;
            }
        }
    }
    if (d[f] < MAX) return d[f];
    return -1;
}

int main() {
    int n, m, k, s, f;
    std::cin >> n >> m >> k >> s >> f;
    Edges g = get_edges(m);
    std::cout << get_d(g, n, k, f-1, s-1) << std::endl;
    return 0;
}
