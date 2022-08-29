/*************************************************************************
	> File Name: exceptdef.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Tue 02 Aug 2022 08:14:53 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_EXCEPTDEF_H__
#define LEPTSTL_EXCEPTDEF_H__ 

#include <stdexcept>
#include <cassert>

namespace leptstl 
{
#define LEPTSTL_DEBUG(expr) assert(expr)

#define THROW_LENGTH_ERROR_IF(expr, what) \
    if ((expr)) throw std::length_error(what)

#define THROW_OUT_OF_RANGE_IF(expr, what) \
    if ((expr)) throw std::out_of_range(what)

#define THROW_RUNTIME_ERROR_IF(expr, what) \
    if ((expr)) throw std::runtime_error(what)

}   /* namespace leptstl */

#endif  /*LEPTSTL_EXCEPTDEF_H__*/

