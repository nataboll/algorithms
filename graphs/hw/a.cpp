#include <iostream>
#include <queue>
#include <vector>
using namespace std;
 
enum Color {
    WHITE,
    GRAY,
    BLACK,
};
 
void bfs_comp(const vector<vector<int>> &g) {
    const int n = g.size();
    Color status[n];
 
    vector<vector<int>> components;
 
    for (int s = 0; s < n; s++){
        status[s] = WHITE;
    }
 
        for (int s = 0; s < n; s++){
                if (status[s] == WHITE){
                        queue<int> q;
            vector<int> to_add;
                        q.push(s);
                        status[s] = GRAY;
                        while(!q.empty()){
                                int u = q.front();
                to_add.push_back(u);
                                status[u] = BLACK;
                                q.pop();
                                const vector<int> &to_add = g.at(u);
                                for (int i = 0; i < to_add.size(); i++){
                                        if (status[to_add[i]] == WHITE){
                                                q.push(to_add[i]);
                                                status[to_add[i]] = GRAY;
                                        }
                                }
                        }
            components.push_back(to_add);
                }
        }
 
    cout << components.size() << endl;
    for (int i = 0; i < components.size(); i++) {
        cout << components.at(i).size() << endl;
        for (int j = 0; j < components.at(i).size(); j++){
            cout << ++components.at(i).at(j) << " ";
        }
        cout << endl;
    }
}
 
int main() {
    int n, m = 0;
        cin >> n >> m;
    vector<vector<int>> g(n);
        for (int i = 0; i < m; i++) {
                int out_ver = 0, in_ver = 0;
                cin >> out_ver >> in_ver;
        if (out_ver <= 0 || in_ver <= 0 || out_ver > n || in_ver > n) return 1;
        g[--out_ver].push_back(--in_ver);
        g[in_ver].push_back(out_ver);
        }
 
    bfs_comp(g);
 
    return 0;
}
