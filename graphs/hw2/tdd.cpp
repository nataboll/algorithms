#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum Color {
	WHITE,
	GRAY,
	BLACK,
};

struct Vertex {
	int x;
	int y;
};

vector<Vertex> bfs_back_way(Vertex *s, Vertex *f, int n) {
	vector<Vertex> dv(8);
	Vertex start{--(*s).x, --(*s).y};
	Vertex finish{--(*f).x, --(*f).y};

	dv[0].x = -1;
	dv[0].y = -2;

	dv[1].x = -2;
	dv[1].y = -1;

	dv[2].x = -2;
	dv[2].y = 1;

	dv[3].x = -1;
	dv[3].y = 2;

	dv[4].x = 1;
	dv[4].y = 2;

	dv[5].x = 2;
	dv[5].y = 1;

	dv[6].x = 2;
	dv[6].y = -1;

	dv[7].x = 1;
	dv[7].y = -2;

	Vertex **prev = new Vertex*[n];
	Color **color = new Color*[n];
	for (int i = 0; i < n; i ++) {
		prev[i] = new Vertex[n];
		color[i] = new Color[n];
		for (int j = 0; j < n; j ++) {
			color[i][j] = WHITE;
		}
	}

	queue<Vertex> q;
	q.push(start);
	color[start.x][start.y] = GRAY;
	while(!q.empty()) {
		Vertex current = q.front();
                color[current.x][current.y] = BLACK;
                q.pop();
                if ((current.x == finish.x) && (current.y == finish.y)) {
                        break;
                }
                for (int i = 0; i < 8; i ++) {
			if ((current.x + dv[i].x < n) && (current.x + dv[i].x >= 0) && (current.y + dv[i].y < n) && (current.y + dv[i].y >= 0)) {
				if (color[current.x + dv[i].x][current.y + dv[i].y] == WHITE) {
                        		Vertex neighbor{current.x + dv[i].x, current.y + dv[i].y};
					q.push(neighbor);
                                	color[neighbor.x][neighbor.y] = GRAY;
                                	prev[neighbor.x][neighbor.y] = current;
				}
			}
		}
        }	

        Vertex current = finish;
        vector<Vertex> back_way;
        back_way.push_back(current);

        while (!(current.x == start.x && current.y == start.y)) {
                current = prev[current.x][current.y];
                back_way.push_back(current);
        }	

	for (int i = 0; i < n; i ++) {
		delete [] prev[i];
		delete [] color[i];
	}
	delete [] prev;
	delete [] color;

	return back_way;
}

int main() {
	int n, x1, x2, y1, y2 = 0;
	n = 8;

        char x_str[2];
        int y[2];
        cin >> x_str[0] >> y[0] >> x_str[1] >> y[1];
        int x[2];
        for (int i = 0; i < 2; i ++) {
                switch(x_str[i]) {
                        case 'a': x[i] = 1; break;
                        case 'b': x[i] = 2; break;
                        case 'c': x[i] = 3; break;
                        case 'd': x[i] = 4; break;
                        case 'e': x[i] = 5; break;
                        case 'f': x[i] = 6; break;
                        case 'g': x[i] = 7; break;
                        case 'h': x[i] = 8; break;
                }
        }

	Vertex start{x[0], y[0]};
	Vertex finish{x[1], y[1]};
	vector<Vertex> back_way = bfs_back_way(&start, &finish, n);
	if ((back_way.size() - 1) % 2 == 1) {
		cout << -1 << endl;
	} else {
		cout << (back_way.size() - 1) / 2 << endl;
	}

	return 0;
}
