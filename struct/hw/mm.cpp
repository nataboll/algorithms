#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>

template <class D, class Y>
class Treap : public std::enable_shared_from_this<Treap<D, Y> > {
public:
    typedef std::shared_ptr<Treap> Ptr;
private:
    Y y;
    Ptr left;
    Ptr right;
    size_t size;
    D sum;

public:
    D data;

    Ptr getptr() { return this->shared_from_this(); }

    Treap(D _d, Y _y) : data(_d), y(_y), left(Ptr()), right(Ptr()), size(1), sum(_d) {}

    Treap(const Treap<D, Y> &) = default;

    static void merge(Ptr &T, Ptr L, Ptr R) {
        if (!L || !R) {
            if (L)
                T = L;
            else
                T = R;
        } else if (L->y < R->y) {
            merge(L->right, L->right, R);
            T = L;
        } else {
            merge(R->left, L, R->left);
            T = R;
        }
        if (T) {
            T->updateSize();
            T->updateSum();
        }
    }

    static void split(Ptr T, size_t key, Ptr &T1, Ptr &T2, size_t add = 0) { 
        if (!T)
            T1 = T2 = Ptr();
        else {
            size_t cur_key = add + T->getLeftSize();
            if (key > cur_key) {
                split(T->right, key, T->right, T2, add + 1 + T->getLeftSize());
                T1 = T;
            } else {
                split(T->left, key, T1, T->left, add);
                T2 = T;
            }
            T->updateSize();
            T->updateSum();
        }
    }

    Ptr insert(D d, Y y0) {
        Ptr T;
        auto xy = std::make_shared<Treap<D, Y> >(d, y0);
        merge(T, getptr(), xy);
        return T;
    }

    std::pair<D, Ptr> getSum(size_t l, size_t r) {
        if (l > r)
            return std::make_pair(0, getptr());
        Ptr L, R, L1, R1, T;
        split(getptr(), l, L, R);
        split(R, r-l+1, L1, R1);
        D ans = L1 ? L1->sum : 0;
        merge(R, L1, R1);
        merge(T, L, R);
        return std::make_pair(ans, T);
    }

    static std::pair<Ptr, Ptr> swap(Ptr odd, Ptr even, size_t l, size_t r) {
        Ptr L_odd, R_odd, L1_odd, R1_odd, L_even, R_even, L1_even, R1_even;
        split(odd, l/2, L_odd, R_odd);
        split(R_odd, (r+1)/2 - l/2, L1_odd, R1_odd);
        split(even, (l+1)/2-1, L_even, R_even);
        split(R_even, r/2 - ((l+1)/2-1), L1_even, R1_even);
        merge(R_even, L1_odd, R1_even);
        merge(even, L_even, R_even);
        merge(R_odd, L1_even, R1_odd);
        merge(odd, L_odd, R_odd);
        return std::make_pair(odd, even);
    }

private:
    void updateSize() { size = getLeftSize() + getRightSize() + 1; }

    size_t getLeftSize() const { return getSize(left); }

    size_t getRightSize() const { return getSize(right); }

    static size_t getSize(Ptr node) { return node ? node->size : 0; }

    void updateSum() { sum = getLeftSum() + getRightSum() + data; }

    D getLeftSum() { return getSum(left); }

    D getRightSum() { return getSum(right); }

    static D getSum(Ptr node) { return node ? node->sum : 0; }
};

using Ptr = Treap<long long, size_t>::Ptr;

int main() {
    srand((size_t)time(0));
    size_t n = 0, m = 0;
    size_t swapper = 0;
    while(true) {
        std::cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        swapper++;
        std::cout << "Swapper " << swapper << ":" << std::endl;

        if (n == 1) {
            long long el = 0;
            std::cin >> el;
            for (size_t i = 0; i < m; i++) {
                size_t task = 0, l = 0, r = 0;
                std::cin >> task >> l >> r;
                if (task == 1) {
                    continue;
                } else {
                    if (l == 1 && r == 1)
                        std::cout << el << std::endl;
                    else 
                        std::cout << 0 << std::endl;
                }
            }
            std::cout << std::endl;
            continue;
        }

        long long el = 0;
        std::cin >> el;
        std::shared_ptr<Treap<long long, size_t> > t_odd(new Treap<long long, size_t>(el, (rand()%100000)+1));
        std::cin >> el;
        std::shared_ptr<Treap<long long, size_t> > t_even(new Treap<long long, size_t>(el, (rand()%100000)+1));
        for (size_t i = 2; i < n; i++) {
            std::cin >> el;
            size_t y = (rand()%100000) + 1;
            if ((i+1)&1)
                t_odd = t_odd->insert(el, y);
            else 
                t_even = t_even->insert(el, y);
        }
        for (size_t i = 0; i < m; i++) {
            size_t task = 0, l = 0, r = 0;
            std::cin >> task >> l >> r;
            if (task == 1) {
                std::pair<Ptr, Ptr> new_treaps = Treap<long long, size_t>::swap(t_odd, t_even, l, r);
                t_odd = new_treaps.first;
                t_even = new_treaps.second;
            } else {
                long long sum = 0;
                std::pair<long long, Ptr> res = t_odd->getSum(l/2, (r+1)/2-1);
                sum += res.first;
                t_odd = res.second;
                res = t_even->getSum((l+1)/2-1, r/2-1);
                sum += res.first;
                t_even = res.second;
                std::cout << sum << std::endl;
            }
        }
        std::cout << std::endl;
    }
    return 0;
}

