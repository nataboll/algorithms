#include <iostream>
using namespace std;

enum Color {
	WHITE,
	GRAY,
	BLACK,
	RED
};

Color *status;

void dfs_visit(int **g, int s, int n);

bool dfs_check_tree(int **g, int n) {
	status = new Color[n];
	for (int s = 0; s < n; s++) {
		status[s] = WHITE;
	}
        dfs_visit(g, 0, n);
	bool connected = true;
        for (int i = 0; i < n; i++) {
		if (status[i] != BLACK) {
			connected = false; 
		}
	}
	delete [] status;
	return connected;
	
}

void dfs_visit(int **g, int s, int n) {
        status[s] = GRAY;
        for(int i = 0; i < n; i++) {
		if (g[s][i] == 1) {
			if (status[i] == WHITE) {
                        	dfs_visit(g, i, n);
			}
		}
        }
        status[s] = BLACK;
}

int main() {
	int n = 0;
	cin >> n;
	if (n < 0) {
		return 1;
	}

	int **g = new int*[n];
	int e_num = 0;
        for (int i = 0; i < n; i++) {
		g[i] = new int[n];
		for (int j = 0; j < n; j++) {
			cin >> g[i][j];
			if (g[i][j] == 1) e_num++;
		}
	}

	if (e_num % 2 != 0 || e_num/2 != n-1) {
		cout << "NO" << endl;
		return 0;
	}

	if (dfs_check_tree(g,n)){
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}

	for (int i = 0; i < n; i++){
		delete [] g[i];
	}

	delete [] g;

	return 0;
}
