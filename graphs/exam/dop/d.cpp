#include <iostream>
#include <vector>
#include <set>
#include <utility>

static const int INF = 1000000000;

struct Route {
    int b;
    int c;
    int d;

    Route() = default;

    Route(int b, int c, int d) : b(b), c(c), d(d)
    {}
};

using Table = std::vector<std::vector<Route>>;

int get_time(const Table &T, const std::vector<int> &s) {
    int timer = 0;

    for (int i = 0; i < s.size()-1; i++) {
        std::vector<bool> used(T.size(), false);
        std::vector<int> d(T.size(), INF);
        std::set<std::pair<int, int>> q;
        d[s[i]] = timer;
        q.insert(std::make_pair(d[s[i]], s[i]));

        while (!q.empty()) {
            int cur = q.begin()->second;
            q.erase(q.begin());
            used[cur] = true;
            for (auto next : T[cur]) {
                int delta = (d[cur] % next.c == 0) ? d[cur] : (d[cur]/next.c + 1) * next.c;
                int time = next.d + delta;
                if (!used[next.b] && time < d[next.b]) {
                    q.erase(std::make_pair(d[next.b], next.b));
                    d[next.b] = time;
                    q.insert(std::make_pair(d[next.b], next.b));
                }
            }
        }

        timer = d[s[i+1]];
    }
    return (timer < INF) ? timer : -1;
}

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    Table g(n);
    for (int i = 0; i < m; i++) {
        int a = 0, b = 0, c = 0, d = 0;
        std::cin >> a >> b >> c >> d;
        g[a-1].push_back(Route(b-1, c, d));
    }
    int k = 0;
    std::cin >> k;
    std::vector<int> s(k);
    for (int i = 0; i < k; i++) {
        std::cin >> s[i];
        s[i]--;
    }
    std::cout << get_time(g, s) << std::endl;
    return 0;
}
