/*************************************************************************
	> File Name: uninitialized.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Thu 04 Aug 2022 03:08:56 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_UNINITIALIZED_H__
#define LEPTSTL_UNINITIALIZED_H__ 

/*此头文件用于对未初始化空间构造元素*/

#include "algobase.h"
#include "construct.h"
#include "iterator.h"
#include "type_traits.h"
#include "util.h"

namespace leptstl 
{
    /*****************************************************************************/
    /* uninitialized_copy 将[first,last)上的内容复制到result为起始处的空间*/
    template<typename InputIter, typename ForwardIter>
        ForwardIter 
        unchecked_uninit_copy(InputIter first, InputIter last, ForwardIter result, std::true_type)
        {
            return leptstl::copy(first, last, result);
        }

    template<typename InputIter, typename ForwardIter>
        ForwardIter 
        unchecked_uninit_copy(InputIter first, InputIter last, ForwardIter result, std::false_type)
        {
            auto cur = result;
            try 
            {
                for(; first != last; ++first, ++cur)
                {
                    leptstl::construct(&*cur, *first);
                }
            }
            catch (...)
            {
                for(; result != cur; ++result)
                    leptstl::destroy(&*result);
            }
            return cur;
        }

    template<typename InputIter, typename ForwardIter>
        ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result)
        {
            return leptstl::unchecked_uninit_copy(first, last, result,
                                                  std::is_trivially_copy_assignable<
                                                  typename iterator_traits<ForwardIter>::
                                                  value_type>{});
        }

    /*********************************************************************************/
    /* uninitialized_copy_n 把[first, first+n）上的内容复制到result为起点的空间*/
    template<typename InputIter, typename Size, typename ForwardIter>
        ForwardIter 
        unchecked_uninit_copy_n(InputIter first, Size n, ForwardIter result, std::true_type)
        {
            return leptstl::copy_n(first, n, result).second;
        }

    template<typename InputIter, typename Size, typename ForwardIter>
        ForwardIter 
        unchecked_uninit_copy_n(InputIter first, Size n, ForwardIter result, std::false_type)
        {
            auto cur = result;
            try 
            {
                for(; n > 0; --n, ++cur, ++first)
                    leptstl::construct(&*cur, *first);
            }
            catch(...)
            {
                for(; result != cur; ++result)
                    leptstl::destroy(&*result);
            }
            return cur;
        }

    template<typename InputIter, typename Size, typename ForwardIter>
        ForwardIter 
        uninitialized_copy_n(InputIter first, Size n, ForwardIter result)
        {
            return leptstl::unchecked_uninit_copy_n(first, n, result,
                                                    std::is_trivially_copy_assignable<
                                                    typename iterator_traits<InputIter>::
                                                    value_type>{});
        }

    /**********************************************************************************/
    /* uninitialized_fill 在[first,last)区间填充元素值*/
    template<typename ForwardIter, typename T>
        void unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T& value, std::true_type)
        {
            leptstl::fill(first, last, value);
        }

    template<typename ForwardIter, typename T>
        void unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T& value, std::false_type)
        {
            auto cur = first;
            try 
            {
                for(; cur != last; ++cur)
                    leptstl::construct(&*cur, value);
            }
            catch(...)
            {
                for(; first != cur; ++first)
                    leptstl::destroy(&*first);
            }
        }

    template<typename ForwardIter, typename T>
        void uninitialized_fill(ForwardIter first, ForwardIter last,const T& value)
        {
            leptstl::unchecked_uninit_fill(first, last, value,
                                           std::is_trivially_copy_assignable<
                                           typename iterator_traits<ForwardIter>::
                                           value_type>{});
        }

    /*********************************************************************************/
    /* uninitialized_fill_n [first, first+n）*/
    template<typename ForwardIter, typename Size, typename T>
        ForwardIter 
        unchecked_uninit_fill_n(ForwardIter first, Size n, const T& value, std::true_type)
        {
            return leptstl::fill_n(first, n, value);
        }

    template<typename ForwardIter, typename Size, typename T>
        ForwardIter 
        unchecked_uninit_fill_n(ForwardIter first, Size n, const T& value, std::false_type)
        {
            auto cur = first;
            try 
            {
                for(; n > 0; --n, ++cur)
                    leptstl::construct(&*cur, value);
            }
            catch(...)
            {
                for(; first != cur; ++first)
                    leptstl::destroy(&*first);
            }
            return cur;
        }

    template<typename ForwardIter, typename Size, typename T>
        ForwardIter 
        uninitialized_fill_n(ForwardIter first, Size n, const T& value)
        {
            return leptstl::unchecked_uninit_fill_n(first, n, value,
                                                    std::is_trivially_copy_assignable<
                                                    typename iterator_traits<ForwardIter>::
                                                    value_type>{});
        }

    /*****************************************************************************/
    /* uninitialized_move 将[first,last)上的内容移动到result为起始处的空间*/
    template<typename InputIter, typename ForwardIter>
        ForwardIter 
        unchecked_uninit_move(InputIter first, InputIter last, ForwardIter result, std::true_type)
        {
            return leptstl::move(first, last, result);
        }

    template<typename InputIter, typename ForwardIter>
        ForwardIter 
        unchecked_uninit_move(InputIter first, InputIter last, ForwardIter result, std::false_type)
        {
            auto cur = result;
            try 
            {
                for(; first != last; ++first, ++cur)
                {
                    leptstl::construct(&*cur, leptstl::move(*first));
                }
            }
            catch (...)
            {
                leptstl::destroy(result, cur);
            }
            return cur;
        }

    template<typename InputIter, typename ForwardIter>
        ForwardIter uninitialized_move(InputIter first, InputIter last, ForwardIter result)
        {
            return leptstl::unchecked_uninit_move(first, last, result,
                                                  std::is_trivially_move_assignable<
                                                  typename iterator_traits<InputIter>::
                                                  value_type>{});
        }



    /*******************************************************************************/
    /* uninitialized_move_n 把[first, first+n）上的内容移动到result为起点的空间*/
    template<typename InputIter, typename Size, typename ForwardIter>
        ForwardIter 
        unchecked_uninit_move_n(InputIter first, Size n, ForwardIter result, std::true_type)
        {
            return leptstl::move(first, first + n, result);
        }

    template<typename InputIter, typename Size, typename ForwardIter>
        ForwardIter 
        unchecked_uninit_move_n(InputIter first, Size n, ForwardIter result, std::false_type)
        {
            auto cur = result;
            try 
            {
                for(; n > 0; --n, ++cur, ++first)
                    leptstl::construct(&*cur, leptstl::move(*first));
            }
            catch(...)
            {
                for(; result != cur; ++result)
                    leptstl::destroy(&*result);
            }
            return cur;
        }

    template<typename InputIter, typename Size, typename ForwardIter>
        ForwardIter 
        uninitialized_move_n(InputIter first, Size n, ForwardIter result)
        {
            return leptstl::unchecked_uninit_move_n(first, n, result,
                                                    std::is_trivially_move_assignable<
                                                    typename iterator_traits<InputIter>::
                                                    value_type>{});
        }

}   /* namespace leptstl */

#endif  /* LEPTSTL_UNINITIALIZED_H__ */
 

