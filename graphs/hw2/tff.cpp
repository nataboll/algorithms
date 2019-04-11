#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;


enum Color {
	WHITE,
	GRAY,
	BLACK,
};

vector<int> bfs_back_way(const int start, const int finish) {
	map<const int, Color> color;	// if value is not in map, it's white 
	map<const int, int> prev;
	queue<int> q;
	q.push(start);
	color[start] = GRAY;
	while (!q.empty()) {
		int current = q.front();
		if (current == finish) {
			break;
		}
		color[current] = BLACK;
		q.pop();
		if ((current / 1000 < 9) && (color.find(current + 1000) == color.end())) {
			q.push(current + 1000);
			color[current + 1000] = GRAY;
			prev[current + 1000] = current;
		}

		if ((current % 10 > 1) && (color.find(current - 1) == color.end())) {
			q.push(current - 1);
			color[current - 1] = GRAY;
			prev[current - 1] = current;
		}

		int left_shift_value = (current % 1000) * 10 + (current / 1000);
		if (color.find(left_shift_value) == color.end()) {
			q.push(left_shift_value);
			color[left_shift_value] = GRAY;
			prev[left_shift_value] = current;
		}

		int right_shift_value = (current % 10) * 1000 + (current / 10);
		if (color.find(right_shift_value) == color.end()) {
			q.push(right_shift_value);
			color[right_shift_value] = GRAY;
			prev[right_shift_value] = current;
		}
	}
	
	vector<int> back_way;
	int current = finish;
	back_way.push_back(current);
	while (current != start) {
		current = prev[current];
		back_way.push_back(current);
	}
	return back_way;
}

int main() {
	int in_value, out_value;
	cin >> in_value >> out_value;
	
	vector<int> back_way = bfs_back_way(in_value, out_value);

	for (int i = back_way.size() - 1; i >= 0; i--) {
			cout << back_way[i] << endl;
	}

	return 0;
}
