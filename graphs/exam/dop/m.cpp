#include <iostream>
#include <memory>
#include <vector>

class Treap : public std::enable_shared_from_this<Treap> {
private:
    using Ptr = std::shared_ptr<Treap>;

    int y;
    int data;
    int sum;
    int size;

    Ptr left;
    Ptr right;

public:
    Treap(int data, int y) : data(data), y(y), sum(data^2), size(1), left(Ptr()), right(Ptr())
    {}

    Ptr get_ptr() const {
        return shared_from_this();
    }

    int get_size() const {
        return size;
    }

    int get_sum() const {
        return sum;
    }

    static void merge(Ptr &T, Ptr L, Ptr R) {
        if (!L || !R) {
            if (L)
                T = L;
            else 
                T = R;
        } else {
            if (L->y < R->y) {
                merge(L->right, L->right, R);
                T = L;
            } else {
                merge(R->left, L, R->left);
                T = R;
            }
        }
        if (T) {
            T->update_size();
            T->update_sum();
        }
    }

    static void split(Ptr T, int key, Ptr &T1, Ptr &T2, int add = 0) { 
        if (!T)
            T1 = T2 = Ptr();
        else {
            int cur_key = add + T->get_left_size();
            if (key > cur_key) {
                split(T->right, key, T->right, T2, add + 1 + T->get_left_size());
                T1 = T;
            } else {
                split(T->left, key, T1, T->left, add);
                T2 = T;
            }
            T->update_size();
            T->update_sum();
        }
    }

    Ptr insert(int idx, int data, int y) {
        Ptr L, R, T, T1;
        auto xy = std::make_shared<Treap>(data, y);
        split(get_ptr(), idx+1, L, R);
        merge(T1, L, xy);
        merge(T, T1, R);
        return T;
    }

    Ptr remove(int idx) {
        Ptr L, R, L1, R1, T;
        split(get_ptr(), idx, L, R);
        split(R, idx+1, L1, R1);
        merge(T, L, R1);
    }

private:
    void update_size() {
        size = get_left_size() + get_right_size();
    }

    int get_left_size() const {
        return (left) ? left->get_size() : 0;
    }

    int get_right_size() const {
        return (right) ? right->get_size() : 0;
    }

    void update_sum() {
        sum = get_left_sum() + get_right_sum();
    }

    int get_left_sum() const {
        return (left) ? left->get_sum() : 0;
    }

    int get_right_sum() const {
        return (right) ? right->get_sum() : 0;
    }
};

int main() {
    int n = 0, p = 0;
    std::cin >> n >> p;
    std::shared_ptr<Treap> t;
    for (int i = 0; i < n; i++) {
        int data = 0;
        std::cin >> data;
        // generate random y
        if (t) 
            t = t->insert(i, data, y);
        else
            t = std::make_shared<Treap>(data, y);
    }
    int k = 0; 
    std::cin >> k;
    for (int i = 0; i < k; i++) {
        int task = 0, num = 0;
        std::cin >> task >> num;
        if (task == 1) {
            // num-1 - bankrot
        } else {
            // division of num-1
        }
        std::cout << t->get_sum() << std::endl;
    }
    return 0;
}
