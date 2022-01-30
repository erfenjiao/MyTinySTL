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
    
    */

}

#endif