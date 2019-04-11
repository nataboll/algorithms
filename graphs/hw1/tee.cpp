#include <iostream>
#include <stack>
using namespace std;

enum Color {
	WHITE,
	GRAY,
	BLACK,
};

struct Vertex {
	int i = 0;
	int j = 0;
};

int main() {
	int m, n = 0;
	cin >> m >> n; 	// field size
	char **g = new char*[m];
	Color status[m][n];
	for (int i = 0; i < m; i++) {
		g[i] = new char[n];
		cin >> g[i];
		for (int j = 0; j < n; j++) {
			status[i][j] = WHITE;
		}
	}

	int components = 0;
	stack<Vertex> dfs_stack;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (g[i][j] == '#') {
				if (status[i][j] == WHITE) {	// for 1 component
					status[i][j] = GRAY;
					components++;
					Vertex s;
					s.i = i;
					s.j = j;
					dfs_stack.push(s);
					
					while (!dfs_stack.empty()) {
						Vertex v = dfs_stack.top();
						dfs_stack.pop();
						if (v.i > 0 && g[v.i-1][v.j] == '#' && status[v.i-1][v.j] == WHITE) {
							Vertex u;
							u.i = v.i - 1;
							u.j = v.j;
							dfs_stack.push(u);
							status[v.i-1][v.j] = BLACK;
						}
						if (v.j > 0 && g[v.i][v.j-1] == '#' && status[v.i][v.j-1] == WHITE) {
							Vertex u;
							u.i = v.i;
							u.j = v.j - 1;
							dfs_stack.push(u);
							status[v.i][v.j-1] = BLACK;
						}
						if (v.i < m - 1 && g[v.i+1][v.j] == '#' && status[v.i+1][v.j] == WHITE) {
							Vertex u;
							u.i = v.i + 1;
							u.j = v.j;
							dfs_stack.push(u);
							status[v.i+1][v.j] = BLACK;
						}
						if (v.j < n - 1 && g[v.i][v.j+1] == '#' && status[v.i][v.j+1] == WHITE) {
							Vertex u;
							u.i = v.i;
							u.j = v.j + 1;
							dfs_stack.push(u);
							status[v.i][v.j+1] = BLACK;
						}
					}	
				}
			}
		}
	}
	for (int i = 0; i < m; i ++) {
		delete [] g[i];
	}
	delete [] g;
	cout << components << endl;
	return 0;
}
