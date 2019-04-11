#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
 
struct Edge {
    	int u;
    	int v;
    	int w;
};
 
class DSU {
private:
    	std::vector<int> parent;
	std::vector<int> prices;
 
public:
    	DSU(int n, std::vector<int> &_prices)
        	: parent(n)
    	{
        	for (int i = 0; i < n; i++) {
         	   	parent[i] = i;
        	}
			prices = _prices;
    	}
 
    	int find_set(int x) {
        	if (x == parent[x]) return x;
        	return parent[x] = find_set(parent[x]);
    	}
 
    	void make_union(int x, int y) {
        	x = find_set(x);
        	y = find_set(y);
        	if (prices[x] > prices[y]) {
            		std::swap(x, y);
        	}   // now prices[x] < prices[y]
        	parent[y] = x;
    	}
};
 
 
std::vector<Edge> get_graph(int n) {
        std::vector<Edge> g;
        for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int w = 0;
                	std::cin >> w;
			if (j > i)
                		g.push_back(Edge{i, j, w});
		}
        }
        return g;
}
 
bool compare(Edge e1, Edge e2) {
        return e1.w < e2.w;
}
 
int get_price(std::vector<Edge> &g, std::vector<int> &prices) {
    int n = prices.size();
	int cost = 0;
	DSU dsu(n, prices);
	for (int i = 0; i < n; i++) {
		cost +=	prices[i];
	}
    	std::sort(g.begin(), g.end(), compare);
    	for (int i = 0; i < g.size(); i++) {
		int benefit = std::max(prices[dsu.find_set(g[i].u)], prices[dsu.find_set(g[i].v)]);
        	if (dsu.find_set(g[i].u) != dsu.find_set(g[i].v) && cost + g[i].w - benefit < cost) {
                    	dsu.make_union(g[i].u, g[i].v);
                        cost = cost + g[i].w - benefit;
                }
    	}

    	return cost;
}
 
int main() {
    	int n = 0;
    	std::cin >> n;
    	std::vector<Edge> g = get_graph(n);
	std::vector<int> prices(n);
	for (int i = 0; i < n; i++) {
		std::cin >> prices[i];
	}
    	std::cout << get_price(g, prices) << std::endl;
    	return 0;
}
