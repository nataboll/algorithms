#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
    int out;
    int in;
    int w;

    Edge(int _out, int _in, int _w) : out(_out), in(_in), w(_w)
    {}
};

using Edges = std::vector<Edge>;

Edges get_edges() {
    int m = 0;
    std::cin >> m;
    Edges edges;
    for (int i = 0; i < m; i++) {
        int out = 0, in = 0, w = 0;
        std::cin >> out >> in >> w;
        edges.push_back(Edge(out, in, w));
    }
    return edges;
}

class compare {
public:
    bool operator() (const Edge &e1, const Edge &e2) const {
        return e1.w < e2.w;
    }
};

class DSU {
private:
    std::vector<int> p, w;

public:
    DSU(int n) : w(n, 0) 
    {
        p = std::vector<int>(n);
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }

    int find_set(int x) {
        if (p[x] == x) return x;
        return p[x] = find_set(p[x]);
    }

    void make_union(int x, int y, int _w) {
        x = find_set(x);
        y = find_set(y);
        if (x != y) {
            if (w[x] > w[y])
                std::swap(x, y);
            p[x] = y;
            w[y] = w[y] + w[x] + _w;
        }
    }

    int get_w(int x) {
        return w[find_set(x)];
    }
};

int main() {
    int n = 0;
    std::cin >> n;
    Edges edges = get_edges();
    std::sort(edges.begin(), edges.end(), compare());
    DSU dsu(n);
    for (int i = 0; i < edges.size(); i++) {
        dsu.make_union(edges[i].out-1, edges[i].in-1, edges[i].w);
    }
    std::cout << dsu.get_w(0) << std::endl;
    return 0;
}

