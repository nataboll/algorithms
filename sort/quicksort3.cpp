#include <iostream>
#include <vector>

struct Ptrs {
    int j;
    int lt;
    int rt;
};

Ptrs partition(std::vector<int> &a, int l, int r) {
    int i = l, j = r+1, lt = l, dt = l;
    while (true) {
        while (a[++i] < a[l])
            if (i == r) break;
        while (a[--j] > a[l])
            if (j == l) break;
        if (i >= j) break;
        std::swap(a[i], a[j]);
    }
    std::swap(a[l], a[j]);
    return Ptrs{j, lt, dt};
}

void quicksort(std::vector<int> &a, int l, int r) {
    if (l >= r) return;
    Ptrs p = partition(a, l, r);
    quicksort(a, l, p.j-1);
    quicksort(a, p.j+1, r);
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
