#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
    int num;
    int x;
    int y;
    int left;
    int right;
    int parent;

    Node() : num(0)
             , x(0)
             , y(0)
             , left(-1)
             , right(-1)
             , parent(-1)
    {}

    Node(int num, int x, int y) : num(num)
                                , x(x)
                                , y(y)
                                , left(-1)
                                , right(-1)
                                , parent(-1)
    {}
};

class Treap {
public:
    std::vector<Node> treap;

    Treap(std::vector<Node> &data) : treap(data.size()) {
        treap[data[0].num] = data[0];
        int root = data[0].num;

        for (int i = 1; i < data.size(); i++) {
            int add = data[i].num;
            treap[add] = data[i];

            int cur = data[i-1].num;
            while (true) {
                if (cur < 0) {
                    treap[root].parent = add;
                    treap[add].left = root;
                    root = add;
                    break;
                } else if (treap[cur].y < treap[add].y) {
                    int prev_right = treap[cur].right;
                    treap[cur].right = add;
                    treap[add].parent = cur;
                    treap[add].left = prev_right;

                    if (prev_right >= 0)
                        treap[prev_right].parent = add;

                    break;
                }

                cur = treap[cur].parent;
            }
        }
    }
};

class Comparator {
public:
    bool operator() (const Node &node1, const Node &node2) const {
        return node1.x < node2.x;
    }
};

int main() {
	int n = 0;
	std::cin >> n;
    std::vector<Node> data(n);
	for (int i = 0; i < n; i++) {
		int ai = 0, bi = 0;
		std::cin >> ai >> bi;
		data[i] = Node{i, ai, bi};
	}

    std::sort(data.begin(), data.end(), Comparator());

    Treap treap(data);
	std::cout << "YES" << std::endl;
    auto &res = treap.treap;

    for (auto &node : res) {
		std::cout << node.parent + 1 << " " << node.left + 1 << " " << node.right + 1 << std::endl;
	}
	return 0;
}
