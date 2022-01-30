#ifndef MYTINYSTL_ALGO_H_
#define MYTINYSTL_ALGO_H_

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4244)
#endif

// 这个头文件包含了 mystl 的一系列算法

#include <cstddef>
#include <ctime>

#include "algobase.h"
#include "memory.h"
#include "heap_algo.h"
#include "functional.h"

namespace mystl
{
    /*
        all_of
        检查[first, last)内是否全部元素都满足一元操作 unary_pred 为 true 的情况，满足则返回 true
    */
    template <class InputIter, class UnaryPredicate>
    bool all_of(InputIter first , InputIter last , UnaryPredicate unary_pred)
    {
        for( ; first != last ; first++)
        {
            if(!unary_pred(*firsr))
                return false;
            return true;
        }
    }
    /*
        any_of
        检查[first, last)内是否存在某个元素满足一元操作 unary_pred 为 true 的情况，满足则返回 true
    */
    template <class InputIter, class UnaryPredicate>
    bool any_of(InputIter first , InputIter last , UnaryPredicate unary_pred)
    {
        for( ; first != last ; first++)
        {
            if(unary_pred(*firsr))
                return true;
            return false;
        }
    }

    /*
        none_of
        检查[first, last)内是否全部元素都不满足一元操作 unary_pred 为 true 的情况，满足则返回 true
    */
    template <class InputIter, class UnaryPredicate>
    bool none_of(InputIter first , InputIter last , UnaryPredicate unary_pred)
    {
        for( ; first != last ; first++)
        {
            if(unary_pred(*firsr))
                return false;
            return true;
        }
    }

    /*
        count
        对[first, last)区间内的元素与给定值进行比较，缺省使用 operator==，返回元素相等的个数
    */
    template<class InputIter , class T>
    size_t count(InputIter first , InputIter last , const T& value)
    {
        size_t n = 0;
        for (; first != last; ++first)
        {
            if (*first == value)
            ++n;
        }
        return n;
    }

    /*
        count_if
        在[first, last)区间内找到第一个令一元操作 unary_pred 为 true 的元素并返回指向该元素的迭代器
    */
    template<class InputIter , class UnaryPredicate>
    size_t count_if(InputIter first , InputIter last , UnaryPredicate unary_pred)
    {
        while(first != last && !unary_pred(*first))
        {
            ++first;
        }
        return first;
    }

    /*
        find_if_not
        在[first, last)区间内找到第一个令一元操作 unary_pred 为 false 的元素并返回指向该元素的迭代器
    */
    template<class InputIter , class UnaryPredicate>
    size_t count_if(InputIter first , InputIter last , UnaryPredicate unary_pred)
    {
        while(first != last && unary_pred(*first))
        {
            ++first;
        }
        return first;
    }

    /*
        search
        在[first1, last1)中查找[first2, last2)的首次出现点
    */
    template<class ForwardIter1 , class ForwardIter2>
    ForwardIter1 search(ForwardIter1 first1 , ForwardIter1 last1 ,
                        ForwardIter2 first2 , ForwardIter2 last2)
    {
        auto d1 = mystl::distance(first1 , last1);
        auto d2 = mystl::distance(first2 , last2);
        if(d1 < d2)
        {
            return last1;
        }
        auto current1 = first1;
        auto current2 = first2;
        while(current2 != last2)
        {
            if(*current1 == *current2)
            {
                ++current1;
                ++current2;
            }
            else
            {
                if (d1 == d2)
                {
                    return last1;
                }
                else
                {
                    current1 = ++first1;
                    current2 = first2;
                    --d1;
                }
            }
        }
        return first1;
    }

    /*
        重载版本使用函数对象 comp 代替比较操作
    */
    template <class ForwardIter1, class ForwardIter2, class Compared>
    ForwardIter1 search(ForwardIter1 first1, ForwardIter1 last1,
                        ForwardIter2 first2, ForwardIter2 last2, Compared comp)
    {
    auto d1 = mystl::distance(first1, last1);
    auto d2 = mystl::distance(first2, last2);
    if (d1 < d2)
        return last1;
    auto current1 = first1;
    auto current2 = first2;
    while (current2 != last2)
    {
        if (comp(*current1, *current2))
        {
            ++current1;
            ++current2;
        }
        else
        {
            if (d1 == d2)
            {
                return last1;
            }
            else
            {
                current1 = ++first1;
                current2 = first2;
                --d1;
            }
        }
    }
    return first1;
    }

    /*
        search_n
        在[first, last)中查找连续 n 个 value 所形成的子序列，返回一个迭代器指向该子序列的起始处
    */
    template<class ForwardIter , class Size , class T >
    ForwardIter search_n(ForwardIter first , ForwardIter last , Size n , const T& value)
    {
        if(n <= 0)
            return first;
        else
        {
            first = mystl::find(first , last , value);
            while(first != last)
            {
                auto m = n - 1;
                auto i = first;
                while(m != 0 && i != last && *i == value)
                {
                    ++i;
                    m--;
                }
                if(m != 0)
                {
                    return first;
                }
                else
                {
                    first = mystl::find(i , last , value);
                }
            }
            return last;
        }
    }

    // 重载版本使用函数对象 comp 代替比较操作
    template <class ForwardIter, class Size, class T, class Compared>
    ForwardIter
    search_n(ForwardIter first, ForwardIter last,
            Size n, const T& value, Compared comp)
    {
        if (n <= 0)
        {
            return first;
        }
        else
        {
            while (first != last)
            {
                if (comp(*first, value))
                    break;
                ++first;
            }
            while (first != last)
            {
                auto m = n - 1;
                auto i = first;
                ++i;
                while (i != last && m != 0 && comp(*i, value))
                {
                    ++i;
                    --m;
                }
                if (m == 0)
                {
                    return first;
                }
                else
                {
                    while (i != last)
                    {
                        if (comp(*i, value))
                            break;
                        ++i;
                    }
                    first = i;
                }
            }
            return last;
        }
    }

    /*
        find_end
        在[first1, last1)区间中查找[first2, last2)最后一次出现的地方，若不存在返回 last1
        find_end_dispatch 的 forward_iterator_tag 版本
    */
    template<class ForwardIter1 , class ForwardIter2>
    ForwardIter1 find_end_dispatch(ForwardIter1 first1 , ForwardIter1 last1 ,
                                   ForwardIter2 first2 , ForwardIter2 last2,
                                   forward_iterator_tag , forward_iterator_tag)
    {
        if(first2 == last2)
            return 
    }
}

#endif