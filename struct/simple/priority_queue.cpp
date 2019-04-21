#include <iostream>
#include <vector>

class PQ {
public:
    std::vector<int> a;
    int n = 0;

    PQ() = default;

    PQ(std::vector<int> &a) : a(a), n(a.size())
    {
        build_max_heap();
    }

private:

    int left(int i) const {
        return (i+1)*2-1;
    }

    int right(int i) const {
        return (i+1)*2;
    }

    int parent(int i) const {
        return (i-1)/2;
    }

    void max_heapify(int i, int k) {
        while (i < k/2) {
            int l = left(i), r = right(i), next = i;
            if (l < k && a[l] > a[i])
                next = l;
            if (r < k && a[r] > a[next])
                next = r;
            if (next == i)
                break;
            std::swap(a[i], a[next]);
            i = next;
        }
    }

    void build_max_heap() {
        for (int i = n/2-1; i >= 0; i--)
            max_heapify(i, n);
    }

public:
    void sort_a() {
        build_max_heap();
        int k = n;
        for (int i = 0; i < n; i++) {
            std::swap(a[0], a[k-1]);
            k--;
            max_heapify(0, k);
        }
    }

    int get_max() const {
        if (n == 0)
            return -1;
        return a[0];
    }

    int erase_max() {
        if (n == 0)
            return -1;
        int max = a[0];
        std::swap(a[0], a[n-1]);
        n--;
        max_heapify(0, n);
        return max;
    }

    void insert(int i) {
        n++;
        if (a.size() < n)
            a.push_back(i);
        else
            a[n-1] = i;
        int j = n-1;
        while (j > 0) {
            if (a[parent(j)] < a[j]) {
                std::swap(a[parent(j)], a[j]);
                j = parent(j);
            } else 
                break;
        }
    }
};

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) 
        std::cin >> a[i];

    PQ pq(a);

    for (int i = 0; i < pq.a.size(); i++)
        std::cout << pq.a[i] << " ";
    std::cout << std::endl;

    for (int i = 0; i < 10; i++) {
        pq.insert(i);
    }

    for (int i = 0; i < pq.a.size(); i++)
        std::cout << pq.a[i] << " ";
    std::cout << std::endl;
    
    for (int i = 0; i < 5; i++) {
        std::cout << pq.erase_max() << std::endl;
        for (int i = 0; i < pq.n; i++)
            std::cout << pq.a[i] << " ";
        std::cout << std::endl << std::endl;
    }

    pq.sort_a();

    for (int i = 0; i < pq.n; i++)
        std::cout << pq.a[i] << " ";
    std::cout << std::endl;

    return 0;
}
