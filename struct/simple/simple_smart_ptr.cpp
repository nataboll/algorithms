#include <iostream>

template <typename T>
class smart_pointer {
    T *m_obj;
    
public:
    smart_pointer(T *obj) : m_obj(obj)
    {}

    ~smart_pointer() {
        delete m_obj;
    }

    T* operator->() { return m_obj; }

    T& operator* () { return *m_obj; }
};

struct my_class {
    int x = 0;
    int y = 0;

    my_class() = default;

    my_class(int x, int y) : x(x), y(y) 
    {}
};

int main() {
    my_class *a = new my_class(1, 1);
    smart_pointer<my_class> ptr(a);
    std::cout << ptr->x << " " << ptr->y << std::endl;
    delete a;
    return 0;
}

