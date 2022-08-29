/*************************************************************************
	> File Name: algobase.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Tue 02 Aug 2022 08:31:04 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_ALGOBASE_H__
#define LEPTSTL_ALGOBASE_H__ 

/* 此头文件包含leptstl基本算法*/

#include <cstring>

#include "iterator.h"
#include "util.h"

namespace leptstl 
{
#ifdef max 
#pragma message("#undefing marco max")
#undef max 
#endif 

#ifdef min 
#pragma message("#undefing marco min")
#undef min 
#endif 

    /*********************************************************************/
    template<typename T>
        const T& max(const T& lhs, const T& rhs)
        {
            return lhs < rhs ? rhs : lhs;
        }
    template<typename T, typename Compare>
        const T& max(const T& lhs, const T& rhs, Compare comp)
        {
            return comp(lhs, rhs) ? rhs : lhs;
        }

    template<typename T>
        const T& min(const T& lhs, const T& rhs)
        {
            return rhs < lhs ? rhs : lhs;
        }
    template<typename T, typename Compare>
        const T& min(const T& lhs, const T& rhs, Compare comp)
        {
            return comp(rhs, lhs) ? rhs : lhs;
        }

    /*************************************************************************/
    /* iter_swap 将两个迭代器所指对象对调*/
    template<typename FIter1, typename FIter2>
        void iter_swap(FIter1 lhs, FIter2 rhs)
        {
            leptstl::swap(*lhs, *rhs);
        }

    /***********************************************************************/
    /* copy 将[first,last]区间元素拷贝到[result,result+(last-first)]内*/
    template<typename InputIter, typename OutputIter>
        OutputIter unchecked_copy_cat(InputIter first, InputIter last, OutputIter result, 
                                      leptstl::input_iterator_tag)
        {
            for(; first != last; ++first, ++result)
                *result = *first;
            return result;
        }

    template<typename RandomIter, typename OutputIter>
        OutputIter unchecked_copy_cat(RandomIter first, RandomIter last, OutputIter result, 
                                      leptstl::random_access_iterator_tag)
        {
            for(auto n = last - first; n > 0; --n, ++first, ++result)
                *result = *first;
            return result;
        }

    template<typename InputIter, typename OutputIter>
        OutputIter unchecked_copy(InputIter first, InputIter last, OutputIter result)
        {
            return unchecked_copy_cat(first, last, result, iterator_category(first));
        }

    /*为trivially_copy_assignable 类型提供特化版本*/
    template<typename T, typename U>
        typename std::enable_if<
        std::is_same<typename std::remove_const<T>::type, U>::value &&
        std::is_trivially_copy_assignable<U>::value, 
        U*>::type 
            unchecked_copy(T* first, T* last, U* result)
            {
                const auto n = static_cast<size_t>(last - first);
                if(n != 0)
                    std::memmove(result, first, n*sizeof(U));
                return result + n;
            }

    template<typename InputIter, typename OutputIter>
        OutputIter copy(InputIter first, InputIter last, OutputIter result)
        {
            return unchecked_copy(first, last, result);
        }

    /***************************************************************************/
    /* copy_backward 将[first, last]区间内的元素拷贝到[result-(last-first)，result]内*/
    template<typename BidirectionalIter1, typename BidirectionalIter2>
        BidirectionalIter2 
        unchecked_copy_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
                                    BidirectionalIter2 result, leptstl::bidirectional_iterator_tag)
        {
            while(first != last)
                *--result = *--last;
            return result;
        }

    template<typename RandomIter1, typename RandomIter2>
        RandomIter2 
        unchecked_copy_backward_cat(RandomIter1 first, RandomIter1 last,
                                    RandomIter2 result, leptstl::random_access_iterator_tag)
        {
            for(auto n = last - first; n > 0; --n)
                *--result = *--last;
            return result;
        }

    template<typename BidirectionalIter1, typename BidirectionalIter2>
        BidirectionalIter2 
        unchecked_copy_backward(BidirectionalIter1 first, BidirectionalIter1 last,
                                BidirectionalIter2 result)
        {
            return unchecked_copy_backward_cat(first, last, result, iterator_category(first));
        }

    /*为trivially_copy_assignable 类型提供特化版本*/
    template<typename T, typename U>
        typename std::enable_if<
        std::is_same<typename std::remove_const<T>::type, U>::value &&
        std::is_trivially_copy_assignable<U>::value, 
        U*>::type 
            unchecked_copy_backward(T* first, T* last, U* result)
            {
                const auto n = static_cast<size_t>(last - first);
                if(n != 0)
                {
                    result -= n;
                    std::memmove(result, first, n*sizeof(U));
                }
                return result;
            }

    template<typename BidirectionalIter1, typename BidirectionalIter2>
        BidirectionalIter2 
        copy_backward(BidirectionalIter1 first, BidirectionalIter1 last, 
                      BidirectionalIter2 result)
        {
            return unchecked_copy_backward(first, last, result);
        }

    /*************************************************************************/
    /*copy_if 把[first,last)内满足医院操作unary_pred的元素拷贝到result为起始的位置上*/
    template<typename InputIter, typename OutputIter, typename UnaryPredicate>
        OutputIter 
        copy_if(InputIter first, InputIter last, OutputIter result, 
                UnaryPredicate unary_pred)
        {
            for(; first != last; ++first)
            {
                if(unary_pred(*first))
                    *result++ = *first;
            }
            return result;
        }

    /*copy_n 把[first,first+n)的元素拷贝到[result,result+n]的位置上*/
    template<typename InputIter, typename Size, typename OutputIter>
        leptstl::pair<InputIter, OutputIter>
        unchecked_copy_n(InputIter first, Size n, OutputIter result, 
                         leptstl::input_iterator_tag)
        {
            for(; n > 0; --n, ++first, ++result)
            {
                *result = *first;
            }
            return leptstl::pair<InputIter, OutputIter>(first, result);
        }

    template<typename RandomIter, typename Size, typename OutputIter>
        leptstl::pair<RandomIter, OutputIter>
        unchecked_copy_n(RandomIter first, Size n, OutputIter result, 
                         leptstl::random_access_iterator_tag)
        {
            auto last = first + n;
            return leptstl::pair<RandomIter, OutputIter>(last, leptstl::copy(first, last, result));
        }

    template<typename InputIter, typename Size, typename OutputIter>
        leptstl::pair<InputIter, OutputIter>
        copy_n(InputIter first, Size n, OutputIter result)
        {
            return unchecked_copy_n(first, n, result, iterator_category(first));
        }

    /*****************************************************************************/
    /* move 把[first,last)区间内的元素移动到[result,result+(last-first))内*/
    template<typename InputIter, typename OutputIter>
        OutputIter 
        unchecked_move_cat(InputIter first, InputIter last, OutputIter result, 
                           leptstl::input_iterator_tag)
        {
            for(; first != last; ++first, ++result)
            {
                *result = leptstl::move(*first);
            }
            return result;
        }

    template<typename RandomIter, typename OutputIter>
        OutputIter 
        unchecked_move_cat(RandomIter first, RandomIter last, OutputIter result, 
                           leptstl::random_access_iterator_tag)
        {
            for(auto n = last - first; n > 0; --n, ++first, ++result)
            {
                *result = leptstl::move(*first);
            }
            return result;
        }

    template<typename InputIter, typename OutputIter>
        OutputIter 
        unchecked_move(InputIter first, InputIter last, OutputIter result)
        {
            return unchecked_move_cat(first, last, result, iterator_category(first));
        }

    /* 为trivially_move_assignable类型提供特化版本*/
    template<typename T, typename U>
        typename std::enable_if<
        std::is_same<typename std::remove_const<T>::type, U>::value &&
        std::is_trivially_move_assignable<U>::value,
        U*>::type 
            unchecked_move(T* first, T* last, U* result)
            {
                const size_t n = static_cast<size_t>(last - first);
                if(n != 0)
                    std::memmove(result, first, n*sizeof(U));
                return result + n;
            }

    template<typename InputIter, typename OutputIter>
        OutputIter move(InputIter first, InputIter last, OutputIter result)
        {
            return unchecked_move(first, last, result);
        }

    /**********************************************************************************/
    /* move_backward 将[first,last)区间内的元素移动到[result-(last-first),result)内*/
    template<typename BidirectionalIter1, typename BidirectionalIter2>
        BidirectionalIter2 
        unchecked_move_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
                                    BidirectionalIter2 result, leptstl::bidirectional_iterator_tag)
        {
            while(first != last)
                *--result = leptstl::move(*--last);
            return result;
        }

    template<typename RandomIter1, typename RandomIter2>
        RandomIter2 
        unchecked_move_backward_cat(RandomIter1 first, RandomIter1 last,
                                    RandomIter2 result, leptstl::random_access_iterator_tag)
        {
            for(auto n = last - first; n > 0; --n)
                *--result = leptstl::move(*--last);
            return result;
        }

    template<typename BidirectionalIter1, typename BidirectionalIter2>
        BidirectionalIter2 
        unchecked_move_backward(BidirectionalIter1 first, BidirectionalIter1 last, 
                                BidirectionalIter2 result)
        {
            return unchecked_move_backward_cat(first, last,result, iterator_category(first));
        }

    /* 为trivially_move_assignable类型提供特化版本*/
    template<typename T, typename U>
        typename std::enable_if<
        std::is_same<typename std::remove_const<T>::type, U>::value &&
        std::is_trivially_move_assignable<U>::value,
        U*>::type 
            unchecked_move_backward(T* first, T* last, U* result)
            {
                const size_t n = static_cast<size_t>(last - first);
                if(n != 0)
                {
                    result -= n;
                    std::memmove(result, first, n*sizeof(U));
                }
                return result;
            }

    template<typename InputIter, typename OutputIter>
        OutputIter move_backward(InputIter first, InputIter last, OutputIter result)
        {
            return unchecked_move_backward(first, last, result);
        }

    /************************************************************************************/
    /* equal 比较第一序列在[first,last)区间上的元素值是否和第二序列的相等*/
    template<typename InputIter1, typename InputIter2>
        bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2)
        {
            for(; first1 != last1; ++first1, ++first2)
            {
                if(*first1 != *first2)
                    return false;
            }
            return true;
        }

    template<typename InputIter1, typename InputIter2, typename Compared>
        bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2, 
                   Compared comp)
        {
            for(; first1 != last1; ++first1, ++first2)
            {
                if(!comp(*first1,*first2))
                    return false;
            }
            return true;
        }

    /*************************************************************************************/
    /* fill_n 从first位置开始填充n个值*/
    template<typename OutputIter, typename Size, typename T>
        OutputIter unchecked_fill_n(OutputIter first, Size n, const T& value)
        {
            for(; n > 0; --n, ++first)
            {
                *first = value;
            }
            return first;
        }

    template<typename T, typename Size, typename U>
        typename std::enable_if<
        std::is_integral<T>::value && sizeof(T) == 1 &&
        !std::is_same<T, bool>::value &&
        std::is_integral<U>::value && sizeof(U) == 1,
        T*>::type 
        unchecked_fill_n(T* first, Size n, U value)
        {
            if(n > 0)
            {
                std::memset(first, (unsigned char)value, (size_t)(n));
            }
            return first + n;
        }

    template<typename OutputIter, typename Size, typename T>
        OutputIter fill_n(OutputIter first, Size n, const T& value)
        {
            return unchecked_fill_n(first, n, value);
        }

    /**********************************************************************************/
    /* fill 为[first,last)区间内的所有元素填充新值*/
    template<typename ForwardIter, typename T>
        void fill_cat(ForwardIter first, ForwardIter last, const T& value, leptstl::forward_iterator_tag)
        {
            for(; first != last; ++first)
            {
                *first = value;
            }
        }

    template<typename RandomIter, typename T>
        void fill_cat(RandomIter first, RandomIter last, const T& value, leptstl::random_access_iterator_tag)
        {
            fill_n(first, last - first, value);
        }

    template<typename ForwardIter, typename T>
        void fill(ForwardIter first, ForwardIter last, const T& value)
        {
            fill_cat(first, last, value, iterator_category(first));
        }

    /****************************************************************************************/
    /* lexicographical_compare 以字典序对两序列进行比较*/
    template<typename InputIter1, typename InputIter2>
        bool lexicographical_compare(InputIter1 first1, InputIter1 last1,
                                    InputIter2 first2, InputIter2 last2)
        {
            for(; first1 != last1 && first2 != last2; ++first1, ++first2)
            {
                if(*first1 < *first2)
                    return true;
                if(*first2 < * first1)
                    return false;
            }
            return first1 == last1 && first2 != last2;
        }

    template<typename InputIter1, typename InputIter2, typename Compared>
        bool lexicographical_compare(InputIter1 first1, InputIter1 last1,
                                    InputIter2 first2, InputIter2 last2, Compared comp)
        {
            for(; first1 != last1 && first2 != last2; ++first1, ++first2)
            {
                if(comp(*first1, *first2))
                    return true;
                if(comp(*first2, *first1))
                    return false;
            }
            return first1 == last1 && first2 != last2;
        }

    /*针对const unsigned char* 特化版*/
    bool lexicographical_compare(const unsigned char* first1,
                                 const unsigned char* last1,
                                 const unsigned char* first2,
                                 const unsigned char* last2)
    {
        const auto len1 = last1 - first1;
        const auto len2 = last2 - first2;
        const auto result = std::memcmp(first1, first2, leptstl::min(len1, len2));
        return result != 0 ? result < 0 : len1 < len2;
    }

    /****************************************************************************************/
    /*mismatch 平行比较两个序列，找到第一个失配元素，返回一对迭代器，分别指向两个序列中失配的元素**/
    template<typename InputIter1, typename InputIter2>
        leptstl::pair<InputIter1, InputIter2>
        mismatch(InputIter1 first1, InputIter1 last1, InputIter2 first2)
        {
            while(first1 != last1 && *first1 == *first2)
            {
                ++first1;
                ++first2;
            }
            return leptstl::pair<InputIter1, InputIter2>(first1, first2);
        }

    template<typename InputIter1, typename InputIter2, typename Compared>
        leptstl::pair<InputIter1, InputIter2>
        mismatch(InputIter1 first1, InputIter1 last1, InputIter2 first2, Compared comp)
        {
            while(first1 != last1 && comp(*first1, *first2))
            {
                ++first1;
                ++first2;
            }
            return leptstl::pair<InputIter1, InputIter2>(first1, first2);
        }

}   /* namespace leptstl */

#endif  /* LEPTSTL_ALGOBASE_H__ */

