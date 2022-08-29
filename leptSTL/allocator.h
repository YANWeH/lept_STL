/*************************************************************************
	> File Name: allocator.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Mon 01 Aug 2022 07:25:53 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_ALLOCATOR_H__
#define LEPTSTL_ALLOCATOR_H__ 

/*此头文件包含一个模板类allocator，用于管理内存分配，释放，对象的构造、析构*/
#include "construct.h"

namespace leptstl 
{
    /* 模板类：allocator */
    template<typename T>
        class allocator 
        {
            public:
                typedef T           value_type;
                typedef T*          pointer;
                typedef const T*    const_pointer;
                typedef T&          reference;
                typedef const T&    const_reference;
                typedef size_t      size_type;
                typedef ptrdiff_t   difference_type;

            public:
                static T* allocate();
                static T* allocate(size_type n);

                static void deallocate(T* ptr);
                static void deallocate(T* ptr, size_type n);

                static void construct(T* ptr);
                static void construct(T* ptr, const T& value);
                static void construct(T* ptr, T&& value);

                template<typename... Args>
                    static void construct(T* ptr, Args&&... args);

                static void destroy(T* ptr);
                static void destroy(T* first, T* last);
        };

    template<typename T>
        T* allocator<T>::allocate()
        {
            return static_cast<T*>(::operator new(sizeof(T)));
        }

    template<typename T>
        T* allocator<T>::allocate(size_type n)
        {
            if(n == 0)
                return nullptr;
            return static_cast<T*>(::operator new(n*sizeof(T)));
        }

    template<typename T>
        void allocator<T>::deallocate(T* ptr)
        {
            if(ptr == nullptr)
                return;
            ::operator delete(ptr);
        }
    template<typename T>
        void allocator<T>::deallocate(T* ptr, size_type /*size*/)
        {
            if(ptr == nullptr)
                return;
            ::operator delete(ptr);
        }

    template<typename T>
        void allocator<T>::construct(T* ptr)
        {
            leptstl::construct(ptr);
        }

    template<typename T>
        void allocator<T>::construct(T* ptr, const T& value)
        {
            leptstl::construct(ptr, value);
        }

    template<typename T>
        void allocator<T>::construct(T* ptr, T&& value)
        {
            leptstl::construct(ptr, leptstl::move(value));
        }

    template<typename T>
        template<typename ...Args>
        void allocator<T>::construct(T* ptr, Args&& ...args)
        {
            leptstl::construct(ptr, leptstl::forward<Args>(args)...);
        }

    template<typename T>
        void allocator<T>::destroy(T* ptr)
        {
            leptstl::destroy(ptr);
        }

    template<typename T>
        void allocator<T>::destroy(T* first, T* last)
        {
            leptstl::destroy(first, last);
        }

}   /* namespace leptstl */

#endif  /* LEPTSTL_ALLOCATOR_H__ */

