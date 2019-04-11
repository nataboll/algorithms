#include <iostream>
#include <vector>

static const int INF = 1000;

void merge(std::vector<int> &a, int l, int r) {
    if (r-l <= 1) {
        if (a[l] > a[r])
            std::swap(a[l], a[r]);
        return;
    }
    merge(a, l, (l+r)/2);
    merge(a, (l+r)/2+1, r);
    std::vector<int> buffer(2, INF);
    std::vector<int> i(2);
    i[0] = l;
    i[1] = (l+r)/2+1;
    buffer[0] = a[i[0]];
    buffer[1] = a[i[1]];
    std::vector<int> tmp(r-l+1, 0);
    int curr = l;
    while (i[0] <= (l+r)/2 && i[1] <= r) {
        int next = (buffer[0] < buffer[1]) ? 0 : 1;
        tmp[curr-l] = buffer[next]; 
        i[next]++;
        buffer[next] = a[i[next]];
        curr++;
    }
    for (int j = i[0]; j <= (l+r)/2; j++) {
        tmp[curr-l] = a[j];
        curr++;
    }
    for (int j = i[1]; j <= r; j++) {
        tmp[curr-l] = a[j];
        curr++;
    }
    for (int i = l; i <= r; i++) {
        a[i] = tmp[i-l];
    }
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) 
        std::cin >> a[i];
    merge(a, 0, a.size()-1);
    for (int i = 0; i < n; i++) 
        std::cout << a[i] << " ";
    std::cout << std::endl;
    return 0;
}
