#include <iostream>
#include <vector>
#include <map>

std::vector<int> twoSum(std::vector<int> &a, int target) {
    std::map<int, int> used;
    std::vector<int> p(2, -1);
    for (int i = 0; i < a.size(); i++) {
        if (used.find(target - a[i]) != used.end()) {
            p[0] = used[target - a[i]];
            p[1] = i;
            return p;
        } else {
            used.insert(std::make_pair(a[i], i));
        }
    }
    return p;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    int target = 0;
    std::cin >> target;
    std::vector<int> p = twoSum(a, target);
    for (int i = 0; i < 2; i++)
        std::cout << p[i] << " ";
    std::cout << std::endl;
    return 0;
}
