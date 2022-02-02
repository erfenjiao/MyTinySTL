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
            return last1;
        else
        {
            auto result1 = last1;
            while(true)
            {
                // 利用 search 查找某个子序列的首次出现点，找不到则返回 last1
                auto new_result = mystl::search(first1 , last1 , first2 , last2);
                if(new_result == last1)
                {
                    return result;
                }
                else
                {
                    result = new_result;
                    first1 = new_result;
                    ++first1;
                }
            }
        }
    }

    // find_end_dispatch 的 bidirectional_iterator_tag 版本
    template <class BidirectionalIter1, class BidirectionalIter2>
    BidirectionalIter1
    find_end_dispatch(BidirectionalIter1 first1, BidirectionalIter1 last1,
                    BidirectionalIter2 first2, BidirectionalIter2 last2,
                    bidirectional_iterator_tag, bidirectional_iterator_tag)
    {
        typedef reverse_iterator<BidirectionalIter1> reviter1;
        typedef reverse_iterator<BidirectionalIter2> reviter2;
        reviter1 rlast1(first1);
        reviter2 rlast2(first2);
        reviter1 rresult = mystl::search(reviter1(last1), rlast1, reviter2(last2), rlast2);
        if (rresult == rlast1)
        {
            return last1;
        }
        else
        {
            auto result = rresult.base();
            mystl::advance(result, -mystl::distance(first2, last2));
            return result;
        }
    }

    template <class ForwardIter1, class ForwardIter2>
    ForwardIter1
    find_end(ForwardIter1 first1, ForwardIter1 last1,
            ForwardIter2 first2, ForwardIter2 last2)
    {
        typedef typename iterator_traits<ForwardIter1>::iterator_category Category1;
        typedef typename iterator_traits<ForwardIter2>::iterator_category Category2;
        return mystl::find_end_dispatch(first1, last1, first2, last2, Category1(), Category2());
    }

    // 重载版本使用函数对象 comp 代替比较操作
    // find_end_dispatch 的 forward_iterator_tag 版本
    template <class ForwardIter1, class ForwardIter2, class Compared>
    ForwardIter1
    find_end_dispatch(ForwardIter1 first1, ForwardIter1 last1,
                    ForwardIter2 first2, ForwardIter2 last2,
                    forward_iterator_tag, forward_iterator_tag, Compared comp)
    {
        if (first2 == last2)
        {
            return last1;
        }
        else
        {
            auto result = last1;
            while (true)
            {
                // 利用 search 查找某个子序列的首次出现点，找不到则返回 last1
                auto new_result = mystl::search(first1, last1, first2, last2, comp);
                if (new_result == last1)
                {
                    return result;
                }
                else
                {
                    result = new_result;
                    first1 = new_result;
                    ++first1;
                }
            }
        }
    }

    // find_end_dispatch 的 bidirectional_iterator_tag 版本
    template <class BidirectionalIter1, class BidirectionalIter2, class Compared>
    BidirectionalIter1
    find_end_dispatch(BidirectionalIter1 first1, BidirectionalIter1 last1,
                    BidirectionalIter2 first2, BidirectionalIter2 last2,
                    bidirectional_iterator_tag, bidirectional_iterator_tag, Compared comp)
    {
        typedef reverse_iterator<BidirectionalIter1> reviter1;
        typedef reverse_iterator<BidirectionalIter2> reviter2;
        reviter1 rlast1(first1);
        reviter2 rlast2(first2);
        reviter1 rresult = mystl::search(reviter1(last1), rlast1, reviter2(last2), rlast2, comp);
        if (rresult == rlast1)
        {
            return last1;
        }
        else
        {
            auto result = rresult.base();
            mystl::advance(result, -mystl::distance(first2, last2));
            return result;
        }
    }

    template <class ForwardIter1, class ForwardIter2, class Compared>
    ForwardIter1
    find_end(ForwardIter1 first1, ForwardIter1 last1,
            ForwardIter2 first2, ForwardIter2 last2, Compared comp)
    {
        typedef typename iterator_traits<ForwardIter1>::iterator_category Category1;
        typedef typename iterator_traits<ForwardIter2>::iterator_category Category2;
        return mystl::find_end_dispatch(first1, last1, first2, last2, Category1(), Category2(), comp);
    }

    /*
        find_first_of
        在[first1, last1)中查找[first2, last2)中的某些元素，返回指向第一次出现的元素的迭代器
    */
    template<class InputIter , class ForwardIter>
    InputIter find_first_of(InputIter first1 , InputIter last1,
                           ForwardIter first2 , ForwardIter last2)
    {
        for (; first1 != last1; ++first1)
        {
            for (auto iter = first2; iter != last2; ++iter)
            {
                if (*first1 == *iter)
                    return first1;
            }
        }
        return last1;
    }

    // 重载版本使用函数对象 comp 代替比较操作
    template <class InputIter, class ForwardIter, class Compared>
    InputIter
    find_first_of(InputIter first1, InputIter last1,
                ForwardIter first2, ForwardIter last2, Compared comp)
    {
        for (; first1 != last1; ++first1)
        {
            for (auto iter = first2; iter != last2; ++iter)
            {
                if (comp(*first1, *iter))
                    return first1;
            }
        }
        return last1;
    }

    /*
        find_each
        使用一个函数对象 f 对[first, last)区间内的每个元素执行一个 operator() 操作，但不能改变元素内容
    */
    template <class InputIter, class Function>
    Function for_each(InputIter first, InputIter last, Function f)
    {
        for( ; first != last ; first++)
        {
            f(*first)
        }
        return f;
    }

    /*****************************************************************************************/
    // adjacent_find
    // 找出第一对匹配的相邻元素，缺省使用 operator== 比较，如果找到返回一个迭代器，指向这对元素的第一个元素
    /*****************************************************************************************/
    template<class ForwardedIter>
    ForwardedIter adiacent_find(ForwardedIter first , ForwardedIter last)
    {
        if(first == last)
            return last;
        auto next = first;
        while(++next != last)
        {
            if(*first == *next)
                return first;
        }
        return last;
    }

    // 重载版本使用函数对象 comp 代替比较操作
    template<class ForwardedIter , class Compared>
    ForwardedIter adiacent_find(ForwardedIter first , ForwardedIter last , Compared comp)
    {
        if(first == last)
            return last;
        auto next = first;
        while(++next != last)
        {
            if(comp(*first == *next))
                return first;
            first = next;
        }
        return last;
    }
    /*****************************************************************************************/
    // lower_bound
    // 在[first, last)中查找第一个不小于 value 的元素，并返回指向它的迭代器，若没有则返回 last
    /*****************************************************************************************/
    template<class ForwardedIter , class T>
    ForwardedIter lower_bound(ForwardedIter first , ForwardedIter last , const T& value , forward_iterator_tag)
    {
        auto len = mystl::distance(first , last);
        auto half = len;
        ForwardedIter middle;
        while(len > 0)
        {
            half = len >> 1;
            middle = first;
            mystl::advance(middle , half);
            if(*middle < value)
            {
                first = middle;
                first++;
                len = len - half - 1;
            }
            else
            {
                len = half;
            }
        }
        return half;
    }

    // lbound_dispatch 的 random_access_iterator_tag 版本
    template <class RandomIter, class T>
    RandomIter
    lbound_dispatch(RandomIter first, RandomIter last,
                    const T& value, random_access_iterator_tag)
    {
        auto len = last - first;
        auto half = len;
        RandomIter middle;
        while (len > 0)
        {
            half = len >> 1;
            middle = first + half;
            if (*middle < value)
            {
                first = middle + 1;
                len = len - half - 1;
            }
            else
            {
                len = half;
            }
        }
        return first;
    }

    template <class ForwardIter, class T>
    ForwardIter
    lower_bound(ForwardIter first, ForwardIter last, const T& value)
    {
        return mystl::lbound_dispatch(first, last, value, iterator_category(first));
    }

    // 重载版本使用函数对象 comp 代替比较操作
    // lbound_dispatch 的 forward_iterator_tag 版本
    template <class ForwardIter, class T, class Compared>
    ForwardIter
    lbound_dispatch(ForwardIter first, ForwardIter last,
                    const T& value, forward_iterator_tag, Compared comp)
    {
        auto len = mystl::distance(first, last);
        auto half = len;
        ForwardIter middle;
        while (len > 0)
        {
            half = len >> 1;
            middle = first;
            mystl::advance(middle, half);
            if (comp(*middle, value))
            {
                first = middle;
                ++first;
                len = len - half - 1;
            }
            else
            {
                len = half;
            }
        }
        return first;
    }

    // lbound_dispatch 的 random_access_iterator_tag 版本
    template <class RandomIter, class T, class Compared>
    RandomIter
    lbound_dispatch(RandomIter first, RandomIter last,
                    const T& value, random_access_iterator_tag, Compared comp)
    {
        auto len = last - first;
        auto half = len;
        RandomIter middle;
        while (len > 0)
        {
            half = len >> 1;
            middle = first + half;
            if (comp(*middle, value))
            {
                first = middle + 1;
                len = len - half - 1;
            }
            else
            {
                len = half;
            }
        }
        return first;
    }

    template <class ForwardIter, class T, class Compared>
    ForwardIter
    lower_bound(ForwardIter first, ForwardIter last, const T& value, Compared comp)
    {
        return mystl::lbound_dispatch(first, last, value, iterator_category(first), comp);
    }

    /*****************************************************************************************/
    // upper_bound
    // 在[first, last)中查找第一个大于value 的元素，并返回指向它的迭代器，若没有则返回 last
    /*****************************************************************************************/
    // ubound_dispatch 的 forward_iterator_tag 版本
    template <class ForwardIter, class T>
    ForwardIter
    ubound_dispatch(ForwardIter first, ForwardIter last,
                    const T& value, forward_iterator_tag)
    {
        auto len = mystl::distance(first, last);
        auto half = len;
        ForwardIter middle;
        while (len > 0)
        {
            half = len >> 1;
            middle = first;
            mystl::advance(middle, half);
            if (value < *middle)
            {
                len = half;
            }
            else
            {
                first = middle;
                ++first;
                len = len - half - 1;
            }
        }
        return first;
    }

    // ubound_dispatch 的 random_access_iterator_tag 版本
    template <class RandomIter, class T>
    RandomIter
    ubound_dispatch(RandomIter first, RandomIter last,
                    const T& value, random_access_iterator_tag)
    {
        auto len = last - first;
        auto half = len;
        RandomIter middle;
        while (len > 0)
        {
            half = len >> 1;
            middle = first + half;
            if (value < *middle)
            {
                len = half;
            }
            else
            {
                first = middle + 1;
                len = len - half - 1;
            }
        }
        return first;
    }

    template <class ForwardIter, class T>
    ForwardIter
    upper_bound(ForwardIter first, ForwardIter last, const T& value)
    {
        return mystl::ubound_dispatch(first, last, value, iterator_category(first));
    }

    // 重载版本使用函数对象 comp 代替比较操作
    // ubound_dispatch 的 forward_iterator_tag 版本
    template <class ForwardIter, class T, class Compared>
    ForwardIter
    ubound_dispatch(ForwardIter first, ForwardIter last,
                    const T& value, forward_iterator_tag, Compared comp)
    {
        auto len = mystl::distance(first, last);
        auto half = len;
        ForwardIter middle;
        while (len > 0)
        {
            half = len >> 1;
            middle = first;
            mystl::advance(middle, half);
            if (comp(value, *middle))
            {
                len = half;
            }
            else
            {
                first = middle;
                ++first;
                len = len - half - 1;
            }
        }
        return first;
    }

    // ubound_dispatch 的 random_access_iterator_tag 版本
    template <class RandomIter, class T, class Compared>
    RandomIter
    ubound_dispatch(RandomIter first, RandomIter last,
                    const T& value, random_access_iterator_tag, Compared comp)
    {
        auto len = last - first;
        auto half = len;
        RandomIter middle;
        while (len > 0)
        {
            half = len >> 1;
            middle = first + half;
            if (comp(value, *middle))
            {
                len = half;
            }
            else
            {
                first = middle + 1;
                len = len - half - 1;
            }
        }
        return first;
    }

    template <class ForwardIter, class T, class Compared>
    ForwardIter
    upper_bound(ForwardIter first, ForwardIter last, const T& value, Compared comp)
    {
        return mystl::ubound_dispatch(first, last, value, iterator_category(first), comp);
    }


}

#endif