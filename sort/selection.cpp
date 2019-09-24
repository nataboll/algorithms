#include <iostream>
#include <vector>

void sort(std::vector<int> &a) {
    for (int i = 0; i < a.size()-1; i++) {
        int m = i;
        for (int j = i+1; j < a.size(); j++)
            m = (a[j] < a[m]) ? j : m;
        std::swap(a[i], a[m]);
    }
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) 
        std::cin >> a[i];
    sort(a);
    for (int i = 0; i < n; i++) 
        std::cout << a[i] << " ";
    std::cout << std::endl;
    return 0;
}
