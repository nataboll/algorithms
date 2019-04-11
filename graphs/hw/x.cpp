#include <iostream>
#include <vector>
#include <utility>
#include <queue>

#define BOUND 1000000001

enum Color {
	WHITE,
	GRAY,
	BLACK,
};

using Graph = std::vector<std::vector<std::pair<int, int>>>;

struct Station {
	int number = 0;
	int time = 0;

	Station(int _n, int _t) {
		number = _n;
		time = _t;
	}
};

struct Passage {
	Station start;
	Station finish;

	Passage(int _s, int _s_time, int _f, int _f_time) : start(_s, _s_time), finish(_f, _f_time) {}
};

using Timetable = std::vector<Passage>;

Timetable get_timetable() {
	int m = 0;
	std::cin >> m;
	Timetable table;

	for (int i = 0; i < m; i++) {
		int out = 0, t_out = 0, in = 0, t_in = 0;
		std::cin >> out >> t_out >> in >> t_in;
		table.push_back(Passage(out, t_out, in, t_in));
	}

	return table;
}

int get_destination_time(Timetable &table, int start, int finish) {
	std::vector<Color> color(table.size());
	for (int i = 0; i < color.size(); i++) {
		color[i] = WHITE;
	}

	std::queue<int> q; // numbers of passages
	
	for (int i = 0; i < table.size(); i++) {
		if (table[i].start.number == start && table[i].start.time >= 0) {
			q.push(i);
			color[i] = GRAY;
		}
	}

	int destination_time = BOUND;
	while (!q.empty()) {
		int current = q.front();
		if (table[current].finish.number == finish && table[current].finish.time < destination_time)
			destination_time = table[current].finish.time;
		color[current] = BLACK;
		q.pop();
		for (int i = 0; i < table.size(); i++) {
	                if (table[i].start.number == table[current].finish.number && table[i].start.time >= table[current].finish.time) {
				if (color[i] == WHITE) {
        	                	q.push(i);
                	        	color[i] = GRAY;
				}
                	}
        	}

	}
	
	if (start == finish && destination_time > 0) {
		return 0;
	}

	return destination_time;
}

int main() {
	int n = 0;
	std::cin >> n;
	int start = 0, finish = 0;
	std::cin >> start >> finish;
	Timetable table = get_timetable();
	std::cout << get_destination_time(table, start, finish) << std::endl;
	return 0;
}

