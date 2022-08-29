/*************************************************************************
	> File Name: type_traits.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Sat 30 Jul 2022 03:24:28 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_TYPE_TRAITS_H__
#define LEPTSTL_TYPE_TRAITS_H__ 
/* 此头文件用来提取（萃取）类型信息*/
#include <type_traits>

namespace leptstl 
{
    /* helper struct*/
    template<typename T, T v>
        struct lept_integral_constant
        {
            static constexpr T value = v;
        };
    template<bool b>
        using lept_bool_constant = lept_integral_constant<bool, b>;

    typedef lept_bool_constant<true>  lept_true_type;
    typedef lept_bool_constant<false> lept_false_type;

/*************************************************************************/
    /* type traits */

    /* forward declaration begin */
    template<typename T1, typename T2>
        struct pair;
    /* forward declaration end */
    template<typename T>
        struct is_pair : leptstl::lept_false_type{};
    template<typename T1, typename T2>
        struct is_pair<leptstl::pair<T1, T2>> : leptstl::lept_true_type{};
}   /*namespace leptstl*/

#endif /* LEPTSTL_TYPE_TRAITS_H__*/

