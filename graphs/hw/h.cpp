#include <iostream>
#include <queue>
#include <list>
 
enum Color {
    WHITE,
    GRAY,
    BLACK,
};
 
using Graph = std::vector<std::vector<int>>;

std::list<int> get_way(Graph &g, int start, int finish) {
	std::vector<int> color(g.size());
	std::vector<int> prev(g.size());
 
        for (int i = 0; i < g.size(); i++) {
                color[i] = WHITE;
        	prev[i] = -1;
        }
 
	std::queue<int> q;
        q.push(start);
        color[start] = GRAY;
        while(!q.empty()) {
                int current = q.front();
                color[current] = BLACK;
                q.pop();
        	if (current == finish) {
            		break;
        	}
                for (auto neighbor : g[current]) {
                        if (color[neighbor] == WHITE) {
                                q.push(neighbor);
                                color[neighbor] = GRAY;
                		prev[neighbor] = current;
                        }
                }
        }

	int current = finish;
	std::list<int> way;
	way.push_front(current);
	if (prev[current] == -1) {
		std::list<int> err_list;
		err_list.push_front(-2);
        	return err_list;
	}
	while (current != start) {
        	current = prev[current];
        	way.push_front(current);
	}

	return way;
}
 
int main() {
    	int n = 0, m = 0;
	std::cin >> n >> m;

	int start = 0, finish = 0;
        std::cin >> start >> finish;
        start--;
        finish--;

	Graph g(n);
	for (int i = 0; i < m; i++) {
        	int out = 0, in = 0;
		std::cin >> out >> in;
            	g[--out].push_back(--in);
		g[in].push_back(out);
    	}

	if (n == 1 || start == finish) {
		std::cout << 0 << std::endl;
		std::cout << start+1 << std::endl;
		return 0;
	}

	std::list<int> way = get_way(g, start, finish);

	if (way.front() >= 0) {
		std::cout << way.size()-1 << std::endl;
	}
	for (auto i = way.begin(); i != way.end(); ++i) {
		std::cout << *i+1 << " ";
	}
	std::cout << std::endl;

    	return 0;
}
 

