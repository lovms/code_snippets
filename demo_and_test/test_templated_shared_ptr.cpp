/* 这里是 shared_ptr一个demo,
 * (1)一个shared_ptr的最基本的成员变量有两个，一个是指针；另一个也是指针，不过是用于计数的。
 *    之所以计数要用指针，是因为共享shared_ptr的实例会有很多个，它们需要共享计数！
 *
 * (2)当然方位成员变量的接口成员函数也是不可或缺的，如 get(), get_count() 方法
 *
 * (3)此外，必须要有拷贝构造函数，最好要有=operator操作符的重载，这也是shared_ptr会有多个共享实例的应用场景所必须的，
 *    但要细心的区分开拷贝够函数以及=operator重载的调用场景，代码的注释中有提到。
 */

#include <iostream>

template <typename T>

class shared_ptr {
public:
    shared_ptr();
    explicit shared_ptr(T*);
    /* 这里有个特别有意思的问题：就是类似于Type x = y; 这种赋值方式，其实并不是调用=操作符的重载，
     * 实际上是调用了这里的拷贝构造函数！！！而且是隐式调用的！！！
     *
     * 由于是隐式调用的，因此不能加explicit关键词来避免隐式调用。
     */
    shared_ptr(shared_ptr&);
    ~shared_ptr();
    //share_ptr<T> operator= (shared_ptr &
    T* get();
    int get_count();

    shared_ptr& operator= (shared_ptr& rp);

private:
    int *_count;
    T* _ptr;
};

template <typename T>
shared_ptr<T>::shared_ptr(): _count(new int(0)), _ptr(nullptr) {
}

template <typename T>
shared_ptr<T>::shared_ptr(T* v) :  _ptr(v) {
    _count = new int(1);
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T>& sptr) {
    *(sptr._count) += 1;
    this->_count = sptr._count;
    this->_ptr = sptr._ptr;
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    if (_count != nullptr) {
        if (*_count <= 1) {
            if (_ptr != nullptr) {
                delete _ptr;
                std::cout << "DEBUG: delete ptr\n";
            }
            delete _count;
            std::cout << "DEBUG: delete count\n";
        } else {
            *_count -= 1; //析构函数不能只想着要释放指针，非最后一个共享指针的实例析构时，需要将计数减一，这个也非常重要！
        }
    }
}

template <typename T>
T *shared_ptr<T>::get() {
    return _ptr;
}

template <typename T>
int shared_ptr<T>::get_count() {
    return *_count;
}

/*
 * 1)=操作符重载，需要特别注意调用方其实是左值, 因此必须事先分配内存！
 *   Type x = y; 这种方式并不能调用=操作符重载！！！实际是用y去初始化x,因此调用了拷贝构造函数
 * 2)返回值必须是引用。
 *   因为调用方是左值，返回值如果不是引用或者指针，那么是不能做为左值的
 */
template <typename T>
shared_ptr<T>& shared_ptr<T>::operator= (shared_ptr<T>& rp) { 
    *(rp._count) += 1;
    this->_count = rp._count;
    this->_ptr = rp._ptr;
    return (*this);
}

int main() {
    shared_ptr<int> p1(new int(100));
    std::cout << "p1: count: " <<  *(p1.get()) << "\n";

    shared_ptr<int> p2(p1);

    std::cout << "p2: count: " << p2.get_count()  << "\t"
              << "value: " << *(p2.get())<< "\n";

    shared_ptr<int> p3 = p2; 
    std::cout << "p3: count: " << p2.get_count()  << "\t"
              << "value: " << *(p2.get())<< "\n";


    std::cout << "=====================\n";
    shared_ptr<int> px1(new int(1000));
    std::cout << "px1: count: " << px1.get_count()  << "\t"
              << "value: " << *(px1.get())<< "\n";

    shared_ptr<int> px2;
    px2 = px1;
    std::cout << "px2: count: " << px2.get_count()  << "\t"
              << "value: " << *(px2.get())<< "\n";


    std::cout << "=====================\n";
    shared_ptr<double> py1(new double(0.234));
    std::cout << "py1: count: " << py1.get_count() << "\t"
              << "value: " << *(py1.get()) << "\n";
    return 0;
} 
