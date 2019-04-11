#include <iostream>
#include <vector>
#include <cmath>

class segment_tree {
private:
    std::vector<long long> tree;
    long long N;
    long long n;
public:
    segment_tree(long long _N) : N(_N) {
        n = (1 << (long long)(std::log2(_N-1) + 1));
        tree.resize(2*n, 0);
        for (int i = n; i < n + N; i++) {
            tree[i] = i - n + 1;
        }
        for (int i = n-1; i > 0; i--) {
            tree[i] = tree[2*i] + tree[2*i+1];
        }
    }

    long long rsq(int l, int r) {
        l += (n-1);
        r += (n-1);
        long long ans = 0;
        while (l <= r) {
            if (l&1)
                ans += tree[l];
            if (!(r&1))
                ans += tree[r];
            l = (l+1)/2;
            r = (r-1)/2;
        }
        return ans;
    }

    long long get_new_score(int i) {
        long long l = i%N+1;
        long long r = (i - 1 + tree[i+n-1])%N+1;
        long long s = 0;
        if (l <= r)
            s = rsq(l, r);
        else 
            s = rsq(1, r) + rsq(l, N);
        return s/tree[i+n-1];
    }

    void update(int i) {
        long long x = get_new_score(i);
        i += (n-1);
        long long d = x - tree[i];
        tree[i] += d;
        while (i /= 2)
            tree[i] += d;
    }

    long long get_sum() {
        return tree[1];
    }
};

int main() {
    long long n = 0;
    std::cin >> n;
    segment_tree tree(n);
    int k = 0; 
    std::cin >> k;
    for (int i = 0; i < k; i++) {
        int s = 0;
        std::cin >> s;
        tree.update(s);
    }
    std::cout << tree.get_sum() << std::endl;
    return 0;
}
