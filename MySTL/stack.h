//栈
#ifndef MYTINYSTL_STACK_H_
#define MYTINYSTL_STACK_H_

// 这个头文件包含了一个模板类 stack
// stack : 栈

#include "deque.h"    //以deque为基础

namespace mystl
{
    template<class T , class Container = mystl::deque<T>>
    class stack
    {
        public:
            typedef Container container_type;
            //使用底层容器的型别
            typedef typename Container::value_type value_type;
            typedef typename Container::size_type  size_type;
            typedef typename Container::reference  reference;
            typedef typename Container::const_reference const_reference;
            static_assert(std::is_same<T, value_type>::value,
                "the value_type of Container should be same with T");
            
        private:
            container_type c_;
        
        public:
            stack() = default;
            explicit stack(size_type n) : c_(n)
            {}
            stack(size_type n , const value_type& value) : c_(n , value)
            {}
            
            template<class IIter>
            stack(IIter first , IIter last) : c_(first , last)
            {}

            stack(std::initializer_list<T> ilist) : c_(ilist.begin() , ilist.end());
            {}
            stack(const Container & c) : c_(c)
            {}
            

        
    }
}