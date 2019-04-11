#include <iostream>
#include <queue>
#include <vector>
#include <cassert>
using namespace std;

enum Color {
	WHITE,
	GRAY,
	BLACK,
};

int main() {
	int n, s = 0;
	cin >> n >> s;
	s--;
	if ((s < 0) || (n < 0) || (s >= n)) {
		return 1;
	}
	else if (n == 0) {
		cout << 0 << std::endl;
		return 0;
	}

	int **g = new int*[n];
        for (int i = 0; i < n; i++) {
		g[i] = new int[n];
		for (int j = 0; j < n; j++) {
			cin >> g[i][j];
		}
	}


	Color status[n];

        for (int u = 0; u < n; u++) {
                status[u] = WHITE;
        }

        queue<int> q;
        q.push(s);
        status[s] = GRAY;
        while(!q.empty()) {
                int i = q.front();
                status[i] = BLACK;
                q.pop();
                for (int j = 0; j < n; j++) {
                        if (status[j] == WHITE && g[i][j] == 1) {
                                q.push(j);
                                status[j] = GRAY;
                        }
                }
        }

        int neighbors = 0;
        for (int i = 0; i < n; i++) {
                assert(status[i] != GRAY);
                if (status[i] == BLACK) {
                        neighbors++;
                }
        }

        cout << neighbors << endl;

	for (int i = 0; i < n; i++){
		delete [] g[i];
	}

	delete [] g;

	return 0;
}
