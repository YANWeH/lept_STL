/*************************************************************************
	> File Name: numeric.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Thu 04 Aug 2022 01:44:05 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_NUMERIC_H__
#define LEPTSTL_NUMERIC_H__ 

/* 此头文件包含leptstl的数值算法*/

#include "iterator.h"

namespace leptstl 
{
    /* accumulate */
    template<typename InputIter, typename T>
        T accumulate(InputIter first, InputIter last, T init)
        {
            for(; first != last; ++first)
                init += *first;
            return init;
        }

    template<typename InputIter, typename T, typename BinaryOp>
        T accumulate(InputIter first, InputIter last, T init, BinaryOp binary_op)
        {
            for(; first != last; ++first)
                init = binary_op(init, *first);
            return init;
        }

    /***************************************************************************/
    /* adjacent_difference 计算相邻元素的差值*/
    template<typename InputIter, typename OutputIter>
        OutputIter adjacent_difference(InputIter first, InputIter last, OutputIter result)
        {
            if(first == last) return result;
            *result = *first;
            auto value = *first;
            while(++first != last)
            {
                auto tmp = *first;
                *++result = tmp - value;
                value = tmp;
            }
            return ++result;
        }

    template<typename InputIter, typename OutputIter, typename BinaryOp>
        OutputIter adjacent_difference(InputIter first, InputIter last, OutputIter result, BinaryOp binary_op)
        {
            if(first == last) return result;
            *result = *first;
            auto value = *first;
            while(++first != last)
            {
                auto tmp = *first;
                *++result = binary_op(tmp, value);
                value = tmp;
            }
            return ++result;
        }

    /***********************************************************************************/
    /*inner_product 以init为初值，计算两区间的内积*/
    template<typename InputIter1, typename InputIter2, typename T>
        T inner_product(InputIter1 first1, InputIter1 last1, InputIter2 first2, T init)
        {
            for(; first1 != last1; ++first1, ++first2)
                init = init + ((*first1) * (*first2));
            return init;
        }

    template<typename InputIter1, typename InputIter2, typename T,typename BinaryOp1, typename BinaryOp2>
        T inner_product(InputIter1 first1, InputIter1 last1, InputIter2 first2, T init, BinaryOp1 binary_op1, BinaryOp2 binary_op2)
        {
            for(; first1 != last1; ++first1, ++first2)
                init = binary_op1(init, binary_op2(*first1, *first2));
            return init;
        }

    /*************************************************************************/
    /* iota 填充[first,last)以value为初值开始递增*/
    template<typename ForwardIter, typename T>
        void iota(ForwardIter first, ForwardIter last, T value)
        {
            while(first != last)
            {
                *first++ = value;
                ++value;
            }
        }

    /*****************************************************************************/
    /* partial_sum 计算局部累计和*/
    template<typename InputIter, typename OutputIter>
        OutputIter partial_sum(InputIter first, InputIter last, OutputIter result)
        {
            if(first == last) return result;
            *result = *first;
            auto value = *first;
            while(++first != last)
            {
                value = value + *first;
                *++result = value;
            }
            return ++result;
        }

    template<typename InputIter, typename OutputIter, typename BinaryOp>
        OutputIter partial_sum(InputIter first, InputIter last, OutputIter result, BinaryOp binary_op)
        {
            if(first == last) return result;
            *result = *first;
            auto value = *first;
            while(++first != last)
            {
                value = binary_op(value, *first);
                *++result = value;
            }
            return ++result;
        }

}   /* namespace leptstl */

#endif  /* LEPTSTL_NUMERIC_H__ */

