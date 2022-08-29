/*************************************************************************
	> File Name: algo.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Sat 06 Aug 2022 09:14:36 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_ALGO_H__
#define LEPTSTL_ALGO_H__ 

/*此头文件包含leptstl一系列算法*/

#include <cstddef>
#include <ctime>

#include "algobase.h"
#include "memory.h"
#include "heap_algo.h"
#include "functional.h"

namespace leptstl 
{
    /*all_of 检查[first,last)内的元素是否全部满足一元操作为true的情况*/
    template<typename InputIter, typename UnaryPred>
        bool all_of(InputIter first, InputIter last, UnaryPred unary_pred)
        {
            for(; first != last; ++first)
            {
                if(!unary_pred(*first))
                    return false;
            }
            return true;
        }

    /******************************************************************************/
    /*any_of*/
    template<typename InputIter, typename UnaryPred>
        bool any_of(InputIter first, InputIter last, UnaryPred unary_pred)
        {
            for(; first != last; ++first)
            {
                if(unary_pred(*first))
                    return true;
            }
            return false;
        }

    /******************************************************************************/
    /*none_of*/
    template<typename InputIter, typename UnaryPred>
        bool none_of(InputIter first, InputIter last, UnaryPred unary_pred)
        {
            for(; first != last; ++first)
            {
                if(unary_pred(*first))
                    return false;
            }
            return true;
        }

    /******************************************************************************/
    /*count 对区间的元素与给定值比较，返回元素相等的个数*/
    template<typename InputIter, typename T>
        size_t count(InputIter first, InputIter last, const T& value)
        {
            size_t n = 0;
            for(; first != last; ++first)
            {
                if(*first == value)
                    ++n;
            }
            return n;
        }

    /******************************************************************************/
    /*count_if 对区间的元素进行一元操作，返回结果为true的个数*/
    template<typename InputIter, typename UnaryPred>
        size_t count_if(InputIter first, InputIter last, UnaryPred unary_pred)
        {
            size_t n = 0;
            for(; first != last; ++first)
            {
                if(unary_pred(*first))
                    ++n;
            }
            return n;
        }

    /******************************************************************************/
    /*find 找到区间等于value的元素，返回指向该元素的迭代器*/
    template<typename InputIter, typename T>
        InputIter find(InputIter first, InputIter last, const T& value)
        {
            while(first != last && *first != value)
                ++first;
            return first;
        }

    /******************************************************************************/
    /*find_if 找到区间等于value的元素，返回指向该元素的迭代器*/
    template<typename InputIter, typename UnaryPred>
        InputIter find_if(InputIter first, InputIter last, UnaryPred unary_pred)
        {
            while(first != last && !unary_pred(*first))
                ++first;
            return first;
        }

    /******************************************************************************/
    /*find_if_not 找到区间不等于value的元素，返回指向该元素的迭代器*/
    template<typename InputIter, typename UnaryPred>
        InputIter find_if_not(InputIter first, InputIter last, UnaryPred unary_pred)
        {
            while(first != last && unary_pred(*first))
                ++first;
            return first;
        }

    /*******************************************************************************/
    /*search 在[first,last)中查找[first2,last2)的首次出现点*/
    template<typename ForwardIter1, typename ForwardIter2>
        ForwardIter1 search(ForwardIter1 first1, ForwardIter1 last1,
                            ForwardIter2 first2, ForwardIter2 last2)
        {
            auto d1 = leptstl::distance(first1, last1);
            auto d2 = leptstl::distance(first2, last2);
            if(d1 < d2)
                return last1;
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
                    if(d1 == d2)
                        return last1;
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

    /*******************************************************************************/
    /*search 在[first,last)中查找[first2,last2)的首次出现点 使用comp*/
    template<typename ForwardIter1, typename ForwardIter2, typename Compared>
        ForwardIter1 search(ForwardIter1 first1, ForwardIter1 last1,
                            ForwardIter2 first2, ForwardIter2 last2, Compared comp)
        {
            auto d1 = leptstl::distance(first1, last1);
            auto d2 = leptstl::distance(first2, last2);
            if(d1 < d2)
                return last1;
            auto current1 = first1;
            auto current2 = first2;
            while(current2 != last2)
            {
                if(comp(*current1, *current2))
                {
                    ++current1;
                    ++current2;
                }
                else 
                {
                    if(d1 == d2)
                        return last1;
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

    /****************************************************************************/
    /*search_n 在[first,last)中查找连续n个value所形成的子序列*/
    template<typename ForwardIter, typename Size, typename T>
        ForwardIter search_n(ForwardIter first, ForwardIter last, Size n, const T& value)
        {
            if(n <= 0)
                return first;
            else 
            {
                first = leptstl::find(first, last, value);
                while(first != last)
                {
                    auto m = n - 1;
                    auto i = first;
                    ++i;
                    while(i != last && m != 0 && *i == value)
                    {
                        ++i;
                        --m;
                    }
                    if(m == 0)
                        return first;
                    else 
                        first = leptstl::find(i, last, value);
                }
                return last;
            }
        }

    /****************************************************************************/
    /*search_n 在[first,last)中查找连续n个value所形成的子序列 使用comp*/
    template<typename ForwardIter, typename Size, typename T, typename  Compared>
        ForwardIter search_n(ForwardIter first, ForwardIter last, Size n, const T& value, Compared comp)
        {
            if(n <= 0)
                return first;
            else 
            {
                while(first != last)
                {
                    if(comp(*first, value))
                        break;
                    ++first;
                }
                while(first != last)
                {
                    auto m = n - 1;
                    auto i = first;
                    ++i;
                    while(i != last && m != 0 && comp(*i, value))
                    {
                        ++i;
                        --m;
                    }
                    if(m == 0)
                        return first;
                    else 
                    {
                        while(i != last)
                        {
                            if(comp(*i, value))
                                break;
                            ++i;
                        }
                        first = i;
                    }
                }
                return last;
            }
        }

    /*************************************************************************************/
    /* find_end 在[first1,last1)中查找[first2,last2)最后一次出现的地方，若不存在返回last1*/
    template <typename ForwardIter1, typename ForwardIter2>
        ForwardIter1
        find_end_dispatch(ForwardIter1 first1, ForwardIter1 last1,
                  ForwardIter2 first2, ForwardIter2 last2,
                  forward_iterator_tag, forward_iterator_tag)
        {
            if(first2 == last2)
                return last1;
            else 
            {
                auto result = last1;
                while(true)
                {
                    auto new_result = leptstl::search(first1, last1, first2, last2);
                    if(new_result == last1)
                        return result;
                    else 
                    {
                        result = new_result;
                        first1 = new_result;
                        ++first1;
                    }
                }
            }
        }

    template<typename BidirectionalIter1, typename BidirectionalIter2>
        BidirectionalIter1 
        find_end_dispatch(BidirectionalIter1 first1, BidirectionalIter1 last1,
                          BidirectionalIter2 first2, BidirectionalIter2 last2,
                          bidirectional_iterator_tag, bidirectional_iterator_tag)
        {
            typedef reverse_iterator<BidirectionalIter1> reviter1;
            typedef reverse_iterator<BidirectionalIter2> reviter2;
            reviter1 rlast1(first1);
            reviter2 rlast2(first2);
            reviter1 rresult = leptstl::search(reviter1(last1),rlast1, reviter2(last2), rlast2);
            if(rresult == rlast1)
            {
                return last1;
            }
            else 
            {
                auto result = rresult.base();
                leptstl::advance(result, -leptstl::distance(first2, last2));
                return result;
            }
        }

    template<typename ForwardIter1, typename ForwardIter2>
        ForwardIter1 
        find_end(ForwardIter1 first1, ForwardIter1 last1,
                 ForwardIter2 first2, ForwardIter2 last2)
        {
            typedef typename iterator_traits<ForwardIter1>::iterator_category Category1;
            typedef typename iterator_traits<ForwardIter2>::iterator_category Category2;
            return leptstl::find_end_dispatch(first1, last1, first2, last2, Category1(), Category2());
        }

    /*************************************************************************************/
    /*使用comp*/
    /* find_end 在[first1,last1)中查找[first2,last2)最后一次出现的地方，若不存在返回last1*/
    template <typename ForwardIter1, typename ForwardIter2, typename Compared>
        ForwardIter1
        find_end_dispatch(ForwardIter1 first1, ForwardIter1 last1,
                  ForwardIter2 first2, ForwardIter2 last2,
                  forward_iterator_tag, forward_iterator_tag, Compared comp)
        {
            if(first2 == last2)
                return last1;
            else 
            {
                auto result = last1;
                while(true)
                {
                    auto new_result = leptstl::search(first1, last1, first2, last2, comp);
                    if(new_result == last1)
                        return result;
                    else 
                    {
                        result = new_result;
                        first1 = new_result;
                        ++first1;
                    }
                }
            }
        }

    template<typename BidirectionalIter1, typename BidirectionalIter2, typename Compared>
        BidirectionalIter1 
        find_end_dispatch(BidirectionalIter1 first1, BidirectionalIter1 last1,
                          BidirectionalIter2 first2, BidirectionalIter2 last2,
                          bidirectional_iterator_tag, bidirectional_iterator_tag, Compared comp)
        {
            typedef reverse_iterator<BidirectionalIter1> reviter1;
            typedef reverse_iterator<BidirectionalIter2> reviter2;
            reviter1 rlast1(first1);
            reviter2 rlast2(first2);
            reviter1 rresult = leptstl::search(reviter1(last1),rlast1, reviter2(last2), rlast2, comp);
            if(rresult == rlast1)
            {
                return last1;
            }
            else 
            {
                auto result = rresult.base();
                leptstl::advance(result, -leptstl::distance(first2, last2));
                return result;
            }
        }

    template<typename ForwardIter1, typename ForwardIter2, typename Compared>
        ForwardIter1 
        find_end(ForwardIter1 first1, ForwardIter1 last1,
                 ForwardIter2 first2, ForwardIter2 last2, Compared comp)
        {
            typedef typename iterator_traits<ForwardIter1>::iterator_category Category1;
            typedef typename iterator_traits<ForwardIter2>::iterator_category Category2;
            return leptstl::find_end_dispatch(first1, last1, first2, last2, Category1(), Category2(), comp);
        }

    /*******************************************************************************/
    /* find_first_of */
    template<typename InputIter, typename ForwardIter>
        InputIter 
        find_first_of(InputIter first1, InputIter last1,
                      ForwardIter first2, ForwardIter last2)
        {
            for(; first1 != last1; ++first1)
            {
                for(auto iter = first2; iter != last2; ++iter)
                {
                    if(*first1 == *iter)
                        return first1;
                }
            }
            return last1;
        }

    /* find_first_of  Compared*/
    template<typename InputIter, typename ForwardIter, typename Compared>
        InputIter 
        find_first_of(InputIter first1, InputIter last1,
                      ForwardIter first2, ForwardIter last2, Compared comp)
        {
            for(; first1 != last1; ++first1)
            {
                for(auto iter = first2; iter != last2; ++iter)
                {
                    if(comp(*first1, *iter))
                        return first1;
                }
            }
            return last1;
        }

    /************************************************************************************/
    /*for_each 使用一个函数对象对区间每个元素执行operator()操作，但不能改变元素内容*/
    template<typename InputIter, typename Function>
        Function for_each(InputIter first, InputIter last, Function func)
        {
            for(; first != last; ++first)
                func(*first);
            return func;
        }

    /*************************************************************************************/
    /* adjacent_find 找出第一对匹配的相邻元素*/
    template<typename ForwardIter>
        ForwardIter adjacent_find(ForwardIter first, ForwardIter last)
        {
            if(first == last)
                return last;
            auto next = first;
            while(++next != last)
            {
                if(*first == *next)
                    return first;
                first = next;
            }
            return last;
        }

    /*************************************************************************************/
    /* adjacent_find 找出第一对匹配的相邻元素, Compared*/
    template<typename ForwardIter, typename Compared>
        ForwardIter adjacent_find(ForwardIter first, ForwardIter last, Compared comp)
        {
            if(first == last)
                return last;
            auto next = first;
            while(++next != last)
            {
                if(comp(*first, *next))
                    return first;
                first = next;
            }
            return last;
        }

    /***********************************************************************************/
    /* lower_bound */
    template<typename ForwardIter, typename T>
        ForwardIter lbound_dispatch(ForwardIter first, ForwardIter last, const T& value, forward_iterator_tag)
        {
            auto len = leptstl::distance(first, last);
            auto half = len;
            ForwardIter mid;
            while(len > 0)
            {
                half = len >> 1;
                mid = first;
                leptstl::advance(mid, half);
                if(*mid < value)
                {
                    first = mid;
                    ++first;
                    len = len - half - 1;
                }
                else 
                    len = half;
            }
            return first;
        }

    /* lower_bound */
    template<typename RandomIter, typename T>
        RandomIter lbound_dispatch(RandomIter first, RandomIter last, const T& value, random_access_iterator_tag)
        {
            auto len = last - first;
            auto half = len;
            RandomIter mid;
            while(len > 0)
            {
                half = len >> 1;
                mid = first + half;
                if(*mid < value)
                {
                    first = mid + 1;
                    len = len - half - 1;
                }
                else 
                    len = half;
            }
            return first;
        }

    template<typename ForwardIter, typename T>
        ForwardIter lower_bound(ForwardIter first, ForwardIter last, const T& value)
        {
            return leptstl::lbound_dispatch(first, last, value, iterator_category(first));
        }

    /***********************************************************************************/
    /* comp*/
    /* lower_bound */
    template<typename ForwardIter, typename T, typename Compared>
        ForwardIter lbound_dispatch(ForwardIter first, ForwardIter last, const T& value, forward_iterator_tag, Compared comp)
        {
            auto len = leptstl::distance(first, last);
            auto half = len;
            ForwardIter mid;
            while(len > 0)
            {
                half = len >> 1;
                mid = first;
                leptstl::advance(mid, half);
                if(comp(*mid, value))
                {
                    first = mid;
                    ++first;
                    len = len - half - 1;
                }
                else 
                    len = half;
            }
            return first;
        }

    /* lower_bound */
    template<typename RandomIter, typename T, typename Compared>
        RandomIter lbound_dispatch(RandomIter first, RandomIter last, const T& value, random_access_iterator_tag, Compared comp)
        {
            auto len = last - first;
            auto half = len;
            RandomIter mid;
            while(len > 0)
            {
                half = len >> 1;
                mid = first + half;
                if(comp(*mid, value))
                {
                    first = mid + 1;
                    len = len - half - 1;
                }
                else 
                    len = half;
            }
            return first;
        }

    template<typename ForwardIter, typename T, typename Compared>
        ForwardIter lower_bound(ForwardIter first, ForwardIter last, const T& value, Compared comp)
        {
            return leptstl::lbound_dispatch(first, last, value, iterator_category(first), comp);
        }
    
    /***********************************************************************************/
    /* upper_bound */
    template<typename ForwardIter, typename T>
        ForwardIter ubound_dispatch(ForwardIter first, ForwardIter last, const T& value, forward_iterator_tag)
        {
            auto len = leptstl::distance(first, last);
            auto half = len;
            ForwardIter mid;
            while(len > 0)
            {
                half = len >> 1;
                mid = first;
                leptstl::advance(mid, half);
                if(value < *mid)
                {
                    len = half;
                }
                else 
                {
                    first = mid;
                    ++first;
                    len = len - half - 1;
                }
            }
            return first;
        }

    /* upper_bound */
    template<typename RandomIter, typename T>
        RandomIter ubound_dispatch(RandomIter first, RandomIter last, const T& value, random_access_iterator_tag)
        {
            auto len = last - first;
            auto half = len;
            RandomIter mid;
            while(len > 0)
            {
                half = len >> 1;
                mid = first + half;
                if(value < *mid)
                {
                    len = half;
                }
                else 
                {
                    first = mid + 1;
                    len = len - half - 1;
                }
            }
            return first;
        }

    template<typename ForwardIter, typename T>
        ForwardIter upper_bound(ForwardIter first, ForwardIter last, const T& value)
        {
            return leptstl::ubound_dispatch(first, last, value, iterator_category(first));
        }

    /***********************************************************************************/
    /* comp*/
    /* upper_bound */
    template<typename ForwardIter, typename T, typename Compared>
        ForwardIter ubound_dispatch(ForwardIter first, ForwardIter last, const T& value, forward_iterator_tag, Compared comp)
        {
            auto len = leptstl::distance(first, last);
            auto half = len;
            ForwardIter mid;
            while(len > 0)
            {
                half = len >> 1;
                mid = first;
                leptstl::advance(mid, half);
                if(comp(value, *mid))
                {
                    len = half;
                }
                else 
                {
                    first = mid;
                    ++first;
                    len = len - half - 1;
                }
            }
            return first;
        }

    /* upper_bound */
    template<typename RandomIter, typename T, typename Compared>
        RandomIter ubound_dispatch(RandomIter first, RandomIter last, const T& value, random_access_iterator_tag, Compared comp)
        {
            auto len = last - first;
            auto half = len;
            RandomIter mid;
            while(len > 0)
            {
                half = len >> 1;
                mid = first + half;
                if(comp(value, *mid))
                {
                    len = half;
                }
                else 
                {
                    first = mid + 1;
                    len = len - half - 1;
                }
            }
            return first;
        }

    template<typename ForwardIter, typename T, typename Compared>
        ForwardIter upper_bound(ForwardIter first, ForwardIter last, const T& value, Compared comp)
        {
            return leptstl::ubound_dispatch(first, last, value, iterator_category(first), comp);
        }

    /****************************************************************************************/
    /* binary_search */
    template<typename ForwardIter, typename T>
        bool binary_search(ForwardIter first, ForwardIter last, const T& value)
        {
            auto i = leptstl::lower_bound(first, last, value);
            return i != last && !(value < *i);
        }

    /* binary_search Compared*/
    template<typename ForwardIter, typename T, typename Compared>
        bool binary_search(ForwardIter first, ForwardIter last, const T& value, Compared comp)
        {
            auto i = leptstl::lower_bound(first, last, value, comp);
            return i != last && !comp(value, *i);
        }

    /***********************************************************************************/
    /*equal_range 查找[first,last)区间与value相等的元素所形成的区间，返回一对迭代器*/
    /*第一个迭代器指向第一个不小于value的元素，第二个迭代器指向第一个大于value的元素*/
    template<typename ForwardIter, typename T>
        leptstl::pair<ForwardIter, ForwardIter>
        erange_dispatch(ForwardIter first, ForwardIter last, const T& value, forward_iterator_tag)
        {
            auto len = leptstl::distance(first, last);
            auto half = len;
            ForwardIter mid, left, right;
            while(len > 0)
            {
                half = len >> 1;
                mid = first;
                leptstl::advance(mid, half);
                if(*mid < value)
                {
                    first = mid;
                    ++first;
                    len = len - half - 1;
                }
                else if(value < *mid)
                    len = half;
                else 
                {
                    left = leptstl::lower_bound(first, last, value);
                    leptstl::advance(first, len);
                    right = leptstl::upper_bound(++mid, first, value);
                    return leptstl::pair<ForwardIter, ForwardIter>(left, right);
                }
            }
            return leptstl::pair<ForwardIter, ForwardIter>(last, last);
        }

    /*erange_dispatch*/ 
    template<typename RandomIter, typename T>
        leptstl::pair<RandomIter, RandomIter>
        erange_dispatch(RandomIter first, RandomIter last, const T& value, random_access_iterator_tag)
        {
            auto len = last - first;
            auto half = len;
            RandomIter mid, left, right;
            while(len > 0)
            {
                half = len >> 1;
                mid = first + half;
                if(*mid < value)
                {
                    first = mid + 1;
                    len = len - half - 1;
                }
                else if(value < *mid)
                    len = half;
                else 
                {
                    left = leptstl::lower_bound(first, last, value);
                    right = leptstl::upper_bound(++mid, first + len, value);
                    return leptstl::pair<RandomIter, RandomIter>(left, right);
                }
            }
            return leptstl::pair<RandomIter, RandomIter>(last, last);
        }

    template<typename ForwardIter, typename T>
        leptstl::pair<ForwardIter, ForwardIter>
        equal_range(ForwardIter first, ForwardIter last, const T& value)
        {
            return leptstl::erange_dispatch(first, last, value, iterator_category(first));
        }

    /* Compared */
    /*equal_range 查找[first,last)区间与value相等的元素所形成的区间，返回一对迭代器*/
    /*第一个迭代器指向第一个不小于value的元素，第二个迭代器指向第一个大于value的元素*/
    template<typename ForwardIter, typename T, typename Compared>
        leptstl::pair<ForwardIter, ForwardIter>
        erange_dispatch(ForwardIter first, ForwardIter last, const T& value, forward_iterator_tag, Compared comp)
        {
            auto len = leptstl::distance(first, last);
            auto half = len;
            ForwardIter mid, left, right;
            while(len > 0)
            {
                half = len >> 1;
                mid = first;
                leptstl::advance(mid, half);
                if(comp(*mid, value))
                {
                    first = mid;
                    ++first;
                    len = len - half - 1;
                }
                else if(comp(value, *mid))
                    len = half;
                else 
                {
                    left = leptstl::lower_bound(first, last, value, comp);
                    leptstl::advance(first, len);
                    right = leptstl::upper_bound(++mid, first, value, comp);
                    return leptstl::pair<ForwardIter, ForwardIter>(left, right);
                }
            }
            return leptstl::pair<ForwardIter, ForwardIter>(last, last);
        }

    /*erange_dispatch*/ 
    template<typename RandomIter, typename T, typename Compared>
        leptstl::pair<RandomIter, RandomIter>
        erange_dispatch(RandomIter first, RandomIter last, const T& value, random_access_iterator_tag, Compared comp)
        {
            auto len = last - first;
            auto half = len;
            RandomIter mid, left, right;
            while(len > 0)
            {
                half = len >> 1;
                mid = first + half;
                if(comp(*mid, value))
                {
                    first = mid + 1;
                    len = len - half - 1;
                }
                else if(comp(value, *mid))
                    len = half;
                else 
                {
                    left = leptstl::lower_bound(first, last, value, comp);
                    right = leptstl::upper_bound(++mid, first + len, value, comp);
                    return leptstl::pair<RandomIter, RandomIter>(left, right);
                }
            }
            return leptstl::pair<RandomIter, RandomIter>(last, last);
        }

    template<typename ForwardIter, typename T, typename Compared>
        leptstl::pair<ForwardIter, ForwardIter>
        equal_range(ForwardIter first, ForwardIter last, const T& value, Compared comp)
        {
            return leptstl::erange_dispatch(first, last, value, iterator_category(first), comp);
        }

    /*************************************************************************************/
    /* generate 将函数对象gen的运算结果对[first,last)内的每一个元素赋值*/
    template<typename ForwardIter, typename Generator>
        void generate(ForwardIter first, ForwardIter last, Generator gen)
        {
            for(; first != last; ++first)
                *first = gen();
        }

    /*************************************************************************************/
    /* generate_n 将函数对象gen的运算结果对[first之后的的每一个元素赋值*/
    template<typename ForwardIter, typename Size, typename Generator>
        void generate_n(ForwardIter first, Size n, Generator gen)
        {
            for(; n > 0; --n, ++first)
                *first = gen();
        }

    /*************************************************************************************/
    /* includes 判断S1传入的元素是否小于S2传入的元素*/
    template<typename InputIter1, typename InputIter2>
        bool includes(InputIter1 first1, InputIter1 last1,
                      InputIter2 first2, InputIter2 last2)
        {
            while(first1 != last1 && first2 != last2)
            {
                if(*first2 < *first1)
                    return false;
                else if(*first1 < *first2)
                    ++first1;
                else 
                {
                    ++first1;
                    ++first2;
                }
            }
            return first2 == last2;
        }

    /* includes 判断S1传入的元素是否小于S2传入的元素 Compared*/
    template<typename InputIter1, typename InputIter2, typename Compared>
        bool includes(InputIter1 first1, InputIter1 last1,
                      InputIter2 first2, InputIter2 last2, Compared comp)
        {
            while(first1 != last1 && first2 != last2)
            {
                if(comp(*first2, *first1))
                    return false;
                else if(comp(*first1, *first2))
                    ++first1;
                else 
                {
                    ++first1;
                    ++first2;
                }
            }
            return first2 == last2;
        }

    /****************************************************************************************/
    /* is_heap */
    template<typename RandomIter>
        bool is_heap(RandomIter first, RandomIter last)
        {
            auto n = leptstl::distance(first, last);
            auto parent = 0;
            for(auto child = 1; child < n; ++child)
            {
                if(first[parent] < first[child])
                    return false;
                if((child & 1) == 0)
                    ++parent;
            }
            return true;
        }

    /* is_heap Compared*/
    template<typename RandomIter, typename Compared>
        bool is_heap(RandomIter first, RandomIter last, Compared comp)
        {
            auto n = leptstl::distance(first, last);
            auto parent = 0;
            for(auto child = 1; child < n; ++child)
            {
                if(comp(first[parent], first[child]))
                    return false;
                if((child & 1) == 0)
                    ++parent;
            }
            return true;
        }

    /********************************************************************************/
    /* is_sorted */
    template<typename ForwardIter>
        bool is_sorted(ForwardIter first, ForwardIter last)
        {
            if(first == last)
                return true;
            auto next = first;
            ++next;
            for(; next != last; first = next, ++next)
            {
                if(*next < *first)
                    return false;
            }
            return true;
        }

    /* is_sorted Compared*/
    template<typename ForwardIter, typename Compared>
        bool is_sorted(ForwardIter first, ForwardIter last, Compared comp)
        {
            if(first == last)
                return true;
            auto next = first;
            ++next;
            for(; next != last; first = next, ++next)
            {
                if(comp(*next, *first))
                    return false;
            }
            return true;
        }

    /*************************************************************************************/
    /* median 找出三个值的中间值*/
    template<typename T>
        const T& median(const T& left, const T& mid, const T& right)
        {
            if(left < mid)
            {
                if(mid < right)
                    return mid;
                else if(left < right)
                    return right;
                else 
                    return left;
            }
            else if(left < right)
                return left;
            else if(mid < right)
                return right;
            else 
                return mid;
        }

    /* median 找出三个值的中间值 Compared*/
    template<typename T, typename Compared>
        const T& median(const T& left, const T& mid, const T& right, Compared comp)
        {
            if(comp(left, mid))
            {
                if(comp(mid, right))
                    return mid;
                else if(comp(left, right))
                    return right;
                else 
                    return left;
            }
            else if(comp(left, right))
                return left;
            else if(comp(mid, right))
                return right;
            else 
                return mid;
        }

    /*************************************************************************************/
    /* max_element 返回一个迭代器，指向最大元素*/
    template<typename ForwardIter>
        ForwardIter max_element(ForwardIter first, ForwardIter last)
        {
            if(first == last)
                return first;
            auto result = first;
            while(++first != last)
            {
                if(*result < *first)
                    result = first;
            }
            return result;
        }

    /* max_element 返回一个迭代器，指向最大元素 Compared*/
    template<typename ForwardIter, typename Compared>
        ForwardIter max_element(ForwardIter first, ForwardIter last, Compared comp)
        {
            if(first == last)
                return first;
            auto result = first;
            while(++first != last)
            {
                if(comp(*result, *first))
                    result = first;
            }
            return result;
        }

    /* min_element 返回一个迭代器，指向最小元素*/
    template<typename ForwardIter>
        ForwardIter min_element(ForwardIter first, ForwardIter last)
        {
            if(first == last)
                return first;
            auto result = first;
            while(++first != last)
            {
                if(*result > *first)
                    result = first;
            }
            return result;
        }

    /* min_element 返回一个迭代器，指向最大元素 Compared*/
    template<typename ForwardIter, typename Compared>
        ForwardIter min_element(ForwardIter first, ForwardIter last, Compared comp)
        {
            if(first == last)
                return first;
            auto result = first;
            while(++first != last)
            {
                if(comp(*first, *result))
                    result = first;
            }
            return result;
        }

    /*******************************************************************************/
    /* swap_ranges */
    template<typename ForwardIter1, typename ForwardIter2>
        ForwardIter2 swap_ranges(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2)
        {
            for(; first1 != last1; ++first1, ++first2)
                leptstl::iter_swap(first1, first2);
            return first2;
        }

    /********************************************************************************/
    /* transform */
    template<typename InputIter, typename OutputIter, typename UnaryOP>
        OutputIter transform(InputIter first, InputIter last,
                             OutputIter result, UnaryOP unary_op)
        {
            for(; first != last; ++first, ++result)
                *result = unary_op(*first);
            return result;
        }

    /* transform */
    template<typename InputIter1, typename InputIter2, typename OutputIter, typename BinaryOP>
        OutputIter transform(InputIter1 first1, InputIter1 last1, 
                             InputIter2 first2, OutputIter result, BinaryOP binary_op)
        {
            for(; first1 != last1; ++first1, ++first2, ++result)
                *result = binary_op(*first1, *first2);
            return result;
        }

    /**********************************************************************/
    /* remove_copy */
    template<typename InputIter, typename OutputIter, typename T>
        OutputIter remove_copy(InputIter first, InputIter last, OutputIter result, const T& value)
        {
            for(; first != last; ++first)
            {
                if(*first != value)
                    *result++ = *first;
            }
            return result;
        }

    /**********************************************************************/
    /* remove_copy_if */
    template<typename InputIter, typename OutputIter, typename UnaryPred>
        OutputIter remove_copy_if(InputIter first, InputIter last, OutputIter result, UnaryPred unary_pred)
        {
            for(; first != last; ++first)
            {
                if(!unary_pred(*first))
                    *result++ = *first;
            }
            return result;
        }

    /*********************************************************************************/
    /* remove */
    template<typename ForwardIter, typename T>
        ForwardIter remove(ForwardIter first, ForwardIter last, const T& value)
        {
            first = leptstl::find(first, last, value);
            auto next = first;
            return first == last ? first : leptstl::remove_copy(++next, last, first, value);
        }

    /*********************************************************************************/
    /* remove_if */
    template<typename ForwardIter, typename UnaryPred>
        ForwardIter remove_if(ForwardIter first, ForwardIter last, UnaryPred unary_pred)
        {
            first = leptstl::find_if(first, last, unary_pred);
            auto next = first;
            return first == last ? first : leptstl::remove_copy_if(++next, last, first, unary_pred);
        }

    /*********************************************************************/
    /* replace */
    template<typename ForwardIter, typename T>
        void replace(ForwardIter first, ForwardIter last,
                     const T& old_value, const T& new_value)
        {
            for(; first != last; ++first)
            {
                if(*first == old_value)
                    *first = new_value;
            }
        }

    /*********************************************************************/
    /* replace_if */
    template<typename ForwardIter, typename UnaryPred, typename T>
        void replace_if(ForwardIter first, ForwardIter last,
                        UnaryPred unary_pred, const T& new_value)
        {
            for(; first != last; ++first)
            {
                if(unary_pred(*first))
                    *first = new_value;
            }
        }

    /*********************************************************************/
    /* replace_copy */
    template<typename InputIter, typename OutputIter, typename T>
        OutputIter
        replace_copy(InputIter first, InputIter last,
                     OutputIter result, const T& old_value, const T& new_value)
        {
            for(; first != last; ++first, ++result)
            {
                *result = *first == old_value ? new_value : *first;
            }
            return result;
        }

    /*********************************************************************/
    /* replace_copy_if */
    template<typename InputIter, typename OutputIter, typename UnaryPred, typename T>
        OutputIter
        replace_copy_if(InputIter first, InputIter last,
                        OutputIter result, UnaryPred unary_pred, const T& new_value)
        {
            for(; first != last; ++first, ++result)
            {
                *result = unary_pred(*first) ? new_value : *first;
            }
            return result;
        }

    /*****************************************************************************/
    /* reverse */
    template<typename BidirectionalIter>
        void reverse_dispatch(BidirectionalIter first, BidirectionalIter last,
                              bidirectional_iterator_tag)
        {
            while(true)
            {
                if(first == last || first == --last)
                    return;
                leptstl::iter_swap(first++, last);
            }
        }

    /* reverse */
    template<typename RandomIter>
        void reverse_dispatch(RandomIter first, RandomIter last,
                              random_access_iterator_tag)
        {
            while(first < last)
            {
                leptstl::iter_swap(first++, --last);
            }
        }       

    template<typename BidirectionalIter>
        void reverse(BidirectionalIter first, BidirectionalIter last)
        {
            leptstl::reverse_dispatch(first, last, iterator_category(first));
        }

    /*****************************************************************************/
    /* reverse_copy */
    template<typename BidirectionalIter, typename OutputIter>
        OutputIter reverse_copy(BidirectionalIter first, BidirectionalIter last,
                                OutputIter result)
        {
            while(first != last)
            {
                --last;
                *result = *last;
                ++result;
            }
            return result;
        }

    /*****************************************************************************/
    /* random_shuffle */
    template<typename RandomIter>
        void random_shuffle(RandomIter first, RandomIter last)
        {
            if(first == last)
                return;
            srand((unsigned)time(0));
            for(auto i = first + 1; i != last; ++i)
                leptstl::iter_swap(i, first + (rand() % (i - first + 1)));
        }

    /* random_shuffle 使用一个产生随机数的函数对象rand*/
    template<typename RandomIter, typename RandomNuGenerator>
        void random_shuffle(RandomIter first, RandomIter last,
                            RandomNuGenerator& randnu)
        {
            if(first == last)
                return;
            auto len = leptstl::distance(first, last);
            for(auto i = first + 1; i != last; ++i)
                leptstl::iter_swap(i, first + (randnu(i - first + 1) % len));
        }

    /****************************************************************************/
    /* rotate */
    template<typename ForwardIter>
        ForwardIter rotate_dispatch(ForwardIter first, ForwardIter middle,
                                    ForwardIter last, forward_iterator_tag)
        {
            auto first2 = middle;
            do 
            {
                leptstl::swap(*first++, *first2++);
                    if(first == middle)
                        middle = first2;
            } while(first2 != last);
            auto new_middle = first;
            first2 = middle;
            while(first2 != last)
            {
                leptstl::swap(*first++, *first2++);
                if(first == middle)
                    middle = first2;
                else if(first2 == last)
                    first2 = middle;
            }
            return new_middle;
        }

    template<typename BidirectionalIter>
        BidirectionalIter rotate_dispatch(BidirectionalIter first, BidirectionalIter middle,
                                          BidirectionalIter last, bidirectional_iterator_tag)
        {
            leptstl::reverse_dispatch(first, middle, bidirectional_iterator_tag());
            leptstl::reverse_dispatch(middle, last, bidirectional_iterator_tag());
            while(first != middle && middle != last)
                swap(*first++, *--last);
            if(first == middle)
            {
                leptstl::reverse_dispatch(middle, last, bidirectional_iterator_tag());
                return last;
            }
            else 
            {
                leptstl::reverse_dispatch(first, middle, bidirectional_iterator_tag());
                return first;
            }
        }

    /* 求最大公因子*/
    template<typename EuclideanRingElement>
        EuclideanRingElement rgcd(EuclideanRingElement m, EuclideanRingElement n)
        {
            while(n != 0)
            {
                auto t = m % n;
                m = n; 
                n = t;
            }
            return m;
        }

    template<typename RandomIter>
        RandomIter rotate_dispatch(RandomIter first, RandomIter middle,
                                   RandomIter last, random_access_iterator_tag)
        {
            auto n = last - first;
            auto l = middle - first;
            auto r = n - l;
            auto result = first + (last - middle);
            if(l == r)
            {
                leptstl::swap_ranges(first, middle, last);
                return result;
            }
            auto cycle_times = rgcd(n, l);
            for(auto i = 0; i < cycle_times; ++i)
            {
                auto tmp = *first;
                auto p = first;
                if(l < r)
                {
                    for(auto j = 0; j < r / cycle_times; ++j)
                    {
                        if(p > first + r)
                        {
                            *p = *(p -r);
                            p -= r;
                        }
                        *p = *(p + l);
                        p += l;
                    }
                }
                else 
                {
                    for(auto j = 0; j < l / cycle_times - 1; ++j)
                    {
                        if(p < last - l)
                        {
                            *p = *(p + l);
                            p += l;
                        }
                        *p = *(p - r);
                        p -= r;
                    }
                }
                *p = tmp;
                ++first;
            }
            return result;
        }

    template<typename ForwardIter>
        ForwardIter rotate(ForwardIter first, ForwardIter middle, ForwardIter last)
        {
            if(first == middle)
                return last;
            if(middle == last)
                return first;
            return leptstl::rotate_dispatch(first, middle, last, iterator_category(first));
        }

    /*************************************************************************************/
    /* rotate_copy */
    template<typename ForwardIter, typename OutputIter>
        ForwardIter rotate_copy(ForwardIter first, ForwardIter middle,
                                ForwardIter last, OutputIter result)
        {
            return leptstl::copy(first, middle, leptstl::copy(middle,last, result));
        }

    /**********************************************************************************/
    /* is_permutation 判断[first1,last1)是否为[first2,last2)的排列组合*/
    template<typename ForwardIter1, typename ForwardIter2, typename BinaryPred>
        bool is_permutation_aux(ForwardIter1 first1, ForwardIter1 last1,
                                ForwardIter2 first2, ForwardIter2 last2,
                                BinaryPred pred)
        {
            constexpr bool is_ra_it = leptstl::is_random_access_iterator<ForwardIter1>::value 
                                   && leptstl::is_random_access_iterator<ForwardIter2>::value;
            if(is_ra_it)
            {
                auto len1 = last1 - first1;
                auto len2 = last2 - first2;
                if(len1 != len2)
                        return false;
            }
            for(;first1 != last1 && first2 != last2; ++first1, (void) ++first2)
            {
                if(!pred(*first1, *first2))
                    break;
            }
            if(is_ra_it)
            {
                if(first1 == last1)
                    return true;
            }
            else 
            {
                auto len1 = leptstl::distance(first1, last1);
                auto len2 = leptstl::distance(first2, last2);
                if(len1 == 0 && len2 == 0)
                    return true;
                if(len1 != len2)
                    return false;
            }
            
            for(auto i = first1; i != last1; ++i)
            {
                bool is_repeated = false;
                for(auto j = first1; j != i; ++j)
                {
                    if(pred(*j, *i))
                    {
                        is_repeated = true;
                        break;
                    }
                }
                if(!is_repeated)
                {
                    auto c2 = 0;
                    for(auto j = first2; j != last2; ++j)
                    {
                        if(pred(*i, *j))
                            ++c2;
                    }
                    if(c2 == 0)
                        return false;
                    
                    auto c1 =1;
                    auto j = i;
                    for(++j; j != last1; ++j)
                    {
                        if(pred(*i, *j))
                            ++c1;
                    }
                    if(c1 != c2)
                        return false;
                }
            }
            return true;
        }

    template<typename ForwardIter1, typename ForwardIter2, typename BinaryPred>
        bool is_permutation(ForwardIter1 first1, ForwardIter1 last1,
                                ForwardIter2 first2, ForwardIter2 last2,
                                BinaryPred pred)
        {
            return is_permutation_aux(first1, last1, first2, last2, pred);
        }

    template<typename ForwardIter1, typename ForwardIter2>
        bool is_permutation(ForwardIter1 first1, ForwardIter1 last1,
                            ForwardIter2 first2, ForwardIter2 last2)
        {
            typedef typename iterator_traits<ForwardIter1>::value_type v1;
            typedef typename iterator_traits<ForwardIter2>::value_type v2;
            static_assert(std::is_same<v1, v2>::value,
                        "the type should be same in leptstl::is_permutation");
            return is_permutation_aux(first1, last1, first2, last2, leptstl::equal_to<v1>());
        }

    /********************************************************************************************/
    /* next_permutation */
    template<typename BidirectionalIter>
        bool next_permutation(BidirectionalIter first, BidirectionalIter last)
        {
            auto i = last;
            if(first == last || first == --i)
                return false;
            for(;;)
            {
                auto ii = i;
                if(*--i < *ii)
                {
                    auto j = last;
                    while(!(*i < *--j));
                    leptstl::iter_swap(i, j);
                    leptstl::reverse(ii, last);
                    return true;
                }
                if(i == first)
                {
                    leptstl::reverse(first, last);
                    return false;
                }
            }
        }

    /* next_permutation  Compared*/
    template<typename BidirectionalIter, typename Compared>
        bool next_permutation(BidirectionalIter first, BidirectionalIter last, Compared comp)
        {
            auto i = last;
            if(first == last || first == --i)
                return false;
            for(;;)
            {
                auto ii = i;
                if(comp(*--i, *ii))
                {
                    auto j = last;
                    while(!comp(*i, *--j));
                    leptstl::iter_swap(i, j);
                    leptstl::reverse(ii, last);
                    return true;
                }
                if(i == first)
                {
                    leptstl::reverse(first, last);
                    return false;
                }
            }
        }

    /* prev_permutation */
    template<typename BidirectionalIter>
        bool prev_permutation(BidirectionalIter first, BidirectionalIter last)
        {
            auto i = last;
            if(first == last || first == --i)
                return false;
            for(;;)
            {
                auto ii = i;
                if(*ii < *--i)
                {
                    auto j = last;
                    while(!(*--j < *i));
                    leptstl::iter_swap(i, j);
                    leptstl::reverse(ii, last);
                    return true;
                }
                if(i == first)
                {
                    leptstl::reverse(first, last);
                    return false;
                }
            }
        }

    /* prev_permutation Compared */
    template<typename BidirectionalIter, typename Compared>
        bool prev_permutation(BidirectionalIter first, BidirectionalIter last, Compared comp)
        {
            auto i = last;
            if(first == last || first == --i)
                return false;
            for(;;)
            {
                auto ii = i;
                if(comp(*ii, *--i))
                {
                    auto j = last;
                    while(!comp(*--j, *i));
                    leptstl::iter_swap(i, j);
                    leptstl::reverse(ii, last);
                    return true;
                }
                if(i == first)
                {
                    leptstl::reverse(first, last);
                    return false;
                }
            }
        }

    /****************************************************************************/
    /* merge */
    template<typename InputIter1, typename InputIter2, typename OutputIter>
        OutputIter merge(InputIter1 first1, InputIter1 last1,
                         InputIter2 first2, InputIter2 last2,
                         OutputIter result)
        {
            while(first1 != last1 && first2 != last2)
            {
                if(*first2 < *first1)
                {
                    *result = *first2;
                    ++first2;
                }
                else 
                {
                    *result = *first1;
                    ++first1;
                }
                ++result;
            }
            return leptstl::copy(first2, last2, leptstl::copy(first1, last1, result));
        }

    /* merge  Compared*/
    template<typename InputIter1, typename InputIter2, typename OutputIter, typename Compared>
        OutputIter merge(InputIter1 first1, InputIter1 last1,
                         InputIter2 first2, InputIter2 last2,
                         OutputIter result, Compared comp)
        {
            while(first1 != last1 && first2 != last2)
            {
                if(comp(*first2, *first1))
                {
                    *result = *first2;
                    ++first2;
                }
                else 
                {
                    *result = *first1;
                    ++first1;
                }
                ++result;
            }
            return leptstl::copy(first2, last2, leptstl::copy(first1, last1, result));
        }

    /************************************************************************************/
    /* inplace_merge 把连接在一起的两个有序序列结合成单一序列并保持有序 */
    template<typename BidirectionalIter, typename Distance>
        void merge_without_buffer(BidirectionalIter first, BidirectionalIter middle,
                                  BidirectionalIter last, Distance len1, Distance len2)
        {
            if(len1 == 0 || len2 == 0)
                return;
            if(len1 + len2 == 2)
            {
                if(*middle < *first)
                    leptstl::iter_swap(first, middle);
                return;
            }
            auto first_cut = first;
            auto second_cut = middle;
            Distance len11 = 0;
            Distance len22 = 0;
            if(len1 > len2)
            {
                len11 = len1 >> 1;
                leptstl::advance(first_cut, len11);
                second_cut = leptstl::lower_bound(middle, last, *first_cut);
                len22 = leptstl::distance(middle, second_cut);
            }
            else 
            {
                len22 = len2 >> 1;
                leptstl::advance(second_cut, len22);
                first_cut = leptstl::upper_bound(first, middle, *second_cut);
                len11 = leptstl::distance(first, first_cut);
            }
            auto new_middle = leptstl::rotate(first_cut, middle, second_cut);
            leptstl::merge_without_buffer(first, first_cut, new_middle, len11, len22);
            leptstl::merge_without_buffer(new_middle, second_cut, last, len1 - len11, len2 - len22);
        }

    template<typename BidirectionalIter1, typename BidirectionalIter2>
        BidirectionalIter1 
        merge_backward(BidirectionalIter1 first1, BidirectionalIter1 last1,
                       BidirectionalIter2 first2, BidirectionalIter2 last2,
                       BidirectionalIter1 result)
        {
            if(first1 == last1)
                return leptstl::copy_backward(first2, last2, result);
            if(first2 == last2)
                return leptstl::copy_backward(first1, last1, result);
            --last1;
            --last2;
            while(true)
            {
                if(*last2 < *last1)
                {
                    *--result = *last1;
                    if(first1 == last1)
                        return leptstl::copy_backward(first2, ++last2, result);
                    --last1;
                }
                else 
                {
                    *--result = *last2;
                    if(first2 == last2)
                        return leptstl::copy_backward(first1, ++last1, result);
                    --last2;
                }
            }
        }

    template<typename BidirectionalIter1, typename BidirectionalIter2, typename Distance>
        BidirectionalIter1 
        rotate_adaptive(BidirectionalIter1 first, BidirectionalIter1 middle,
                        BidirectionalIter1 last, Distance len1, Distance len2,
                        BidirectionalIter2 buffer, Distance buffer_size)
        {
            BidirectionalIter2 buffer_end;
            if(len1 > len2 && len2 <= buffer_size)
            {
                buffer_end = leptstl::copy(middle, last, buffer);
                leptstl::copy_backward(first, middle, last);
                return leptstl::copy(buffer, buffer_end, first);
            }
            else if(len1 <= buffer_size)
            {
                buffer_end = leptstl::copy(first, middle, buffer);
                leptstl::copy(middle, last, first);
                return leptstl::copy_backward(buffer, buffer_end, last);
            }
            else 
                return leptstl::rotate(first, middle, last);
        }

    template<typename BidirectionalIter, typename Distance, typename Pointer>
        void merge_adaptive(BidirectionalIter first, BidirectionalIter middle,
                            BidirectionalIter last, Distance len1, Distance len2,
                            Pointer buffer, Distance buffer_size)
        {
            if(len1 <= len2 && len1 <= buffer_size)
            {
                Pointer buffer_end = leptstl::copy(first, middle, buffer);
                leptstl::merge(buffer, buffer_end, middle, last, first);
            }
            else if(len2 <= buffer_size)
            {
                Pointer buffer_end = leptstl::copy(middle, last, buffer);
                leptstl::merge_backward(first, middle, buffer, buffer_end, last);
            }
            else 
            {
                auto first_cut = first;
                auto second_cut = middle;
                Distance len11 = 0;
                Distance len22 = 0;
                if(len1 > len2)
                {
                    len11 = len1 >> 1;
                    leptstl::advance(first_cut, len11);
                    second_cut = leptstl::lower_bound(middle, last, *first_cut);
                    len22 = leptstl::distance(middle, second_cut);
                }
                else 
                {
                    len22 = len2 >> 1;
                    leptstl::advance(second_cut, len22);
                    first_cut = leptstl::upper_bound(first, middle, *second_cut);
                    len11 = leptstl::distance(first, first_cut);
                }
                auto new_middle = leptstl::rotate_adaptive(first_cut, middle, second_cut,
                                                           len1 - len11, len22, buffer, buffer_size);
                leptstl::merge_adaptive(first, first_cut, new_middle, len11, len22, buffer, buffer_size);
                leptstl::merge_adaptive(new_middle, second_cut, last, len1 - len11,
                                        len2 - len22, buffer, buffer_size);
            }
        }

    template<typename BidirectionalIter, typename T>
        void inplace_merge_aux(BidirectionalIter first, BidirectionalIter middle,
                               BidirectionalIter last, T*)
        {
            auto len1 = leptstl::distance(first, middle);
            auto len2 = leptstl::distance(middle, last);
            temporary_buffer<BidirectionalIter, T> buf(first, last);
            if(!buf.begin())
                leptstl::merge_without_buffer(first, middle, last, len1, len2);
            else 
                leptstl::merge_adaptive(first, middle, last, len1, len2, buf.begin(), buf.size());
        }

    template<typename BidirectionalIter>
        void inplace_merge(BidirectionalIter first, BidirectionalIter middle,
                           BidirectionalIter last)
        {
            if(first == middle || middle == last)
                return;
            leptstl::inplace_merge_aux(first, middle, last, value_type(first));
        }

    /************************************************************************************/
    /* Compared */
    /* inplace_merge 把连接在一起的两个有序序列结合成单一序列并保持有序 */
    template<typename BidirectionalIter, typename Distance, typename Compared>
        void merge_without_buffer(BidirectionalIter first, BidirectionalIter middle,
                                  BidirectionalIter last, Distance len1, Distance len2,
                                  Compared comp)
        {
            if(len1 == 0 || len2 == 0)
                return;
            if(len1 + len2 == 2)
            {
                if(comp(*middle, *first))
                    leptstl::iter_swap(first, middle);
                return;
            }
            auto first_cut = first;
            auto second_cut = middle;
            Distance len11 = 0;
            Distance len22 = 0;
            if(len1 > len2)
            {
                len11 = len1 >> 1;
                leptstl::advance(first_cut, len11);
                second_cut = leptstl::lower_bound(middle, last, *first_cut, comp);
                len22 = leptstl::distance(middle, second_cut);
            }
            else 
            {
                len22 = len2 >> 1;
                leptstl::advance(second_cut, len22);
                first_cut = leptstl::upper_bound(first, middle, *second_cut, comp);
                len11 = leptstl::distance(first, first_cut);
            }
            auto new_middle = leptstl::rotate(first_cut, middle, second_cut);
            leptstl::merge_without_buffer(first, first_cut, new_middle, len11, len22, comp);
            leptstl::merge_without_buffer(new_middle, second_cut, last, len1 - len11, len2 - len22, comp);
        }

    template<typename BidirectionalIter1, typename BidirectionalIter2, typename Compared>
        BidirectionalIter1 
        merge_backward(BidirectionalIter1 first1, BidirectionalIter1 last1,
                       BidirectionalIter2 first2, BidirectionalIter2 last2,
                       BidirectionalIter1 result, Compared comp)
        {
            if(first1 == last1)
                return leptstl::copy_backward(first2, last2, result);
            if(first2 == last2)
                return leptstl::copy_backward(first1, last1, result);
            --last1;
            --last2;
            while(true)
            {
                if(comp(*last2, *last1))
                {
                    *--result = *last1;
                    if(first1 == last1)
                        return leptstl::copy_backward(first2, ++last2, result);
                    --last1;
                }
                else 
                {
                    *--result = *last2;
                    if(first2 == last2)
                        return leptstl::copy_backward(first1, ++last1, result);
                    --last2;
                }
            }
        }

    template<typename BidirectionalIter, typename Distance, typename Pointer, typename Compared>
        void merge_adaptive(BidirectionalIter first, BidirectionalIter middle,
                            BidirectionalIter last, Distance len1, Distance len2,
                            Pointer buffer, Distance buffer_size, Compared comp)
        {
            if(len1 <= len2 && len1 <= buffer_size)
            {
                Pointer buffer_end = leptstl::copy(first, middle, buffer);
                leptstl::merge(buffer, buffer_end, middle, last, first, comp);
            }
            else if(len2 <= buffer_size)
            {
                Pointer buffer_end = leptstl::copy(middle, last, buffer);
                leptstl::merge_backward(first, middle, buffer, buffer_end, last, comp);
            }
            else 
            {
                auto first_cut = first;
                auto second_cut = middle;
                Distance len11 = 0;
                Distance len22 = 0;
                if(len1 > len2)
                {
                    len11 = len1 >> 1;
                    leptstl::advance(first_cut, len11);
                    second_cut = leptstl::lower_bound(middle, last, *first_cut, comp);
                    len22 = leptstl::distance(middle, second_cut);
                }
                else 
                {
                    len22 = len2 >> 1;
                    leptstl::advance(second_cut, len22);
                    first_cut = leptstl::upper_bound(first, middle, *second_cut, comp);
                    len11 = leptstl::distance(first, first_cut);
                }
                auto new_middle = leptstl::rotate_adaptive(first_cut, middle, second_cut,
                                                           len1 - len11, len22, buffer, buffer_size);
                leptstl::merge_adaptive(first, first_cut, new_middle, len11, len22, buffer, buffer_size, comp);
                leptstl::merge_adaptive(new_middle, second_cut, last, len1 - len11,
                                        len2 - len22, buffer, buffer_size, comp);
            }
        }

    template<typename BidirectionalIter, typename T, typename Compared>
        void inplace_merge_aux(BidirectionalIter first, BidirectionalIter middle,
                               BidirectionalIter last, T*, Compared comp)
        {
            auto len1 = leptstl::distance(first, middle);
            auto len2 = leptstl::distance(middle, last);
            temporary_buffer<BidirectionalIter, T> buf(first, last);
            if(!buf.begin())
                leptstl::merge_without_buffer(first, middle, last, len1, len2, comp);
            else 
                leptstl::merge_adaptive(first, middle, last, len1, len2, buf.begin(), buf.size(), comp);
        }

    template<typename BidirectionalIter, typename Compared>
        void inplace_merge(BidirectionalIter first, BidirectionalIter middle,
                           BidirectionalIter last, Compared comp)
        {
            if(first == middle || middle == last)
                return;
            leptstl::inplace_merge_aux(first, middle, last, value_type(first), comp);
        }

    /******************************************************************************/
    /* partial_sort */
    template<typename RandomIter>
        void partial_sort(RandomIter first, RandomIter middle, RandomIter last)
        {
            leptstl::make_heap(first, middle);
            for(auto i = middle; i < last; ++i)
            {
                if(*i < *first)
                    leptstl::pop_heap_aux(first, middle, i, *i, distance_type(first));
            }
            leptstl::sort_heap(first, middle);
        }

    /* partial_sort Compared*/
    template<typename RandomIter, typename Compared>
        void partial_sort(RandomIter first, RandomIter middle, RandomIter last, Compared comp)
        {
            leptstl::make_heap(first, middle, comp);
            for(auto i = middle; i < last; ++i)
            {
                if(comp(*i, *first))
                    leptstl::pop_heap_aux(first, middle, i, *i, distance_type(first), comp);
            }
            leptstl::sort_heap(first, middle, comp);
        }

    /* partial_sort_copy */
    template<typename InputIter, typename RandomIter, typename Distance>
        RandomIter psort_copy_aux(InputIter first, InputIter last,
                                  RandomIter result_first, RandomIter result_last,
                                  Distance*)
        {
            if(result_first == result_last)
                return result_last;
            auto result_iter = result_first;
            while(first != last && result_iter != result_last)
            {
                *result_iter = *first;
                ++result_iter;
                ++first;
            }
            leptstl::make_heap(result_first, result_iter);
            while(first != last)
            {
                if(*first < *result_first)
                    leptstl::adjust_heap(result_first, static_cast<Distance>(0),
                                         result_iter - result_first, *first);
                ++first;
            }
            leptstl::sort_heap(result_first, result_iter);
            return result_iter;
        }

    template<typename InputIter, typename RandomIter>
        RandomIter partial_sort_copy(InputIter first, InputIter last,
                                     RandomIter result_first, RandomIter result_last)
        {
            return leptstl::psort_copy_aux(first, last, result_first, result_last,
                                           distance_type(result_first));
        }

    /* partial_sort_copy Compared */
    template<typename InputIter, typename RandomIter, typename Distance, typename Compared>
        RandomIter psort_copy_aux(InputIter first, InputIter last,
                                  RandomIter result_first, RandomIter result_last,
                                  Distance*, Compared comp)
        {
            if(result_first == result_last)
                return result_last;
            auto result_iter = result_first;
            while(first != last && result_iter != result_last)
            {
                *result_iter = *first;
                ++result_iter;
                ++first;
            }
            leptstl::make_heap(result_first, result_iter, comp);
            while(first != last)
            {
                if(comp(*first, *result_first))
                    leptstl::adjust_heap(result_first, static_cast<Distance>(0),
                                         result_iter - result_first, *first, comp);
                ++first;
            }
            leptstl::sort_heap(result_first, result_iter, comp);
            return result_iter;
        }

    template<typename InputIter, typename RandomIter, typename Compared>
        RandomIter partial_sort_copy(InputIter first, InputIter last,
                                     RandomIter result_first, RandomIter result_last,
                                     Compared comp)
        {
            return leptstl::psort_copy_aux(first, last, result_first, result_last,
                                           distance_type(result_first), comp);
        }

    /***********************************************************************************/
    /* partition */
    template<typename BidirectionalIter, typename UnaryPred>
        BidirectionalIter 
        partition(BidirectionalIter first, BidirectionalIter last, UnaryPred unary_pred)
        {
            while(true)
            {
                while(first != last && unary_pred(*first))
                    ++first;
                if(first == last)
                    break;
                --last;
                while(first != last && !unary_pred(*last))
                    --last;
                if(first == last)
                    break;
                leptstl::iter_swap(first, last);
                ++first;
            }
            return first;
        }

    /*********************************************************************************/
    /* partition_copy */
    template<typename InputIter, typename OutputIter1, typename OutputIter2, typename UnaryPred>
        leptstl::pair<OutputIter1, OutputIter2>
        partition_copy(InputIter first, InputIter last,
                       OutputIter1 result_true, OutputIter2 result_false,
                       UnaryPred unary_pred)
        {
            for(; first != last; ++first)
            {
                if(unary_pred(*first))
                    *result_true++ = *first;
                else 
                    *result_false++ = *first;
            }
            return leptstl::pair<OutputIter1, OutputIter2>(result_true, result_false);
        }

    /*************************************************************************************/
    /* sort */
    constexpr static size_t kSmallSectionSize = 128; /*在这个大小内采用插入排序*/
    template<typename Size>
        Size slg2(Size n)
        {
            /*找出lgk <= n 的 k 的最大值*/
            Size k = 0;
            for(; n > 1; n >>= 1)
                ++k;
            return k;
        }

    /* 分割函数 unchecked_partition */
    template<typename RandomIter, typename T>
        RandomIter unchecked_partition(RandomIter first, RandomIter last, const T& pivot)
        {
            while(true)
            {
                while(*first < pivot)
                    ++first;
                --last;
                while(pivot < *last)
                    --last;
                if(!(first < last))
                    return first;
                leptstl::iter_swap(first, last);
                ++first;
            }
        }

    /* 先进行quick sort 当分割行为有恶化倾向时，改用heap_sort*/
    template<typename RandomIter, typename Size>
        void intro_sort(RandomIter first, RandomIter last, Size depth_limit)
        {
            while(static_cast<size_t>(last - first) > kSmallSectionSize)
            {
                if(depth_limit == 0)
                {
                    leptstl::partial_sort(first, last, last);/* 到达最大分割深度,改用heap_sort*/
                    return;
                }
                --depth_limit;
                auto mid = leptstl::median(*first, *(first + (last - first) / 2), *(last - 1));
                auto cut = leptstl::unchecked_partition(first, last, mid);
                leptstl::intro_sort(cut, last, depth_limit);
                last = cut;
            }
        }

    /*插入排序辅助函数*/
    template<typename RandomIter, typename T>
        void unchecked_linear_insert(RandomIter last, const T& value)
        {
            auto next = last;
            --next;
            while(value < *next)
            {
                *last = *next;
                last = next;
                --next;
            }
            *last = value;
        }

    template<typename RandomIter>
        void unchecked_insertion_sort(RandomIter first, RandomIter last)
        {
            for(auto i = first; i != last; ++i)
                leptstl::unchecked_linear_insert(i ,*i);
        }

    template<typename RandomIter>
        void insertion_sort(RandomIter first, RandomIter last)
        {
            if(first == last)
                return;
            for(auto i = first + 1; i != last; ++i)
            {
                auto value = *i;
                if(value < *first)
                {
                    leptstl::copy_backward(first, i, i + 1);
                    *first = value;
                }
                else 
                    leptstl::unchecked_linear_insert(i ,value);
            }
        }

    template<typename RandomIter>
        void final_insertion_sort(RandomIter first, RandomIter last)
        {
            if(static_cast<size_t>(last - first) > kSmallSectionSize)
            {
                leptstl::insertion_sort(first, first + kSmallSectionSize);
                leptstl::unchecked_insertion_sort(first + kSmallSectionSize, last);
            }
            else 
                leptstl::insertion_sort(first, last);
        }

    template<typename RandomIter>
        void sort(RandomIter first, RandomIter last)
        {
            if(first != last)
            {
                /*将区间分为一个一个小区间，然后对整体进行插入排序*/
                leptstl::intro_sort(first, last, slg2(last - first)*2);
                leptstl::final_insertion_sort(first, last);
            }
        }

    /* 分割函数 unchecked_partition Compared*/
    template<typename RandomIter, typename T, typename Compared>
        RandomIter unchecked_partition(RandomIter first, RandomIter last, 
                                       const T& pivot, Compared comp)
        {
            while(true)
            {
                while(comp(*first, pivot))
                    ++first;
                --last;
                while(comp(pivot, *last))
                    --last;
                if(!(first < last))
                    return first;
                leptstl::iter_swap(first, last);
                ++first;
            }
        }

    /* 先进行quick sort 当分割行为有恶化倾向时，改用heap_sort*/
    template<typename RandomIter, typename Size, typename Compared>
        void intro_sort(RandomIter first, RandomIter last, Size depth_limit, Compared comp)
        {
            while(static_cast<size_t>(last - first) > kSmallSectionSize)
            {
                if(depth_limit == 0)
                {
                    leptstl::partial_sort(first, last, last, comp);/* 到达最大分割深度,改用heap_sort*/
                    return;
                }
                --depth_limit;
                auto mid = leptstl::median(*first, *(first + (last - first) / 2), *(last - 1), comp);
                auto cut = leptstl::unchecked_partition(first, last, mid, comp);
                leptstl::intro_sort(cut, last, depth_limit, comp);
                last = cut;
            }
        }

    /*插入排序辅助函数*/
    template<typename RandomIter, typename T, typename Compared>
        void unchecked_linear_insert(RandomIter last, const T& value, Compared comp)
        {
            auto next = last;
            --next;
            while(comp(value, *next))
            {
                *last = *next;
                last = next;
                --next;
            }
            *last = value;
        }

    template<typename RandomIter, typename Compared>
        void unchecked_insertion_sort(RandomIter first, RandomIter last, Compared comp)
        {
            for(auto i = first; i != last; ++i)
                leptstl::unchecked_linear_insert(i ,*i, comp);
        }

    template<typename RandomIter, typename Compared>
        void insertion_sort(RandomIter first, RandomIter last, Compared comp)
        {
            if(first == last)
                return;
            for(auto i = first + 1; i != last; ++i)
            {
                auto value = *i;
                /* 减少比较次数，先直接与第一个比较*/
                if(comp(value, *first))
                {
                    leptstl::copy_backward(first, i, i + 1);
                    *first = value;
                }
                else 
                    leptstl::unchecked_linear_insert(i ,value, comp);
            }
        }

    template<typename RandomIter, typename Compared>
        void final_insertion_sort(RandomIter first, RandomIter last, Compared comp)
        {
            if(static_cast<size_t>(last - first) > kSmallSectionSize)
            {
                leptstl::insertion_sort(first, first + kSmallSectionSize, comp);
                leptstl::unchecked_insertion_sort(first + kSmallSectionSize, last, comp);
            }
            else 
                leptstl::insertion_sort(first, last, comp);
        }

    template<typename RandomIter, typename Compared>
        void sort(RandomIter first, RandomIter last, Compared comp)
        {
            if(first != last)
            {
                leptstl::intro_sort(first, last, slg2(last - first)*2, comp);
                leptstl::final_insertion_sort(first, last, comp);
            }
        }

    /**********************************************************************************/
    /* nth_element */
    template<typename RandomIter>
        void nth_element(RandomIter first, RandomIter nth, RandomIter last)
        {
            if(nth == last)
                return;
            while(last - first > 3)
            {
                auto cut = leptstl::unchecked_partition(first, last, leptstl::median(
                                                        *first, *(first + (last- first) / 2),
                                                        *(last - 1)));
                if(cut <= nth)
                    first = cut;
                else 
                    last = cut;
            }
            leptstl::insertion_sort(first, last);
        }

    /* nth_element Compared*/
    template<typename RandomIter, typename Compared>
        void nth_element(RandomIter first, RandomIter nth, RandomIter last, Compared comp)
        {
            if(nth == last)
                return;
            while(last - first > 3)
            {
                auto cut = leptstl::unchecked_partition(first, last, leptstl::median(
                                                        *first, *(first + (last- first) / 2),
                                                        *(last - 1)), comp);
                if(cut <= nth)
                    first = cut;
                else 
                    last = cut;
            }
            leptstl::insertion_sort(first, last, comp);
        }

    /************************************************************************************/
    /* unique_copy */
    template<typename InputIter, typename ForwardIter>
        ForwardIter unique_copy_dispatch(InputIter first, InputIter last,
                                         ForwardIter result, forward_iterator_tag)
        {
            *result = *first;
            while(++first != last)
            {
                if(*result != *first)
                    *++result = *first;
            }
            return ++result;
        }

    template<typename InputIter, typename OutputIter>
        OutputIter unique_copy_dispatch(InputIter first, InputIter last,
                                         OutputIter result, output_iterator_tag)
        {
            auto value = *first;
            *result = value;
            while(++first != last)
            {
                if(value != *first)
                {
                    value = *first;
                    *++result = value;
                }
            }
            return ++result;
        }

    template<typename InputIter, typename OutputIter>
        OutputIter unique_copy(InputIter first, InputIter last,
                                         OutputIter result)
        {
            if(first == last)
                return result;
            return leptstl::unique_copy_dispatch(first, last,result, iterator_category(result));
        }

    /* unique_copy Compared*/
    template<typename InputIter, typename ForwardIter, typename Compared>
        ForwardIter unique_copy_dispatch(InputIter first, InputIter last,
                                         ForwardIter result, forward_iterator_tag, Compared comp)
        {
            *result = *first;
            while(++first != last)
            {
                if(!comp(*result, *first))
                    *++result = *first;
            }
            return ++result;
        }

    template<typename InputIter, typename OutputIter, typename Compared>
        OutputIter unique_copy_dispatch(InputIter first, InputIter last,
                                         OutputIter result, output_iterator_tag, Compared comp)
        {
            auto value = *first;
            *result = value;
            while(++first != last)
            {
                if(!comp(value, *first))
                {
                    value = *first;
                    *++result = value;
                }
            }
            return ++result;
        }

    template<typename InputIter, typename OutputIter, typename Compared>
        OutputIter unique_copy(InputIter first, InputIter last,
                                         OutputIter result, Compared comp)
        {
            if(first == last)
                return result;
            return leptstl::unique_copy_dispatch(first, last,result, iterator_category(result), comp);
        }

    /******************************************************************************/
    /* unique */
    template<typename ForwardIter>
        ForwardIter unique(ForwardIter first, ForwardIter last)
        {
            first = leptstl::adjacent_find(first, last);
            return leptstl::unique_copy(first, last, first);
        }

    /* unique  Compared*/
    template<typename ForwardIter, typename Compared>
        ForwardIter unique(ForwardIter first, ForwardIter last, Compared comp)
        {
            first = leptstl::adjacent_find(first, last, comp);
            return leptstl::unique_copy(first, last, first, comp);
        }

}   /* namespace leptstl */

#endif  /*LEPTSTL_ALGO_H__*/

