/*************************************************************************
	> File Name: set_algo.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Thu 04 Aug 2022 02:26:04 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_SET_ALGO_H__
#define LEPTSTL_SET_ALGO_H__ 

/*set的四种算法：union intersection difference symmetric_difference 所有函数都要求序列有序*/

#include "algobase.h"
#include "iterator.h"

namespace leptstl 
{
    /* set_union 计算S1 U S2 的结果，并保存到result中*/
    template<typename InputIter1, typename InputIter2, typename OutputIter>
        OutputIter set_union(InputIter1 first1, InputIter1 last1,
                             InputIter2 first2, InputIter2 last2,
                             OutputIter result)
        {
            while(first1 != last1 && first2 != last2)
            {
                if(*first1 < *first2)
                {
                    *result = *first1;
                    ++first1;
                }
                else if(*first2 < *first1)
                {
                    *result = *first2;
                    ++first2;
                }
                else 
                {
                    *result = *first1;
                    ++first1;
                    ++first2;
                }
                ++result;
            }
            return leptstl::copy(first2, last2, leptstl::copy(first1, last1, result));
        }

    template<typename InputIter1, typename InputIter2, typename OutputIter, typename Compared>
        OutputIter set_union(InputIter1 first1, InputIter1 last1,
                             InputIter2 first2, InputIter2 last2,
                             OutputIter result, Compared comp)
        {
            while(first1 != last1 && first2 != last2)
            {
                if(comp(*first1, *first2))
                {
                    *result = *first1;
                    ++first1;
                }
                else if(comp(*first2, *first1))
                {
                    *result = *first2;
                    ++first2;
                }
                else 
                {
                    *result = *first1;
                    ++first1;
                    ++first2;
                }
                ++result;
            }
            return leptstl::copy(first2, last2, leptstl::copy(first1, last1, result));
        }

    /***************************************************************************************/
    /* set_intersection 计算S1 n S2*/
    template<typename InputIter1, typename InputIter2, typename OutputIter>
        OutputIter set_intersection(InputIter1 first1, InputIter1 last1,
                                    InputIter2 first2, InputIter2 last2,
                                    OutputIter result)
        {
            while(first1 != last1 && first2 != last2)
            {
                if(*first1 < *first2)
                    ++first1;
                else if(*first2 < *first1)
                    ++first2;
                else 
                {
                    *result = *first1;
                    ++first1;
                    ++first2;
                    ++result;
                }
            }
            return result;
        }

    template<typename InputIter1, typename InputIter2, typename OutputIter, typename Compared>
        OutputIter set_intersection(InputIter1 first1, InputIter1 last1,
                                    InputIter2 first2, InputIter2 last2,
                                    OutputIter result, Compared comp)
        {
            while(first1 != last1 && first2 != last2)
            {
                if(comp(*first1, *first2))
                    ++first1;
                else if(comp(*first2, *first1))
                    ++first2;
                else 
                {
                    *result = *first1;
                    ++first1;
                    ++first2;
                    ++result;
                }
            }
            return result;
        }

    /****************************************************************************************/
    /* set_difference 计算S1 - S2 */
    template<typename InputIter1, typename InputIter2, typename OutputIter>
        OutputIter set_difference(InputIter1 first1, InputIter1 last1,
                                    InputIter2 first2, InputIter2 last2,
                                    OutputIter result)
        {
            while(first1 != last1 && first2 != last2)
            {
                if(*first1 < *first2)
                {
                    *result = *first1;
                    ++first1;
                    ++result;
                }
                else if(*first2 < *first1)
                    ++first2;
                else 
                {
                    ++first1;
                    ++first2;
                }
            }
            return leptstl::copy(first1, last1, result);
        }

    template<typename InputIter1, typename InputIter2, typename OutputIter, typename Compared>
        OutputIter set_difference(InputIter1 first1, InputIter1 last1,
                                    InputIter2 first2, InputIter2 last2,
                                    OutputIter result, Compared comp)
        {
            while(first1 != last1 && first2 != last2)
            {
                if(comp(*first1, *first2))
                {
                    *result = *first1;
                    ++first1;
                    ++result;
                }
                else if(comp(*first2, *first1))
                    ++first2;
                else 
                {
                    ++first1;
                    ++first2;
                }
            }
            return leptstl::copy(first1, last1, result);
        }

    /***********************************************************************************/
    /* set_symmetric_difference 计算(S1 - S2) U (S2 - S1)*/
    template<typename InputIter1, typename InputIter2, typename OutputIter>
        OutputIter set_symmetric_difference(InputIter1 first1, InputIter1 last1,
                                            InputIter2 first2, InputIter2 last2,
                                            OutputIter result)
        {
            while(first1 != last1 && first2 != last2)
            {
                if(*first1 < *first2)
                {
                    *result = *first1;
                    ++first1;
                    ++result;
                }
                else if(*first2 < *first1)
                {
                    *result = *first2;
                    ++first2;
                    ++result;
                }
                else 
                {
                    ++first1;
                    ++first2;
                }
            }
            return leptstl::copy(first2, last2,leptstl::copy(first1, last1, result));
        }

    template<typename InputIter1, typename InputIter2, typename OutputIter, typename Compared>
        OutputIter set_symmetric_difference(InputIter1 first1, InputIter1 last1,
                                            InputIter2 first2, InputIter2 last2,
                                            OutputIter result, Compared comp)
        {
            while(first1 != last1 && first2 != last2)
            {
                if(comp(*first1, *first2))
                {
                    *result = *first1;
                    ++first1;
                    ++result;
                }
                else if(comp(*first2, *first1))
                {
                    *result = *first2;
                    ++first2;
                    ++result;
                }
                else 
                {
                    ++first1;
                    ++first2;
                }
            }
            return leptstl::copy(first2, last2,leptstl::copy(first1, last1, result));
        }

}   /* namespace leptstl */

#endif  /* LEPTSTL_SET_ALGO_H__ */

