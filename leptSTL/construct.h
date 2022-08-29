/*************************************************************************
	> File Name: construct.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Mon 01 Aug 2022 03:24:06 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_CONSTRUCT_H__
#define LEPTSTL_CONSTRUCT_H__ 

/*此头文件包含两个函数：
 * construct：负责对象构造
 * destroy：负责对象析构
 */

#include <new>

#include "type_traits.h"
#include "iterator.h"
#include "util.h"

namespace leptstl 
{
    /*construct 构造对象*/
    template<typename T>
        void construct(T* ptr)
        {
            ::new ((void*)ptr) T();
        }

    template<typename T1, typename T2>
        void construct(T1* ptr, const T2& value)
        {
            ::new ((void*)ptr) T1(value);
        }

    template<typename T, typename... Args>
        void construct(T* ptr, Args&&... args)
        {
            ::new ((void*)ptr) T(leptstl::forward<Args>(args)...);
        }

    /* destroy 将对象析构 */
    template<typename T>
        void destroy_one(T*, std::true_type){}

    template<typename T>
        void destroy_one(T* pointer, std::false_type)
        {
            if(pointer != nullptr)
            {
                pointer->~T();
            }
        }

    template<typename ForwardIter>
        void destroy_cat(ForwardIter, ForwardIter, std::true_type){}

    template<typename ForwardIter>
        void destroy_cat(ForwardIter first, ForwardIter last, std::false_type)
        {
            for(; first != last; ++first)
                destroy(&*first);
        }

    template<typename T>
        void destroy(T* pointer)
        {
            destroy_one(pointer, std::is_trivially_destructible<T>{});
        }

    template<typename ForwardIter>
        void destroy(ForwardIter first, ForwardIter last)
        {
            destroy_cat(first, last, std::is_trivially_destructible<
                    typename iterator_traits<ForwardIter>::value_type>{});
        }

}   /* namespace leptstl */

#endif /* LEPTSTL_CONSTRUCT_H__ */
