/*************************************************************************
	> File Name: iterator.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Sun 31 Jul 2022 04:49:54 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_ITERATOR_H__
#define LEPTSTL_ITERATOR_H__ 

/* 此头文件用于迭代器设计， 包含了一些模板结构体与全局函数 */
#include <cstddef>

#include "type_traits.h"

namespace leptstl 
{
    /* 五种迭代器类型 */
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    /* iterator 模板 */
    template<typename Category, typename T, typename Distance = ptrdiff_t,
        typename Pointer = T*, typename Reference = T&>
            struct iterator 
            {
                typedef Category    iterator_category;
                typedef T           value_type;
                typedef Pointer     pointer;
                typedef Reference   reference;
                typedef Distance    difference_type;
            };

    /* iterator traits */
    template<typename T>
        struct has_iterator_cat
        {
            private:
                struct two { char a; char b; };
                template<typename U> static two test(...);
                template<typename U> static char test(typename U::iterator_category* = 0);
            public:
                static const bool value = sizeof(test<T>(0)) == sizeof(char);
        };

    template<typename Iterator, bool>
        struct iterator_traits_impl {};

    template<typename Iterator>
        struct iterator_traits_impl<Iterator, true>
        {
            typedef typename Iterator::iterator_category iterator_category;
            typedef typename Iterator::value_type        value_type;
            typedef typename Iterator::pointer           pointer;
            typedef typename Iterator::reference         reference;
            typedef typename Iterator::difference_type   difference_type;
        };

    template<typename Iterator, bool>
        struct iterator_traits_helper {};

    template<typename Iterator>
        struct iterator_traits_helper<Iterator, true>
            :public iterator_traits_impl<Iterator,
            std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
            std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value>
        {
        };

    /* 萃取迭代器特性 */
    template<typename Iterator>
        struct iterator_traits 
            :public iterator_traits_helper<Iterator,has_iterator_cat<Iterator>::value> {};

    /* 针对原生指针的偏特化版本 */
    template<typename T>
        struct iterator_traits<T*>
        {
            typedef random_access_iterator_tag      iterator_category;
            typedef T                               value_type;
            typedef T*                              pointer;
            typedef T&                              reference;
            typedef ptrdiff_t                       difference_type;
        };

    template<typename T>
        struct iterator_traits<const T*>
        { 
            typedef random_access_iterator_tag      iterator_category;
            typedef T                               value_type;
            typedef const T*                        pointer;
            typedef const T&                        reference;
            typedef ptrdiff_t                       difference_type;
        };

    template<typename T,typename U, bool = has_iterator_cat<iterator_traits<T>>::value>
        struct has_iterator_cat_of
            :public lept_bool_constant<std::is_convertible<
             typename iterator_traits<T>::iterator_category, U>::value>
        {
        };

    /* 萃取某种迭代器 */
    template<typename T, typename U>
        struct has_iterator_cat_of<T, U, false> : public lept_false_type {};

    template<typename Iter>
        struct is_input_iterator : public has_iterator_cat_of<Iter, input_iterator_tag> {};

    template<typename Iter>
        struct is_output_iterator : public has_iterator_cat_of<Iter, output_iterator_tag> {};

    template<typename Iter>
        struct is_forward_iterator : public has_iterator_cat_of<Iter, forward_iterator_tag> {};

    template<typename Iter>
        struct is_bidirectional_iterator : public has_iterator_cat_of<Iter, bidirectional_iterator_tag> {};

    template<typename Iter>
        struct is_random_access_iterator : public has_iterator_cat_of<Iter, random_access_iterator_tag> {};

    template<typename Iterator>
        struct is_iterator : 
            public lept_bool_constant<is_input_iterator<Iterator>::value ||
            is_output_iterator<Iterator>::value>
        {    
        };

    /* 萃取某个迭代器category */
    template<typename Iterator>
        typename iterator_traits<Iterator>::iterator_category 
        iterator_category(const Iterator&)
        {
            typedef typename iterator_traits<Iterator>::iterator_category Category;
            return Category();
        }

    /* 萃取某个迭代器的distance_type */
    template<typename Iterator>
        typename iterator_traits<Iterator>::difference_type*
        distance_type(const Iterator&)
        {
            return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
        }

    /* 萃取某个迭代器的value_type */
    template<typename Iterator>
        typename iterator_traits<Iterator>::value_type*
        value_type(const Iterator&)
        {
            return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
        }

    /* 计算迭代器间的距离 */
    /*distance input_iterator_tag版*/
    template<typename InputIterator>
        typename iterator_traits<InputIterator>::difference_type 
        distance_dispatch(InputIterator first, InputIterator last, input_iterator_tag)
        {
            typename iterator_traits<InputIterator>::difference_type n = 0;
            while(first != last)
            {
                ++first;
                ++n;
            }
            return n;
        }

    /* distance random_access_iterator_tag版*/
    template<typename RandomIter>
        typename iterator_traits<RandomIter>::difference_type 
        distance_dispatch(RandomIter first, RandomIter last, random_access_iterator_tag)
        {
            return last - first;
        }

    template<typename InputIterator>
        typename iterator_traits<InputIterator>::difference_type 
        distance(InputIterator first, InputIterator last)
        {
            return distance_dispatch(first, last, iterator_category(first));
        }
        
    /* 以下函数让迭代器前进n个距离*/
    /*advance input_iterator_tag */
    template<typename InputIterator, typename Distance>
        void advance_dispatch(InputIterator& i, Distance n, input_iterator_tag)
        {
            while(n--)
                ++i;
        }
    
    /*advance bidirectional_iterator_tag */
    template<typename BidirectionalIterator, typename Distance>
        void advance_dispatch(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag)
        {
            if(n >= 0)
                while(n--) ++i;
            else 
                while(n++) --i;
        }

    /*advance random_access_iterator_tag*/
    template<typename RandomIter, typename Distance>
        void advance_dispatch(RandomIter& i, Distance n, random_access_iterator_tag)
        {
            i += n;
        }

    template<typename InputIterator, typename Distance>
        void advance(InputIterator& i, Distance n)
        {
            advance_dispatch(i , n, iterator_category(i));
        }

    /******************************************************************************/

    /*模板类：reverse_iterator*/
    template<typename Iterator>
        class reverse_iterator
        {
            private:
                Iterator current; /*记录对应的正向迭代器*/

            public:
                /*反向迭代器的五种相应类型*/
                typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
                typedef typename iterator_traits<Iterator>::value_type          value_type;
                typedef typename iterator_traits<Iterator>::difference_type     difference_type;
                typedef typename iterator_traits<Iterator>::pointer             pointer;
                typedef typename iterator_traits<Iterator>::reference           reference;

                typedef Iterator                                                iterator_type;
                typedef reverse_iterator<Iterator>                              self;

            public:
                /*构造函数*/
                reverse_iterator(){}
                explicit reverse_iterator(iterator_type i) : current(i){}
                reverse_iterator(const self& rhs) : current(rhs.current){}

            public:
                /* 取出对应的正向迭代器*/
                iterator_type base() const 
                { return current; }

                /*重载操作符 */
                reference operator*() const 
                {
                    /*实际对应正向迭代器的前一个位置*/
                    auto tmp = current;
                    return *--tmp;
                }
                pointer operator->() const 
                {
                    return &(operator*());
                }

                /* 前进++ 变为后退--*/
                self& operator++()
                {
                    --current;
                    return *this;
                }
                self operator++(int)
                {
                    self tmp = *this;
                    --current;
                    return tmp;
                }
                /* 后退--变为前进++*/
                self& operator--()
                {
                    ++current;
                    return *this;
                }
                self operator--(int)
                {
                    self tmp = *this;
                    ++current;
                    return tmp;
                }

                self operator+=(difference_type n)
                {
                    current -= n;
                    return *this;
                }
                self operator+(difference_type n) const 
                {
                    return self(current - n);
                }
                self operator-=(difference_type n)
                {
                    current += n;
                    return *this;
                }
                self operator-(difference_type n) const 
                {
                    return self(current + n);
                }

                reference operator[](difference_type n) const 
                {
                    return *(*this + n);
                }
        };

    /* 重载operator-*/
    template<typename Iterator>
        typename reverse_iterator<Iterator>::difference_type 
        operator-(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
        {
            return rhs.base() - lhs.base();
        }

    /*重载比较操作符*/
    template<typename Iterator>
        bool operator==(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
        {
            return lhs.base() == rhs.base();
        }

    template<typename Iterator>
        bool operator<(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
        {
            return rhs.base() < lhs.base();
        }

    template<typename Iterator>
        bool operator!=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
        {
            return !(lhs == rhs);
        }

    template<typename Iterator>
        bool operator>(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
        {
            return rhs < lhs;
        }

    template<typename Iterator>
        bool operator<=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
        {
            return !(rhs < lhs);
        }

    template<typename Iterator>
        bool operator>=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
        {
            return !(lhs < rhs);
        }

}   /*namespace leptstl */

#endif /* LEPTSTL_ITERATOR_H__ */

