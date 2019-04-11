#include <iostream>
#include <vector>
#include <utility>
#include <queue>

enum Color {
    WHITE,
    GRAY,
    BLACK,
};

using Graph = std::vector<std::vector<int>>;

std::pair<bool, std::vector<int>> get_teams(Graph &g, int k) {
    std::vector<Color> color(g.size(), WHITE);
    std::vector<int> group(g.size(), 0);
    std::queue<int> q;
    for (int s = 0; s < g.size(); s++) {
        if (color[s] == WHITE) {
            q.push(s);
            color[s] = GRAY;
            group[s] = 1;
            while (!q.empty()) {
                int cur = q.front();
                q.pop();
                color[cur] = BLACK;
                for (int next : g[cur]) {
                    if (color[next] == WHITE) {
                        q.push(next);
                        color[next] = GRAY;
                        group[next] = 3 - group[cur];
                    } else if (color[next] == GRAY && group[next] == group[cur]) {
                        group[cur] = 3;
                        break;
                    }
                }
            }
        }
    }
    int counter_1 = 0, counter_2 = 0;
    for (int gr : group) {
        if (gr == 1)
            counter_1++;
        else if (gr == 2)
            counter_2++;
    }
    int gr = (counter_1 >= counter_2) ? 1 : 2;
    int counter = std::max(counter_1, counter_2);
    if (counter < k) 
        return std::make_pair(false, std::vector<int>());
    std::vector<int> teams;
    for (int i = 0; i < g.size(); i++) {
        if (group[i] == gr) 
            teams.push_back(i);
    }
    return std::make_pair(true, teams);
}

int main() {
    int n = 0;
    std::cin >> n;
    Graph g(n);
    for (int i = 0; i < n; i++) {
        int out = 0, in = 0;
        std::cin >> out >> in;
        g[out-1].push_back(in-1);
        g[in-1].push_back(out-1);
    }
    int k = 0;
    std::cin >> k;
    std::pair<bool, std::vector<int>> res = get_teams(g, k);
    if (res.first) {
        for (int i = 0; i < k; i++)
            std::cout << res.second[i]+1 << " ";
        std::cout << std::endl;
    } else
        std::cout << 0 << std::endl;
    return 0;
}
