#include <iostream>
#include <vector>

int bin_search(std::vector<int> &a, int k) {
    int l = 0, r = a.size()-1;
    while (l <= r) {
        int m = (l+r)/2;
        if (k < a[m])
            r = m-1;
        else if (k > a[m])
            l = m+1;
        else 
            return m;
    }
    return -1;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) 
        std::cin >> a[i];
    int k = 0;
    std::cin >> k;
    std::cout << bin_search(a, k) << std::endl;
    return 0;
}
