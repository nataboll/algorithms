#include <iostream>
#include <vector>

int main() {
	std::vector<int> a(6);
	a.push_back(3);
	std::cout << a.size() << std::endl;
	std::cout << a[0] << std::endl;
	return 0;
}
