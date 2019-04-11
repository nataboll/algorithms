#include <iostream>
#include <queue>
using namespace std;
 
enum Color {
    WHITE,
    GRAY,
    BLACK,
};
 
 
vector<int> bfs_back_way(vector<vector<int>> &g, int start, int finish) {
        Color status[g.size()];
 
    vector<int> prev(g.size());
 
        for (int i = 0; i < g.size(); i++) {
                status[i] = WHITE;
        prev[i] = -1;
        }
 
    queue<int> q;
        q.push(start);
        status[start] = GRAY;
        while(!q.empty()) {
                int current = q.front();
                status[current] = BLACK;
                q.pop();
        if (current == finish) {
            break;
        }
                for (int neighbor = 0; neighbor < g.size(); neighbor++) {
                        if (status[neighbor] == WHITE && g[current][neighbor] == 1) {
                                q.push(neighbor);
                                status[neighbor] = GRAY;
                		prev[neighbor] = current;
                        }
                }
        }
 
    int current = finish;
    vector<int> back_way;
    back_way.push_back(current);
    if (prev[current] == -1) {
        vector<int> vect;
        vect.push_back(-1);
        return vect;
    }
    while (current != start) {
        current = prev[current];
        back_way.push_back(current);
    }
 
    return back_way;
}
 
int main() {
    int n = 0, m = 0;
    cin >> n >> m;
    int start, finish = 0;
    cin >> start >> finish;
    start --;
    finish --;

    vector<vector<int>> g(n);

    for (int i = 0; i < n; i++) {
	g[i] = std::vector<int>(n);
	for (int j = 0; j < n; j++) {
		g[i][j] = 0;
	}
    }

    for (int i = 0; i < m; i ++) {
        int out, in = 0;
	cin >> out >> in;
        g[in-1][out-1] = g[out-1][in-1] = 1;
    }
 
    vector<int> back_way = bfs_back_way(g, start, finish);
 
    if (back_way[0] == -1) {
        cout << -1 << endl;
        return 0;
    }
    cout << back_way.size() - 1 << endl;
    for (int i = back_way.size()-1; i >= 0; i --) {
        cout << ++back_way[i] << " ";
    }
    cout << endl;
 
    return 0;
}
