#include <iostream>
#include <unordered_map>
#include <string>
#include <list>
#include <vector>
#include <cassert>
#include <iterator>
#include <utility>

using std::string;
//using std::assert;
using std::vector;
using std::list;
using std::pair;

class TestComparison {
public:
    static void comparison_between_signed_and_unsigned_integer() {
        int sz = -1;
        string str = "test comparison to a size_t value";
        //assert(sz < str.size());   // Dangerous Error!!! This statment will never be true.
        assert(sz < 0 || sz < str.size());   // judge if sz is a nagative alone
        std::cout << "Here is a very subtle error! When comparing a negative signed integer\n"
                      "with an unsigned integer returned by the method size() of any container,\n"
                      "the statement (sz < str.size()) will never be True, which indicates that compiler\n"
                      "transfers all values into unsigned integer before real comparison happening." << std::endl;        
    }

};

class TestScope {
public:
    static void declare_in_condition_statement() {
        //if ((int a = 4) > 0)   // Compile Error: expected primary-exression before 'int'
        int a = 0;      // declare the variable beforehand
        if ((a = 4) > 0) {
            std::cout << "value is: " << a << std::endl;
        }
    }
};

using std::unordered_map;
class TestUnorderedMap {
public:
    static void init_manners() {
    }

    static void  set_default_for_iterator() {
        unordered_map<int, int> test_map = {{'a',1}, {'b',2}};
        // Compile Error: conversion from 'std::nullptr_t' to non-scalar type 'std::unordered_map<int, int>::iterator' ...
        // unordered_map<int, int>::iterator itr = nullptr; 
        unordered_map<int, int>::iterator itr = test_map.end();   // set default as Map::END() instead

    }

};

class TestList {
public:
    static void basic_usage() {
        vector<int> a = {1, 2, 3, 4};
        list<int> b(a.rbegin(), a.rend());

        list<int>::iterator it = b.begin();
        it++;       // Operator overload  list已经对 ++ --进行了操作符重载了，但不代表list的迭代器可以计算！！！
        //it += 1;    // Error: no match for 'operator+' (operand types are 'std::__cxx11::list<int>::iterator)
        std::cout << *it << std::endl;

        it--;
        std::cout << *it << std::endl;


        b.insert(it, 100);

        for (auto x : b) {
            std::cout << x << ", ";
        }
        std::cout << std::endl;

        std::cout << *it << "; " << *(++it) << std::endl;


        /*
          可以通过正向迭代器i来给 反向迭代器r 赋值, 它们之间的关系是: &*r == &*(i-1), 事实上并不指向同一个位置。
          参考：https://en.cppreference.com/w/cpp/iterator/reverse_iterator。
        */
        list<int>::reverse_iterator xxx(b.begin());
        //list<int>::iterator last_it(b.begin());    // Error: 不能用reverse_iterator 来初始化 iterator


        /*
          如何最快获取指向链表最后元素的迭代器。ref:https://www.codenong.com/2678175/
        */
       it = b.end();
       list<int>::iterator head = b.begin();
       std::advance(head, b.size()-1);
       std::cout << "the Last ele is: a. " << *(--it)
                 << "\nb. " << *std::prev(b.end())
                 << "\nc. " << *head << std::endl;
    }
};


/*
ref:
1) https://sg-first.gitbooks.io/cpp-template-tutorial/content/jie_te_hua_yu_pian_te_hua.html
2)
*/
class TestTemplateUsage {
public:
    /* 注意 “模版函数" 和 "模版类" 在specialization时的不同！
        1) 模版函数只能全特化（目前），而模版类可以全特化，还可以偏特化 partial specialization;
        2) 函数模版特化时，C++ 允许模版参数的类型从传递给特化版本的参数中推导出来，这就意味着，在
            调用一个特化的函数模版时，编译器会根据传递的参数类型自动推动出模版参数的类型，从而不需要
            “显示”指定模版参数。
            而对于类模版特化时，C++ 要求你“必须显示”指定模版参数的类型。编译器不会尝试从构造函数的
            参数中推导模版参数的类型。因此，当你想要使用一个模版类的特化版本时，你就需要“显示”地指定
            模版参数类型，如：std::vector<int> my_vec。
    */
    static void use_make_pair() {
        //pair<int, int> point = std::make_pair<int, int>(1, 2);    // 肯定是可以的
        pair<int, int> point = std::make_pair(1, 2);           // 不需要显示指定模版参数以特化
        std::cout << "New Point (" << point.first << "," << point.second << ")" << std::endl;
    }

};

int main() {
    //TestScope::declare_in_condition_statement();

    //TestComparison::comparison_between_signed_and_unsigned_integer();

    //TestList::basic_usage();

    TestTemplateUsage::use_make_pair();

    return 0;
}