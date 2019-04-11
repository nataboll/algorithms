#include <iostream>
#include <vector>
#include <queue>

using Table = std::vector<std::vector<int>>;

enum Color {
    WHITE,
    GRAY,
    BLACK,
};

struct Vertex {
    int x = 0;
    int y = 0;

    Vertex(int _x, int _y) : x(_x), y(_y)
    {}

    Vertex() = default;
};

Table get_table(const std::vector<Vertex> &starts, int n, int m) {
    std::vector<Vertex> dv(4);
    dv[0] = Vertex(-1, 0);
    dv[1] = Vertex(0, 1);
    dv[2] = Vertex(1, 0);
    dv[3] = Vertex(0, -1);
    std::vector<std::vector<Color>> color(n, std::vector<Color>(m, WHITE));
    std::queue<Vertex> q;
    Table t(n, std::vector<int>(m, 2000));
    for (auto v : starts) {
        q.push(v);
        color[v.x][v.y] = GRAY;
        t[v.x][v.y] = 0;
    }
    while (!q.empty()) {
        Vertex curr = q.front();
        q.pop();
        color[curr.x][curr.y] = BLACK;
        for (auto shift : dv) {
            int x = curr.x + shift.x;
            int y = curr.y + shift.y;
            if (x < n && x >= 0 && y < m && y >= 0 && color[x][y] == WHITE) {
                q.push(Vertex(x, y));
                color[x][y] = GRAY;
                if (t[x][y] > t[curr.x][curr.y] + 1) {
                    t[x][y] = t[curr.x][curr.y] + 1;
                }
            }
        }
    }
    return t;
}

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<Vertex> starts;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int start = 0;
            std::cin >> start;
            if (start) 
                starts.push_back(Vertex(i, j));
        }
    }
    Table t = get_table(starts, n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << t[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
