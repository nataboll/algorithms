#include <iostream>
#include <vector>

class Heap {
public:
    std::vector<int> a;

    Heap(std::vector<int> &a) : a(a)
    {
        sort_a();
    }

private:
    int left(int i) const {
        return (i+1)*2-1;
    }

    int right(int i) const {
        return (i+1)*2;
    }

    void build_max_heap() {
        for (int i = a.size()/2-1; i >= 0; i--) {
            max_heapify(i, a.size());
        }
    }

    void max_heapify(int i, int n) {
        while(i < n/2) {
            int l = left(i), r = right(i), next = i;
            if (l < n)
                next = (a[l] > a[i]) ? l : i;
            if (r < n)
                next = (a[r] > a[next]) ? r : next;
            if (next == i)
                break;
            std::swap(a[i], a[next]);
            i = next;
        }
    }

    void sort_a() {
        build_max_heap();
        int n = a.size();
        for (int i = n-1; i > 0; i--) {
            std::swap(a[n-1], a[0]);
            n--;
            max_heapify(0, n);
        }
    }
};

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) 
        std::cin >> a[i];
    Heap heap(a);
    for (int i = 0; i < heap.a.size(); i++) 
        std::cout << heap.a[i] << " ";
    std::cout << std::endl;
    return 0;
}
