#include <iostream>
#include <vector>

void merge(std::vector<int> &a, std::vector<int> &aux, int l, int m, int r) {
    int i = l, j = m+1;
    for (int k = l; k <= r; k++) {
        if (i > m) aux[k] = a[j++];
        else if (j > r) aux[k] = a[i++];
        else if (a[j] < a[i]) aux[k] = a[j++];
        else aux[k] = a[i++];
    }
}

void sort(std::vector<int> &a, std::vector<int> &aux, int l, int r) {
    if (l >= r)
        return;
    int m = (l+r)/2;
    sort(aux, a, l, m);
    sort(aux, a, m+1, r);
    merge(a, aux, l, m, r);
}

void mergesort(std::vector<int> &a) {
    std::vector<int> aux(a);
    sort(a, aux, 0, a.size()-1);
    a = aux;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) 
        std::cin >> a[i];
    mergesort(a);
    for (int i = 0; i < n; i++) 
        std::cout << a[i] << " ";
    std::cout << std::endl;
    return 0;
}
