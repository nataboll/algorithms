#include <iostream>
#include <vector>

void quicksort(std::vector<int> &a, int l, int r) {
    int i = l, j = r;
    int pivot = a[(l+r)/2];
    while (i <= j) {
        while (a[i] < pivot)
            i++;
        while (a[j] > pivot)
            j--;
        if (i <= j) {
            std::swap(a[i], a[j]);
            i++;
            j--;
        }
        if (l < j) quicksort(a, l, j);
        if (i < r) quicksort(a, i, r);
    }
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) 
        std::cin >> a[i];
    quicksort(a, 0, a.size()-1);
    for (int i = 0; i < n; i++) 
        std::cout << a[i] << " ";
    std::cout << std::endl;
    return 0;
}
