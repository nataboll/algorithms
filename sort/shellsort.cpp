#include <iostream>
#include <vector>
#include <list>

std::list<int> get_seq(int n) {
    std::list<int> seq;
    int h = 1;
    while (h < n) {
        seq.push_front(h);
        h = 3*h + 1;
    }
    return seq;
}

void h_sort(std::vector<int> &a, int h) {
    for (int i = h; i < a.size(); i++) {
        for (int j = i; j >= h && a[j-h] > a[j] ; j -= h)
            std::swap(a[j-h], a[j]);
    }
}

void sort(std::vector<int> &a) {
    std::list<int> seq = get_seq(a.size());
    for (auto it = seq.begin(); it != seq.end(); ++it) 
        h_sort(a, *it);
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
