#include <iostream>
#include <vector>

void sort(std::vector<int> &a) {
    for (int i = 1; i < a.size(); i++) {
        for (int j = i; j>0 && a[j-1]>a[j]; j--) 
            std::swap(a[j-1], a[j]);
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
