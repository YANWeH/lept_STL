/*************************************************************************
	> File Name: leptstring.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Tue 16 Aug 2022 02:47:58 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_LEPTSTRING_H__
#define LEPTSTL_LEPTSTRING_H__ 

#include "basic_string.h"

namespace leptstl 
{
    using string    = leptstl::basic_string<char>;
    using wstring   = leptstl::basic_string<wchar_t>;
    using u16string = leptstl::basic_string<char16_t>;
    using u32string = leptstl::basic_string<char32_t>;

}   /*namespace leptstl */

#endif /* LEPTSTL_LEPTSTRING_H__*/

