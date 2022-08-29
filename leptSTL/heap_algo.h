/*************************************************************************
	> File Name: heap_algo.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Wed 03 Aug 2022 04:54:20 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_HEAP_ALGO_H__
#define LEPTSTL_HEAP_ALGO_H__ 
/* 此头文件包含heap四个算法：push_heap pop_heap sort_heap make_heap*/
#include "iterator.h"

namespace leptstl 
{
    /*push_heap该函数接受两个迭代器，表示一个heap容器的首尾，并且新元素已经插入到容器尾部*/
    template<typename RandomIter, typename Distance, typename T>
        void push_heap_aux(RandomIter first, Distance holeIndex, Distance topIndex, T value)
        {
            auto parent = (holeIndex - 1) / 2;
            while(holeIndex > topIndex && *(first + parent) < value)
            {
                *(first + holeIndex) = *(first + parent);
                holeIndex = parent;
                parent = (holeIndex - 1) / 2;
            }
            *(first + holeIndex) = value;
        }

    template<typename RandomIter, typename Distance>
        void push_heap_d(RandomIter first, RandomIter last, Distance*)
        {
            leptstl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0), *(last - 1));
        }

    template<typename RandomIter>
        void push_heap(RandomIter first, RandomIter last)
        {
            leptstl::push_heap_d(first, last, distance_type(first));
        }

    /* 重载使用函数对象comp代替比较操作*/
    template<typename RandomIter, typename Distance, typename T, typename Compared>
        void push_heap_aux(RandomIter first, Distance holeIndex, Distance topIndex, T value, Compared comp)
        {
            auto parent = (holeIndex - 1) / 2;
            while(holeIndex > topIndex && comp(*(first + parent), value))
            {
                *(first + holeIndex) = *(first + parent);
                holeIndex = parent;
                parent = (holeIndex - 1) / 2;
            }
            *(first + holeIndex) = value;
        }

    template<typename RandomIter, typename Distance, typename Compared>
        void push_heap_d(RandomIter first, RandomIter last, Distance*,Compared comp)
        {
            leptstl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0), *(last - 1), comp);
        }

    template<typename RandomIter, typename Compared>
        void push_heap(RandomIter first, RandomIter last, Compared comp)
        {
            leptstl::push_heap_d(first, last, distance_type(first), comp);
        }

    /****************************************************************************/
    /* pop_heap 该函数接受两个迭代器，将heap的根节点取出放在容器尾部，调整heap*/
    template<typename RandomIter, typename T, typename Distance>
        void adjust_heap(RandomIter first, Distance holeIndex, Distance len, T value)
        {
            auto topIndex = holeIndex;
            auto rchild = holeIndex * 2 + 2;
            while(rchild < len)
            {
                if(*(first + rchild) < *(first + rchild -1))
                    --rchild;
                *(first + holeIndex) = *(first + rchild);
                holeIndex = rchild;
                rchild = holeIndex * 2 + 2;
            }
            if(rchild == len)
            {
                *(first + holeIndex) = *(first + rchild -1);
                holeIndex = rchild - 1;
            }
            leptstl::push_heap_aux(first, holeIndex, topIndex, value);
        }

    template<typename RandomIter, typename T, typename Distance>
        void pop_heap_aux(RandomIter first, RandomIter last, RandomIter result, T value, Distance*)
        {
            *result = *first;
            leptstl::adjust_heap(first, static_cast<Distance>(0), last - first, value);
        }

    template<typename RandomIter>
        void pop_heap(RandomIter first, RandomIter last)
        {
            leptstl::pop_heap_aux(first, last - 1, last - 1, *(last - 1), distance_type(first));
        }

    /*重载使用函数对象comp代替比较*/
    template<typename RandomIter, typename T, typename Distance, typename Compared>
        void adjust_heap(RandomIter first, Distance holeIndex, Distance len, T value, Compared comp)
        {
            auto topIndex = holeIndex;
            auto rchild = holeIndex * 2 + 2;
            while(rchild < len)
            {
                if(comp(*(first + rchild), *(first + rchild -1)))
                    --rchild;
                *(first + holeIndex) = *(first + rchild);
                holeIndex = rchild;
                rchild = holeIndex * 2 + 2;
            }
            if(rchild == len)
            {
                *(first + holeIndex) = *(first + rchild -1);
                holeIndex = rchild - 1;
            }
            leptstl::push_heap_aux(first, holeIndex, topIndex, value, comp);
        }

    template<typename RandomIter, typename T, typename Distance, typename Compared>
        void pop_heap_aux(RandomIter first, RandomIter last, RandomIter result, T value, Distance*, Compared comp)
        {
            *result = *first;
            leptstl::adjust_heap(first, static_cast<Distance>(0), last - first, value, comp);
        }

    template<typename RandomIter, typename Compared>
        void pop_heap(RandomIter first, RandomIter last, Compared comp)
        {
            leptstl::pop_heap_aux(first, last - 1, last - 1, *(last - 1), distance_type(first), comp);
        }

    /**********************************************************************************/
    /* sort_heap 不断执行pop_heap，直到首尾最多差1*/
    template<typename RandomIter>
        void sort_heap(RandomIter first, RandomIter last)
        {
            while(last - first > 1)
                leptstl::pop_heap(first, last--);
        }

    template<typename RandomIter, typename Compared>
        void sort_heap(RandomIter first, RandomIter last, Compared comp)
        {
            while(last - first > 1)
                leptstl::pop_heap(first, last--, comp);
        }

    /*************************************************************************************/
    /* make_heap */
    template<typename RandomIter, typename Distance>
        void make_heap_aux(RandomIter first, RandomIter last, Distance*)
        {
            if(last - first < 2)
                return;
            auto len = last - first; 
            auto holeIndex = (len - 2) / 2;
            while(true)
            {
                leptstl::adjust_heap(first, holeIndex, len, *(first + holeIndex));
                if(holeIndex == 0)
                    return;
                holeIndex--;
            }
        }

    template<typename RandomIter>
        void make_heap(RandomIter first, RandomIter last)
        {
            leptstl::make_heap_aux(first, last, distance_type(first));
        }

    template<typename RandomIter, typename Distance, typename Compared>
        void make_heap_aux(RandomIter first, RandomIter last, Distance*, Compared comp)
        {
            if(last - first < 2)
                return;
            auto len = last - first; 
            auto holeIndex = (len - 2) / 2;
            while(true)
            {
                leptstl::adjust_heap(first, holeIndex, len, *(first + holeIndex), comp);
                if(holeIndex == 0)
                    return;
                holeIndex--;
            }
        }

    template<typename RandomIter, typename Compared>
        void make_heap(RandomIter first, RandomIter last, Compared comp)
        {
            leptstl::make_heap_aux(first, last, distance_type(first), comp);
        }

}   /* namespace leptstl */

#endif  /* LEPTSTL_HEAP_ALGO_H__ */

