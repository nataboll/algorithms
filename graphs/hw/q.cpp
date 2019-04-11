#include <iostream>
#include <vector>

class DSU {
private:
	std::vector<int> parent;
	std::vector<int> w;
	int counter = 0;	// number of components

public:
	DSU(int n)
		: parent(n)
		, w(n)
	{
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			w[i] = 0;
		}
		counter = n;
	}

	int find_set(int x) {
		if (x == parent[x]) return x;
		return parent[x] = find_set(parent[x]);
	}

	void make_union(int x, int y) {
                x = find_set(x);
                y = find_set(y);
                if (x == y) {
                        return;
                }
		counter--;
                if (w[x] > w[y]) {
                        std::swap(x, y);
                }
                parent[x] = y;
                if (w[x] == w[y]) {
			w[y]++;
		}
        }

	int get_counter() const {
		return counter;
	}
};

int main() {
	int n = 0, m = 0;
	std::cin >> n >> m;
	DSU dsu(n);

	int counter = 0;
	for (int i = 0; i < m; i++) {
		int in = 0, out = 0;
		std::cin >> out >> in;
		dsu.make_union(out, in);
		counter++;
		if (dsu.get_counter() == 1) {
			break;
		}
	}

	std::cout << counter << std::endl;

	return 0;
}
