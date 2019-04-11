#include <iostream>

int main() {
    int i = 5;
    while (i *= 0.5)
        std::cout << i << std::endl;
	return 0;
}
