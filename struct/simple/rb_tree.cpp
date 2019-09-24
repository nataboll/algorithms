#include <iostream>
#include <vector>
#include <memory>
#include <set>
#include <cassert>

template<class Key, class Value>
class BST {
public:
    struct Node {
        Key key;
        Value val;
        int count;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        bool color; // true when red, false when black

        Node(Key key, Value val) : key(key), 
                                val(val), 
                                left(Ptr()), 
                                right(Ptr()),
                                count(0),
                                color(true)
        {}

        Node() = default;
    };

    using Ptr = std::shared_ptr<Node>;

    Ptr root;

    BST() : root(Ptr())
    {}

    void put(Key key, Value val) {
        root = put(root, key, val);
        root->color = false;
    }

    Key find_min() const {
        return find_min(root)->key;
    }

    Key find_max() const {
        return find_max(root)->key;
    }
    
    Key floor(Key key) const {
        Ptr x = floor(root, key);
        return (x) ? x->key : -1;
    }

    int rank(Key key) const {
        return rank(key, root);
    }

    std::set<Key> inorder() const {
        std::set<Key> q;
        inorder(root, q);
        return q;
    }

    void delete_min() {
        root = delete_min(root);
    }

    void delete_key(Key key) {
        root = delete_key(root, key);
        root->color = false;
    }

    Value find(Key key) const {
        return find(key, root)->val;
    }

private:

    bool is_red(const Ptr &x) const {
        return x ? x->color : false;
    }

    Ptr put(Ptr &x, Key key, Value val) {
        if (!x) return std::make_shared<Node>(key, val);
        if (key < x->key)
            x->left = put(x->left, key, val);
        else if (key > x->key)
            x->right = put(x->right, key, val);
        else x->val = val;
        x->count = 1 + size(x->left) + size(x->right);

        if (is_red(x->right) && !is_red(x->left)) x = rotate_left(x);
        if (is_red(x->left) && x->left->left && is_red(x->left->left)) x = rotate_right(x);
        if (is_red(x->left) && is_red(x->right)) flip_colors(x);

        return x;
    }

    Ptr rotate_left(Ptr &h) {
        assert(is_red(h->right));
        Ptr x = h->right;
        h->right = x->left;
        x->left = h;
        x->color = h->color;
        h->color = true;
        return x;
    }

    Ptr rotate_right(Ptr &h) {
        assert(is_red(h->left));
        Ptr x = h->left;
        h->left = x->right;
        x->right = h;
        x->color = h->color;
        h->color = true;
        return x;
    }

    void flip_colors(Ptr &h) {
        assert(!is_red(h) && is_red(h->left) && is_red(h->right));
        h->color = true;
        h->left->color = h->right->color = false;
    }

    Ptr find_min(const Ptr &x) const {
        return (x->left) ? find_min(x->left) : x;
    }

    Ptr find_max(const Ptr &x) const {
        return (x->right) ? find_max(x->right) : x;
    }

    Ptr floor(const Ptr &x, Key key) const {
        if (!x) return Ptr();
        if (key == x->key) return x;
        if (key < x->key) return floor(x->left, key);
        Ptr t = floor(x->right, key);
        return (t) ? t : x;
    }

    int size(const Ptr &root) const {
        return root ? root->count : 0;
    }

    int rank(Key key, const Ptr &x) const {
        if (!x) return 0;
        if (key < x->key) return rank(key, x->left);
        else if (key > x->key) return 1 + size(x->left) + rank(key, x->right);
        else return size(x->left);
    }

    void inorder(const Ptr &x, std::set<Key> &q) const {
        if (!x) return;
        inorder(x->left, q);
        q.insert(x->key);
        inorder(x->right, q);
    }

    Ptr delete_min(Ptr &x) {
        if (!x->left) {
            if (x->right) x->right->color = x->color;
            return x->right;
        }
        x->left = delete_min(x->left);
        x->count = 1 + size(x->left) + size(x->right);
        return x;
    }

    Ptr delete_key(Ptr &x, Key key) {
        if (!x) return Ptr();
        if (key < x->key) x->left = delete_key(x->left, key);
        else if (key > x->key) x->right = delete_key(x->right, key);
        else {
            if (!x->right) {
                if (x->left) x->left->color = x->color;
                return x->left;
            }
            if (!x->left) {
                x->right->color = x->color;
                return x->right;
            }
            
            Ptr t = x;
            x = find_min(t->right);
            x->right = delete_min(t->right);
            x->left = t->left;
        }
        
        x->count = 1 + size(x->left) + size(x->right);
        return x;
    }

    Ptr find(Key key, const Ptr &x) const {
        if (key < x->key) return find(key, x->left);
        else if (key > x->key) return find(key, x->right);
        else return x;
    }
};

int main() {
    BST<int, int> bst; 
    bst.put(1, 1); 
    bst.put(1, 2);
    bst.put(2, 2);
    bst.put(7, 2);
    bst.put(5, 2);
    bst.put(6, 2);
    std::set<int> q = bst.inorder();
    for (auto i : q)
        std::cout << i << ":" << bst.find(i) << " ";
    std::cout << std::endl;
    std::cout << bst.find_min() << " " << bst.find_max() << std::endl;
    bst.delete_key(2);
    q = bst.inorder();
    for (auto i : q)
        std::cout << i << ":" << bst.find(i) << " ";
    std::cout << std::endl;
    std::cout << bst.rank(5) << std::endl;
    std::cout << bst.floor(5) << std::endl;
    std::cout << bst.floor(6) << std::endl; 
    return 0;
}

