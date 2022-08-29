/*************************************************************************
	> File Name: functional.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Mon 01 Aug 2022 09:05:49 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_FUNCTIONAL_H__
#define LEPTSTL_FUNCTIONAL_H__ 

/*此头文件包含了leptstl的函数对象与哈希函数*/
#include <cstddef>

namespace leptstl 
{
    /*定义一元函数的参数类型和返回值类型*/
    template<typename Arg, typename Result>
        struct unary_function
        {
            typedef Arg         argument_type;
            typedef Result      result_type;
        };

    /*定义二元函数的参数类型和返回值类型*/
    template<typename Arg1, typename Arg2, typename Result>
        struct binary_function
        {
            typedef Arg1    first_argument_type;
            typedef Arg2    second_argument_type;
            typedef Result  result_type;
        };

    /* 仿函数（函数对象）：加法*/
    template<typename T>
        struct plus : public binary_function<T, T, T>
        {
            T operator()(const T& x, const T& y) const { return x + y; }
        };

    /*仿函数：减法*/
    template<typename T>
        struct minus : public binary_function<T, T, T>
        {
            T operator()(const T& x, const T& y) const { return x - y; }
        };

    /* 仿函数：乘法*/
    template<typename T>
        struct multiplies : public binary_function<T, T, T>
        {
            T operator()(const T& x, const T& y) const { return x * y; }
        };

    /* 仿函数：除法*/
    template<typename T>
        struct divides : public binary_function<T, T, T>
        {
            T operator()(const T& x, const T& y) const { return x / y; }
        };

    /* 仿函数：取模*/
    template<typename T>
        struct modulus : public binary_function<T, T, T>
        {
            T operator()(const T& x, const T& y) const { return x % y; }
        };

    /* 仿函数：相反*/
    template<typename T>
        struct negate : public unary_function<T, T>
        {
            T operator()(const T& x) const { return -x; }
        };

    /* 加法证同*/
    template<typename T>
        T identity_element(plus<T>) { return T(0); }

    /*乘法证同*/
    template<typename T>
        T identity_element(multiplies<T>) { return T(1); }

    /* 仿函数：等于*/
    template<typename T>
        struct equal_to : public binary_function<T, T, bool>
        {
            bool operator()(const T& x, const T& y) const { return x == y; }
        };


    /* 仿函数：不等于*/
    template<typename T>
        struct not_equal_to : public binary_function<T, T, bool>
        {
            bool operator()(const T& x, const T& y) const { return x != y; }
        };

    /* 仿函数：大于*/
    template<typename T>
        struct greater : public binary_function<T, T, bool>
        {
            bool operator()(const T& x, const T& y) const { return x > y; }
        };

    /* 仿函数：小于*/
    template<typename T>
        struct less : public binary_function<T, T, bool>
        {
            bool operator()(const T& x, const T& y) const { return x < y; }
        };

    /* 仿函数：大于等于*/
    template<typename T>
        struct greater_equal : public binary_function<T, T, bool>
        {
            bool operator()(const T& x, const T& y) const { return x >= y; }
        };

    /* 仿函数：小于等于*/
    template<typename T>
        struct less_equal : public binary_function<T, T, bool>
        {
            bool operator()(const T& x, const T& y) const { return x <= y; }
        };

    /* 仿函数：逻辑与*/
    template<typename T>
        struct logical_and : public binary_function<T, T, bool>
        {
            bool operator()(const T& x, const T& y) const { return x && y; }
        };

    /* 仿函数：逻辑或*/
    template<typename T>
        struct logical_or : public binary_function<T, T, bool>
        {
            bool operator()(const T& x, const T& y) const { return x || y; }
        };

    /* 仿函数：逻辑非*/
    template<typename T>
        struct logical_not : public unary_function<T, bool>
        {
            bool operator()(const T& x) const { return !x; }
        };

    /* 仿函数：证同*/
    template<typename T>
        struct identity : public unary_function<T, bool>
        {
            const T& operator()(const T& x) const { return x; }
        };

    /* 仿函数：接受一个pair，返回第一个元素*/
    template<typename Pair>
        struct selectfirst : public unary_function<Pair, typename Pair::first_type>
        {
            const typename Pair::first_type& operator()(const Pair& x) const 
            {
                return x.first;
            }
        };

    /* 仿函数：接受一个pair，返回第二个元素*/
    template<typename Pair>
        struct selectsecond : public unary_function<Pair, typename Pair::second_type>
        {
            const typename Pair::second_type& operator()(const Pair& x) const 
            {
                return x.second;
            }
        };

    /*仿函数：返回第一个参数*/
    template<typename Arg1, typename Arg2>
        struct projectfirst : public binary_function<Arg1, Arg2, Arg1>
        {
            Arg1 operator()(const Arg1& x, const Arg2&) const { return x; }
        };

    /*仿函数：返回第二个参数*/
    template<typename Arg1, typename Arg2>
        struct projectsecond : public binary_function<Arg1, Arg2, Arg2>
        {
            Arg2 operator()(const Arg1&, const Arg2& y) const { return y; }
        };

    /***********************************************************/
    /* 哈希函数对象*/

    /*对于大部分类型，hash function 什么都不用做*/
    template<typename T>
        struct hash {};

    /*针对指针的偏特化*/
    template<typename T>
        struct hash<T*>
        {
            size_t operator()(T* p) const noexcept 
            {
                return reinterpret_cast<size_t>(p);
            }
        };

    /* 对于整型，只是返回原值   特化*/
#define LEPTSTL_TRIVIAL_HASH_FUN(Type)              \
    template<> struct hash<Type>                    \
    {                                               \
        size_t operator()(Type val) const noexcept  \
        { return static_cast<size_t>(val); }        \
    };

    /* 显式实例化*/
    LEPTSTL_TRIVIAL_HASH_FUN(bool)
    LEPTSTL_TRIVIAL_HASH_FUN(char)
    LEPTSTL_TRIVIAL_HASH_FUN(signed char)
    LEPTSTL_TRIVIAL_HASH_FUN(unsigned char)
    LEPTSTL_TRIVIAL_HASH_FUN(wchar_t)
    LEPTSTL_TRIVIAL_HASH_FUN(char16_t)
    LEPTSTL_TRIVIAL_HASH_FUN(char32_t)
    LEPTSTL_TRIVIAL_HASH_FUN(short)
    LEPTSTL_TRIVIAL_HASH_FUN(unsigned short)
    LEPTSTL_TRIVIAL_HASH_FUN(int)
    LEPTSTL_TRIVIAL_HASH_FUN(unsigned int)
    LEPTSTL_TRIVIAL_HASH_FUN(long)
    LEPTSTL_TRIVIAL_HASH_FUN(unsigned long)
    LEPTSTL_TRIVIAL_HASH_FUN(long long)
    LEPTSTL_TRIVIAL_HASH_FUN(unsigned long long)
#undef LEPTSTL_TRIVIAL_HASH_FUN


    /*对于浮点数 逐位hash*/
    inline size_t bitwise_hash(const unsigned char* first, size_t count)
    {
    #if ((__GNUC__ || __clang__) && __SIZEOF_POINTER__ == 8)
        const size_t fnv_offset = 14695981039346656037ull;
        const size_t fnv_prime = 1099511628211ull;
    #else 
        const size_t fnv_offset = 2166136261u;
        const size_t fnv_prime = 16777619u;
    #endif 
        size_t result = fnv_offset;
        for(size_t i = 0; i < count; ++i)
        {
            result ^= (size_t)first[i];
            result *= fnv_prime;
        }
        return result;
    }

    /* 特化*/
    template<>
        struct hash<float>
        {
            size_t operator()(const float& val)
            {
                return val == 0.0f ? 0 : bitwise_hash((const unsigned char*)&val, sizeof(float));
            }
        };

    template <>
        struct hash<double>
        {
            size_t operator()(const double& val)
            {
                return val == 0.0f ? 0 : bitwise_hash((const unsigned char*)&val,sizeof(double));
            }
        };

    template <>
        struct hash<long double>
        {
            size_t operator()(const long double& val)
            {
                return val == 0.0f ? 0 : bitwise_hash((const unsigned char*)&val,sizeof(long double));
            }
        };

}   /* namespace leptstl */

#endif  /* LEPTSTL_FUNCTIONAL_H__ */
