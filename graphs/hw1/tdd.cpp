#include <iostream>
#include <queue>
#include <vector>
using namespace std;

enum Color {
	WHITE,
	GRAY,
	BLACK,
};

bool bfs_paint(const vector<vector<int>> &g) {
	vector<int> clas(g.size());
	Color status[g.size()];

	for (int s = 0; s < g.size(); s++){
		status[s] = WHITE;
		clas[s] = 2; // another one
	}

        for (int s = 0; s < g.size(); s++){
                if (status[s] == WHITE){
			clas[s] = 0;
                        queue<int> q;
                        q.push(s);
                        status[s] = GRAY;
                        while(!q.empty()){
                                int u = q.front();
                                status[u] = BLACK;
                                q.pop();
                                const vector<int> &to_add = g.at(u);
                                for (int i = 0; i < to_add.size(); i++){
                                        if (status[to_add[i]] == WHITE){
                                                q.push(to_add[i]);
                                                status[to_add[i]] = GRAY;
						clas[to_add[i]] = 1 - clas[u];
                                        } else {
						if (clas[to_add[i]] == clas[u]) {
							return false;
						}
					}
                                }
                        }
                }
        }
	return true;
}

int main() {
	int n, m = 0;
        cin >> n >> m;
	
	vector<vector<int>> g(n);
        for (int i = 0; i < m; i++) {
                int out_ver = 0, in_ver = 0;
                cin >> out_ver >> in_ver;
		if (in_ver == out_ver) {
			cout << "NO" << endl;
			return 0;
		}
		g[--out_ver].push_back(--in_ver);
		g[in_ver].push_back(out_ver);
        }

	bool b = bfs_paint(g);
	if (b)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	return 0;
}
