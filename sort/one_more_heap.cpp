#include <iostream>
#include <vector>

class Heap {
private:
    int left(int i) {
        return 2*(i+1)-1;
    }

    int right(int i) {
        return 2*(i+1);
    }

    int upper(int i) {
        return (i-1)/2;
    }

    void sink(int i) {
        while (left(i) < n) {
            int j = left(i);
            if (j < n-1 && a[j] < a[j+1]) j++;
            if (a[j] < a[i]) break;
            std::swap(a[i], a[j]);
            i = j;
        }
    }

    void swim(int i) {
        while (i > 0 && a[upper(i)] < a[i]) {
            std::swap(a[i], a[upper(i)]);
            i = upper(i);
        }
    }

public:
    std::vector<int> a;
    int n;

    Heap(const std::vector<int> &a) : a(a), n(a.size())
    {
        build_heap();
    }

    void build_heap() {
        for (int i = n/2-1; i >= 0; i--)
            sink(i);
    }

    void sort() {
        while(n > 1) {
            std::swap(a[0], a[--n]);
            sink(0);
        }
    }

    void insert(int i) {
        if (a.size() == n)
            a.push_back(i);
        else
            a[n] = i;
        n++;
        swim(n-1);
    }

    int del_max() {
        int max = a[0];
        std::swap(a[0], a[--n]);
        sink(0);
        a[n] = -1;
        return max;
    }
};

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> a(n, 0);
    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    Heap heap(a);
    for (int i = 0; i < heap.n; i++) 
        std::cout << heap.a[i] << " ";
    std::cout << std::endl;

    heap.insert(21);
    heap.insert(20);
    for (int i = 0; i < heap.n; i++) 
        std::cout << heap.a[i] << " ";
    std::cout << std::endl;

    std::cout << heap.del_max() << std::endl;
    heap.sort();
    for (int i = 0; i < heap.a.size(); i++) 
        std::cout << heap.a[i] << " ";
    std::cout << std::endl;
    return 0;
}

