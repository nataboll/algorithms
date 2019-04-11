#include <iostream>
#include <vector>

void sort(std::vector<int> &a) {
    for (int i = 0; i < a.size()-1; i++) {
        int counter = 0;
        for (int j = 0; j < a.size()-1-i; j++) {
            if (a[j] > a[j+1]) {
                std::swap(a[j+1], a[j]);
                counter++;
            }
        }
        for (int j = a.size()-i-2; j > i; j--) {
            if (a[j] < a[j-1]) {
                std::swap(a[j-1], a[j]);
                counter++;
            }
        }
        if (!counter)
            break;
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
