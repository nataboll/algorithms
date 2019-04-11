#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum Color {
	WHITE,
	GRAY,
	BLACK,
};

struct Cell {
	int i;
	int j;
};


void bfs_way(vector<vector<int>> &table, vector<vector<int>> &new_table) {
	vector<Cell> shift(4);

	shift[0] = {-1, 0};
	shift[1] = {0, 1};
	shift[2] = {1, 0};
	shift[3] = {0, -1};
	
	vector<vector<Color>> color(table.size());
	vector<Cell> starts;
	int n = table.size();
	int m = 0;
	for (int i = 0; i < n; i ++) {
		m = table[i].size();
		for (int j = 0; j < m; j ++) {
			color[i].push_back(WHITE);
			if (table[i][j] == 1) {
				Cell s{i, j};
                                starts.push_back(s);
                        }
			new_table[i][j] = 5000;
		}
	}

/*	cout << "starts: ";
	for (int i = 0; i < starts.size(); i ++) {
		cout << starts[i].i << starts[i].j << " ";
	}
	cout << endl; */

	for (int s = 0; s < starts.size(); s ++) {
		Cell start = starts[s];
		queue<Cell> q;
		q.push(start);	// contains 1
		color[start.i][start.j] = GRAY;
		new_table[start.i][start.j] = 0;
		while(!q.empty()) {
			Cell current = q.front();
			color[current.i][current.j] = BLACK;
			q.pop();
//			cout << current.i << current.j << endl;
			for (int k = 0; k < 4; k ++) {
				if ((current.i + shift[k].i >= 0) && (current.i + shift[k].i < n) && (current.j + shift[k].j < m) && (current.j + shift[k].j >= 0)) {
					if (color[current.i + shift[k].i][current.j + shift[k].j] == WHITE) {
						Cell neighbor{current.i + shift[k].i, current.j + shift[k].j};
						if (table[neighbor.i][neighbor.j] == 1) {
							new_table[neighbor.i][neighbor.j] = 0;
						} else if (new_table[current.i][current.j] + 1 < new_table[neighbor.i][neighbor.j]) {
							new_table[neighbor.i][neighbor.j] = new_table[current.i][current.j] + 1;
						}
						q.push(neighbor);
						color[neighbor.i][neighbor.j] = GRAY;
					} 
				}
			} 
		}
		for (int i = 0; i < n; i ++) {
                	for (int j = 0; j < m; j ++) {
                        color[i][j] = WHITE;
                	}
        	}
	}
}

int main() {
	int n, m = 0;
	cin >> n >> m;
	vector<vector<int>> table(n);
	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < m; j ++) {
			int value;
			cin >> value;
			table[i].push_back(value);
		}
	}

	vector<vector<int>> new_table = table;
	bfs_way(table, new_table);

	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < m; j ++) {
			cout << new_table[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
