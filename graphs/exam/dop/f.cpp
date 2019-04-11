#include <iostream>
#include <vector>
#include <utility>
#include <map>

struct Cell {
    int x;
    int y;

    Cell() = default;

    Cell(int x, int y) : x(x), y(y)
    {}
};

class DSU {
private:
    std::vector<int> p;
    std::vector<int> r;

public:
    DSU(int n) : p(n), r(n, 0) {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }

    int find_set(int x) {
        if (p[x] == x) return x;
        return p[x] = find_set(p[x]);
    }

    bool make_union(int x, int y) {
        x = find_set(x);
        y = find_set(y);
        if (x == y)
            return true;
        if (r[x] < r[y])
            std::swap(x, y);
        p[y] = x;
        if (r[x] == r[y])
            r[x]++;
        return false;
    }

};

class Compare {
public:
    bool operator() (const Cell &c1, const Cell &c2) const {
        return (c1.x != c2.x) ? (c1.x < c2.x) : (c1.y < c2.y);
    }
};

int main() {
    int m = 0;
    std::cin >> m;
    std::map<Cell, int, Compare> cells;
    int counter = 0;
    std::vector<std::pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        std::cin >> x1 >> y1 >> x2 >> y2;
        if (cells.find(Cell(x1, y1)) == cells.end()) {
            cells.insert(std::make_pair(Cell(x1, y1), counter));
            counter++;
        }
        if (cells.find(Cell(x2, y2)) == cells.end()) {
            cells.insert(std::make_pair(Cell(x2, y2), counter));
            counter++;
        }
        edges[i] = std::make_pair(cells[Cell(x1, y1)], cells[Cell(x2, y2)]);
    }
    DSU dsu(counter);
    for (int i = 0; i < m; i++) {
        auto &e = edges[i];
        if (dsu.make_union(e.first, e.second)) {
            std::cout << i+1 << std::endl;
            return 0;
        }   
    }
    std::cout << 0 << std::endl;
    return 0;
}

