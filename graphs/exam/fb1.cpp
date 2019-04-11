#include <iostream>
#include <vector>
#include <list>

int MAX = 10000000;

struct Edge {
    int out;
    int in;
    int w;

    Edge() = default;

    Edge(int _out, int _in, int _w) : out(_out), in(_in), w(_w)
    {}
};

using Edges = std::list<Edge>;

Edges get_edges(int n) {
    Edges e;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int edge;
            std::cin >> edge;
            if (edge != 100000) {
                e.emplace_back(i, j, edge);
            }
        }
    }
    return e;
}

std::pair<bool, std::list<int>> get_cycle(Edges &g, int n) {
    std::vector<int> d(n, MAX), p(n, -1);
    std::vector<bool> used(n, false);
    int x = -1;
    for (int k = 0; k < n; k++) {
        if (!used[k]) {
            d[k] = 0;
            used[k] = true;
            for (int i = 0; i < n-1; i++) {
                for (auto e : g) {
                    if (d[e.in] > d[e.out] + e.w && d[e.out] < MAX) {
                        d[e.in] = d[e.out] + e.w;
                        p[e.in] = e.out;
                        used[e.in] = true;
                    }
                }
            }
            for (auto e : g) {
                if (d[e.in] > d[e.out] + e.w && d[e.out] < MAX) {
                    x = e.in;
                    break;
                }
            }
            if (x != -1)
                break;
        }
    }
    if (x == -1)
        return std::make_pair(false, std::list<int>());
    for (int i = 0; i < n; i++) 
        x = p[x];
    std::list<int> c;
    int last = x;
    c.push_front(last+1);
    x = p[x];
    while (x != last) {
        c.push_front(x+1);
        x = p[x];
    }
    c.push_front(x+1);
    return std::make_pair(true, c);
}

int main() {
    int n = 0;
    std::cin >> n;
    if (n == 1) {
        int w = 0;
        std::cin >> w;
        if (w < 0) {
            std::cout << "YES" << std::endl << "2" << std::endl << "1 1" << std::endl;
            return 0;
        }
    }
    Edges g = get_edges(n);
    std::pair<bool, std::list<int>> res = get_cycle(g, n);
    if (res.first) {
        std::cout << "YES" << std::endl;
        std::cout << res.second.size() << std::endl;
        for (auto it = res.second.begin(); it != res.second.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    } else
        std::cout << "NO" << std::endl;
    return 0;
}

