#include <iostream>
#include <vector>
#include <string>

std::pair<int, int> get_containers() {
    std::string b;
    std::cin >> b;
    if (b[0] != 'b') {
        return std::make_pair(1, (int)b[0]);
    } else {
        return std::make_pair(2, 40);
    }
}

int main() {
    // Number of test cases.
    int T = 0;
    std::cin >> T;
    for (int t = 0; t < T; t++) {
        // Capacity and number of containers for the test case.
        int K, n = 0;
        std::cin >> K >> n;
        // ships will coitain remaining capacity of each spaceship that is already in use.
        std::vector<int> ships;
        // Load spaceships.
        for (int c = 0; c < n;) {
            std::string b;
            // Number and volume of arriving containers.
            std::pair<int, int> containers = get_containers();
            int r = containers.first, v = containers.second;
            // Now put containers into spaceships.
            for (int i = 0; i < r; i++) {
                for (int s = 0; s < ships.size(); s++) {
                    // Put the container if possible.
                    if (ships[s] >= v) {
                        ships[s] -= v;
                        break;
                    } 
                    // If no place left, start using another spaceship.
                    ships.push_back(K-v);
                }
            }
        }
        // Print number of spaceships used.
        std::cout << ships.size();
        // Count waste.
        int w = 0;
        for (int i = 0; i < ships.size(); i++) {
            w += ships[i];
        }
        std::cout << w;
    }

    return 0;
}
