#include <iostream>
#include <vector>

struct S {
	int i = 0;
	int j = 0;

	S(int _i, int _j) {
		i = _i;
		j = _j;
	}
};

int main() {
	std::vector<S> v;
	v.push_back(S(1, 1));
	return 0;
}
