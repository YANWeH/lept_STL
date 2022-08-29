/*************************************************************************
	> File Name: util.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Sat 30 Jul 2022 03:42:29 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_UTIL_H__
#define LEPTSTL_UTIL_H__ 

/* 此头文件包含通用工具， 如move forward swap等函数 以及pair */
#include <cstddef>

#include "type_traits.h"

namespace leptstl 
{
    /* move 移动 右值引用*/
    template<typename T>
        typename std::remove_reference<T>::type&& move(T&& arg) noexcept 
        {
            return static_cast<typename std::remove_reference<T>::type&&>(arg);
        }

    /* forward 完美转发*/
    template<typename T>
        T&& forward(typename std::remove_reference<T>::type& arg) noexcept 
        {
            return static_cast<T&&>(arg);
        }

    template<typename T>
        T&& forward(typename std::remove_reference<T>::type&& arg) noexcept 
        {
            static_assert(!std::is_lvalue_reference<T>::value, "bad forward");
            return static_cast<T&&>(arg);
        }

    /* swap */
    template<typename T>
        void swap(T& lhs, T& rhs)
        {
            auto tmp(leptstl::move(lhs));
            lhs = leptstl::move(rhs);
            rhs = leptstl::move(tmp);
        }

    template<typename ForwardIter1, typename ForwardIter2>
        ForwardIter2 swap_range(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2)
        {
            for(; first1 != last1; ++first1, (void)++first2)
                leptstl::swap(*first1, *first2);
            return first2;
        }

    template<typename T, size_t N>
        void swap(T(&a)[N], T(&b)[N])
        {
            leptstl::swap_range(a, a+N, b);
        }

    /**********************************************************/
    /* pair */
    template<typename T1, typename T2>
        struct pair 
        {
            typedef T1 first_type;
            typedef T2 second_type;
            first_type first;   /*保存第一个数据*/
            second_type second; /*保存第二个数据*/

            /* default constructiable */
            template<typename O1 = T1, typename O2 = T2,
                typename = typename std::enable_if<
                    std::is_default_constructible<O1>::value &&
                    std::is_default_constructible<O2>::value, void>::type>
                    constexpr pair()
                    : first(), second()
                    {
                    }

            /* implicit constructiable for this type */
            template<typename U1 = T1, typename U2 = T2,
                typename std::enable_if<
                    std::is_copy_constructible<U1>::value &&
                    std::is_copy_constructible<U2>::value &&
                    std::is_convertible<const U1&, T1>::value &&
                    std::is_convertible<const U2&, T2>::value, int>::type = 0>
                    constexpr pair(const T1& a,const T2& b)
                    :first(a), second(b)
                    {
                    }

            /* explicit constructiable for this type */
            template<typename U1 = T1, typename U2 = T2,
                typename std::enable_if<
                    std::is_copy_constructible<U1>::value &&
                    std::is_copy_constructible<U2>::value &&
                    (!std::is_convertible<const U1&, T1>::value ||
                    !std::is_convertible<const U2&, T2>::value), int>::type = 0>
                    explicit constexpr pair(const T1& a,const T2& b)
                    :first(a), second(b)
                    {
                    }

            pair(const pair& rhs) = default;
            pair(pair&& rhs) = default;

            /* implicit constructiable for other type */
            template<typename Other1, typename Other2,
                typename std::enable_if<
                std::is_constructible<T1, Other1>::value &&
                std::is_constructible<T2, Other2>::value &&
                std::is_convertible<Other1&&, T1>::value &&
                std::is_convertible<Other2&&, T2>::value, int>::type = 0>
                constexpr pair(Other1&& a, Other2&& b)
                :first(leptstl::forward<Other1>(a)),
                second(leptstl::forward<Other2>(b))
            {
            }

            /* explicit constructiable for other type */
            template<typename Other1, typename Other2,
                typename std::enable_if<
                std::is_constructible<T1, Other1>::value &&
                std::is_constructible<T2, Other2>::value &&
                (!std::is_convertible<Other1, T1>::value ||
                !std::is_convertible<Other2, T2>::value), int>::type = 0>
                explicit constexpr pair(Other1&& a, Other2&& b)
                :first(leptstl::forward<Other1>(a)),
                second(leptstl::forward<Other2>(b))
            {
            }

            /* implicit constructiable for other pair */
            template<typename Other1, typename Other2,
                typename std::enable_if<
                std::is_constructible<T1, const Other1&>::value &&
                std::is_constructible<T2, const Other2&>::value &&
                std::is_convertible<const Other1&, T1>::value &&
                std::is_convertible<const Other2&, T2>::value, int>::type = 0>
                constexpr pair(const pair<Other1, Other2>& other)
                :first(other.first),
                second(other.second)
            {
            }

            template<typename Other1, typename Other2,
                typename std::enable_if<
                std::is_constructible<T1, Other1>::value &&
                std::is_constructible<T2, Other2>::value &&
                std::is_convertible<Other1, T1>::value &&
                std::is_convertible<Other2, T2>::value, int>::type = 0>
                constexpr pair(pair<Other1, Other2>&& other)
                :first(leptstl::forward<Other1>(other.first)),
                second(leptstl::forward<Other2>(other.second))
            {
            }

            /* explicit constructiable for other pair */
            template<typename Other1, typename Other2,
                typename std::enable_if<
                std::is_constructible<T1, const Other1&>::value &&
                std::is_constructible<T2, const Other2&>::value &&
                (!std::is_convertible<const Other1&, T1>::value ||
                !std::is_convertible<const Other2&, T2>::value), int>::type = 0>
                explicit constexpr pair(const pair<Other1, Other2>& other)
                :first(other.first),
                second(other.second)
            {
            }

            template<typename Other1, typename Other2,
                typename std::enable_if<
                std::is_constructible<T1, Other1>::value &&
                std::is_constructible<T2, Other2>::value &&
                (!std::is_convertible<Other1, T1>::value ||
                !std::is_convertible<Other2, T2>::value), int>::type = 0>
                explicit constexpr pair(pair<Other1, Other2>&& other)
                :first(leptstl::forward<Other1>(other.first)),
                second(leptstl::forward<Other2>(other.second))
            {
            }

            /* copy assign for this pair */
            pair& operator=(const pair& rhs)
            {
                if(this != &rhs)
                {
                    first = rhs.first;
                    second = rhs.second;
                }
                return *this;
            }
            /* move assign for this pair */
            pair& operator=(pair&& rhs)
            {
                if(this != &rhs)
                {
                    first = leptstl::move(rhs.first);
                    second = leptstl::move(rhs.second);
                }
                return *this;
            }

            /* copy assign for other pair */
            template<typename Other1, typename Other2>
                pair& operator=(const pair<Other1, Other2>& other)
                {
                    first = other.first;
                    second = other.second;
                    return *this;
                }
            /* move assign for other pair */
            template<typename Other1, typename Other2>
                pair& operator=(pair<Other1, Other2>&& other)
                {
                    first = leptstl::forward<Other1>(other.first);
                    second = leptstl::forward<Other2>(other.second);
                    return *this;
                }

            ~pair() = default;

            void swap(pair& other)
            {
                if(this != &other)
                {
                    leptstl::swap(first, other.first);
                    leptstl::swap(second, other.second);
                }
            }
        };

    /* 重载比较操作符*/
    template<typename T1, typename T2>
        bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
        {
            return lhs.first == rhs.first && lhs.second == rhs.second;
        }

    template<typename T1, typename T2>
        bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
        {
            return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
        }

    template<typename T1, typename T2>
        bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
        {
            return !(lhs == rhs);
        }

    template<typename T1, typename T2>
        bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
        {
            return rhs < lhs;
        }

    template<typename T1, typename T2>
        bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
        {
            return !(rhs < lhs);
        }

    template<typename T1, typename T2>
        bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
        {
            return !(lhs < rhs);
        }

    /* 重载leptstl中的swap */
    template<typename T1, typename T2>
        void swap(pair<T1, T2>& lhs, pair<T1, T2>& rhs)
        {
            lhs.swap(rhs);
        }

    /* 全局函数 让两个数据成为一个pair */
    template<typename T1, typename T2>
        pair<T1, T2> make_pair(T1&& first, T2&& second)
        {
            return pair<T1, T2>(leptstl::forward<T1>(first),leptstl::forward<T2>(second));
        }

} /* namespace leptstl */

#endif /* LEPTSTL_UTIL_H__ */

