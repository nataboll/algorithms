#include <iostream>
#include <vector>
#include <queue>
using namespace std;


enum Color {
	WHITE,
	GRAY,
	BLACK
};


bool dfs_visit(vector<vector<int>> &g, int s, Color *color);

bool no_cycles(vector<vector<int>> &g) {
	Color color[g.size()];
        for (int s = 0; s < g.size(); s++) {
                color[s] = WHITE;
        }
	for (int s = 0; s < g.size(); s++) {
        	if (!dfs_visit(g, s, color)) {
			return false;	
		}
	}
        return true;
}

bool dfs_visit(vector<vector<int>> &g, int s, Color *color) {
        color[s] = GRAY;
        for(int i = 0; i < g[s].size(); i++) {
                if (color[g[s][i]] == WHITE) {
			if (!dfs_visit(g, g[s][i], color)) {
				return false;
			}
                } else if (color[g[s][i]] == GRAY) {
			return false;
		}
        }
        color[s] = BLACK;
	return true;
}

void sort(vector<vector<int>> &g_r, vector<vector<int>> &g, vector<int> &result) {
	bool used[g_r.size()];
	for (int i = 0; i < g_r.size(); i++) {
		used[i] = false;
	}
	while (result.size() < g_r.size()) {
		for (int i = 0; i < g_r.size(); i++) {
			if (g_r[i].size() == 0 && !used[i]) {
				used[i] = true;
				result.push_back(i);
			
				for (int m = 0; m < g[i].size(); m++) {
					vector<int> to_add;
					vector<int> &real = g_r[g[i][m]];
					for (int l = 0; l < real.size(); l++) {
						if (real[l] != i) {
							to_add.push_back(real[l]);
						}
					}
					real = to_add;
				}
			}
		}
	}
}

int main() {
	int n, m = 0;
	cin >> n >> m;
	vector<vector<int>> g(n); // graph
	vector<vector<int>> g_r(n); // reversed graph: in-neighbors
	for (int i = 0; i < m; i++) {
		int in_ver, out_ver = 0;
		cin >> out_ver >> in_ver;
		g_r[--in_ver].push_back(--out_ver);
		g[out_ver].push_back(in_ver);
	}

	if (n == 1 && m >= 1) {
		cout << "No" << endl;
		return 0;
	}

	if (no_cycles(g)) {
		cout << "Yes" << endl;
		vector<int> result;
		sort(g_r, g, result);

		for (int i = 0; i < n; i++) {
			cout << ++result[i] << " ";
		}
		cout << endl;	
	} else {
		cout << "No" << endl;
	}

	return 0;
}
