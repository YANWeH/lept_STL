/*************************************************************************
	> File Name: unordered_set.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Sun 21 Aug 2022 08:18:51 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_UNORDERED_SET_H__
#define LEPTSTL_UNORDERED_SET_H__ 

/*此头文件包含两个模板类unordered_set和unordered_multiset*/

#include "hashtable.h"

namespace leptstl 
{
    /* 模板类 unordered_set，键值不允许重复*/
    /* 参数一代表键值类型，参数二代表哈希函数，缺省使用 leptstl::hash，*/
    /* 参数三代表键值比较方式，缺省使用 leptstl::equal_to*/
    template<typename Key, typename Hash = leptstl::hash<Key>, typename KeyEqual = leptstl::equal_to<Key>>
        class unordered_set 
        {
            private:
                /* 使用hashtable作为底层机制*/
                typedef hashtable<Key, Hash, KeyEqual> base_type;
                base_type ht_;

            public:
                typedef typename base_type::allocator_type       allocator_type;
                typedef typename base_type::key_type             key_type;
                typedef typename base_type::value_type           value_type;
                typedef typename base_type::hasher               hasher;
                typedef typename base_type::key_equal            key_equal;

                typedef typename base_type::size_type            size_type;
                typedef typename base_type::difference_type      difference_type;
                typedef typename base_type::pointer              pointer;
                typedef typename base_type::const_pointer        const_pointer;
                typedef typename base_type::reference            reference;
                typedef typename base_type::const_reference      const_reference;

                typedef typename base_type::const_iterator       iterator;
                typedef typename base_type::const_iterator       const_iterator;
                typedef typename base_type::const_local_iterator local_iterator;
                typedef typename base_type::const_local_iterator const_local_iterator;

                allocator_type get_allocator() const { return ht_.get_allocator(); }

            public:
                /*构造 复制 移动函数*/
                unordered_set()
                    :ht_(100, Hash(), KeyEqual())
                {
                }

                explicit unordered_set(size_type bucket_count,
                                       const Hash& hash = Hash(),
                                       const KeyEqual& equal = KeyEqual())
                    :ht_(bucket_count, hash, equal)
                {
                }

                template <typename InputIterator>
                    unordered_set(InputIterator first, InputIterator last,
                                  const size_type bucket_count = 100,
                                  const Hash& hash = Hash(),
                                  const KeyEqual& equal = KeyEqual())
                    : ht_(leptstl::max(bucket_count, static_cast<size_type>(leptstl::distance(first, last))), hash, equal)
                {
                    for (; first != last; ++first)
                        ht_.insert_unique_noresize(*first);
                }

                unordered_set(std::initializer_list<value_type> ilist,
                              const size_type bucket_count = 100,
                              const Hash& hash = Hash(),
                              const KeyEqual& equal = KeyEqual())
                    :ht_(leptstl::max(bucket_count, static_cast<size_type>(ilist.size())), hash, equal)
                {
                    for (auto first = ilist.begin(), last = ilist.end(); first != last; ++first)
                        ht_.insert_unique_noresize(*first);
                }

                unordered_set(const unordered_set& rhs)
                    :ht_(rhs.ht_)
                {
                }
                unordered_set(unordered_set&& rhs) noexcept
                    : ht_(leptstl::move(rhs.ht_))
                {
                }

                unordered_set& operator=(const unordered_set& rhs)
                {
                    ht_ = rhs.ht_;
                    return *this;
                }
                unordered_set& operator=(unordered_set&& rhs)
                {
                    ht_ = leptstl::move(rhs.ht_);
                    return *this;
                }

                unordered_set& operator=(std::initializer_list<value_type> ilist)
                {
                    ht_.clear();
                    ht_.reserve(ilist.size());
                    for (auto first = ilist.begin(), last = ilist.end(); first != last; ++first)
                        ht_.insert_unique_noresize(*first);
                    return *this;
                }

                ~unordered_set() = default;

                /*迭代器相关*/
                iterator       begin()        noexcept
                { return ht_.begin(); }
                const_iterator begin()  const noexcept
                { return ht_.begin(); }
                iterator       end()          noexcept
                { return ht_.end(); }
                const_iterator end()    const noexcept
                { return ht_.end(); }

                const_iterator cbegin() const noexcept
                { return ht_.cbegin(); }
                const_iterator cend()   const noexcept
                { return ht_.cend(); }

                /* 容量相关*/

                bool      empty()    const noexcept { return ht_.empty(); }
                size_type size()     const noexcept { return ht_.size(); }
                size_type max_size() const noexcept { return ht_.max_size(); }

                /* 修改容器操作*/

                /* empalce / empalce_hint*/

                template <typename ...Args>
                    pair<iterator, bool> emplace(Args&& ...args)
                { return ht_.emplace_unique(leptstl::forward<Args>(args)...); }

                template <typename ...Args>
                    iterator emplace_hint(const_iterator hint, Args&& ...args)
                { return ht_.emplace_unique_use_hint(hint, leptstl::forward<Args>(args)...); }

                /* insert*/

                pair<iterator, bool> insert(const value_type& value)
                { return ht_.insert_unique(value); }
                pair<iterator, bool> insert(value_type&& value)
                { return ht_.emplace_unique(leptstl::move(value)); }

                iterator insert(const_iterator hint, const value_type& value)
                { return ht_.insert_unique_use_hint(hint, value); }
                iterator insert(const_iterator hint, value_type&& value)
                { return ht_.emplace_unique_use_hint(hint, leptstl::move(value)); }

                template <typename InputIterator>
                    void insert(InputIterator first, InputIterator last)
                { ht_.insert_unique(first, last); }

                /* erase / clear*/

                void      erase(iterator it)
                { ht_.erase(it); }
                void      erase(iterator first, iterator last)
                { ht_.erase(first, last); }

                size_type erase(const key_type& key)
                { return ht_.erase_unique(key); }

                void      clear()
                { ht_.clear(); }

                void      swap(unordered_set& other) noexcept
                { ht_.swap(other.ht_); }

                /* 查找相关*/

                size_type      count(const key_type& key) const 
                { return ht_.count(key); }

                iterator       find(const key_type& key) 
                { return ht_.find(key); }
                const_iterator find(const key_type& key)  const 
                { return ht_.find(key); }

                pair<iterator, iterator> equal_range(const key_type& key)
                { return ht_.equal_range_unique(key); }
                pair<const_iterator, const_iterator> equal_range(const key_type& key) const
                { return ht_.equal_range_unique(key); }

                /* bucket interface*/

                /*选择bucket上的index为n的位置*/
                local_iterator       begin(size_type n)        noexcept
                { return ht_.begin(n); }
                const_local_iterator begin(size_type n)  const noexcept
                { return ht_.begin(n); }
                const_local_iterator cbegin(size_type n) const noexcept
                { return ht_.cbegin(n); }

                local_iterator       end(size_type n)          noexcept
                { return ht_.end(n); }
                const_local_iterator end(size_type n)    const noexcept
                { return ht_.end(n); }
                const_local_iterator cend(size_type n)   const noexcept
                { return ht_.cend(n); }

                /* 返回bucket的容量*/
                size_type bucket_count()                 const noexcept
                { return ht_.bucket_count(); }
                /*返回bucket能达到的最大容量*/
                size_type max_bucket_count()             const noexcept
                { return ht_.max_bucket_count(); }

                /*返回bucket[n]的node数*/
                size_type bucket_size(size_type n)       const noexcept
                { return ht_.bucket_size(n); }
                /*返回key对应的bucket位置*/
                size_type bucket(const key_type& key)    const
                { return ht_.bucket(key); }

                /* hash policy*/

                float     load_factor()            const noexcept { return ht_.load_factor(); }

                float     max_load_factor()        const noexcept { return ht_.max_load_factor(); }
                void      max_load_factor(float ml)               { ht_.max_load_factor(ml); }

                void      rehash(size_type count)                 { ht_.rehash(count); }
                void      reserve(size_type count)                { ht_.reserve(count); }

                hasher    hash_fcn()               const          { return ht_.hash_fcn(); }
                key_equal key_eq()                 const          { return ht_.key_eq(); }

            private:
                friend bool operator==(const unordered_set& lhs, const unordered_set& rhs)
                {
                    return lhs.ht_.equal_range_unique(rhs.ht_);
                }
                friend bool operator!=(const unordered_set& lhs, const unordered_set& rhs)
                {
                    return !lhs.ht_.equal_range_unique(rhs.ht_);
                }

        }; /* unordered_set */

    /* 重载比较操作符*/
    template <typename Key, typename Hash, typename KeyEqual, typename Alloc>
        bool operator==(const unordered_set<Key, Hash, KeyEqual>& lhs,
                        const unordered_set<Key, Hash, KeyEqual>& rhs)
        {
            return lhs == rhs;
        }
        
    template <typename Key, typename Hash, typename KeyEqual, typename Alloc>
        bool operator!=(const unordered_set<Key, Hash, KeyEqual>& lhs,
                        const unordered_set<Key, Hash, KeyEqual>& rhs)
        {
            return lhs != rhs;
        }
        
    /* 重载 leptstl 的 swap*/
    template <typename Key, typename Hash, typename KeyEqual, typename Alloc>
        void swap(unordered_set<Key, Hash, KeyEqual>& lhs,
                  unordered_set<Key, Hash, KeyEqual>& rhs)
        {
            lhs.swap(rhs);
        }

    /*****************************************************************************************/
    /* 模板类 unordered_multiset，键值允许重复*/
    /* 参数一代表键值类型，参数二代表哈希函数，缺省使用 leptstl::hash，*/
    /* 参数三代表键值比较方式，缺省使用 leptstl::equal_to*/
    template<typename Key, typename Hash = leptstl::hash<Key>, typename KeyEqual = leptstl::equal_to<Key>>
        class unordered_multiset
        {
            private:
                typedef hashtable<Key, Hash, KeyEqual> base_type;
                base_type ht_;

            public:
                /* 使用 hashtable 的型别*/
                typedef typename base_type::allocator_type       allocator_type;
                typedef typename base_type::key_type             key_type;
                typedef typename base_type::value_type           value_type;
                typedef typename base_type::hasher               hasher;
                typedef typename base_type::key_equal            key_equal;

                typedef typename base_type::size_type            size_type;
                typedef typename base_type::difference_type      difference_type;
                typedef typename base_type::pointer              pointer;
                typedef typename base_type::const_pointer        const_pointer;
                typedef typename base_type::reference            reference;
                typedef typename base_type::const_reference      const_reference;

                typedef typename base_type::const_iterator       iterator;
                typedef typename base_type::const_iterator       const_iterator;
                typedef typename base_type::const_local_iterator local_iterator;
                typedef typename base_type::const_local_iterator const_local_iterator;

                allocator_type get_allocator() const { return ht_.get_allocator(); }

            public:
                /* 构造 复制 移动*/
                unordered_multiset()
                    :ht_(100, Hash(), KeyEqual())
                {
                }

                explicit unordered_multiset(size_type bucket_count,
                              const Hash& hash = Hash(),
                              const KeyEqual& equal = KeyEqual())
                    :ht_(bucket_count, hash, equal)
                {
                }

                template <typename InputIterator>
                unordered_multiset(InputIterator first, InputIterator last,
                                   const size_type bucket_count = 100,
                                   const Hash& hash = Hash(),
                                   const KeyEqual& equal = KeyEqual())
                    :ht_(leptstl::max(bucket_count, static_cast<size_type>(leptstl::distance(first, last))), hash, equal)
                {
                    for (; first != last; ++first)
                        ht_.insert_multi_noresize(*first);
                }

                unordered_multiset(std::initializer_list<value_type> ilist,
                                   const size_type bucket_count = 100,
                                   const Hash& hash = Hash(),
                                   const KeyEqual& equal = KeyEqual())
                    :ht_(leptstl::max(bucket_count, static_cast<size_type>(ilist.size())), hash, equal)
                {
                    for (auto first = ilist.begin(), last = ilist.end(); first != last; ++first)
                        ht_.insert_multi_noresize(*first);
                }

                unordered_multiset(const unordered_multiset& rhs)
                    :ht_(rhs.ht_)
                {
                }
                unordered_multiset(unordered_multiset&& rhs) noexcept
                    :ht_(leptstl::move(rhs.ht_))
                {
                }

                unordered_multiset& operator=(const unordered_multiset& rhs)
                {
                    ht_ = rhs.ht_;
                    return *this;
                }
                unordered_multiset& operator=(unordered_multiset&& rhs)
                {
                    ht_ = leptstl::move(rhs.ht_);
                    return *this;
                }

                unordered_multiset& operator=(std::initializer_list<value_type> ilist)
                {
                    ht_.clear();
                    ht_.reserve(ilist.size());
                    for (auto first = ilist.begin(), last = ilist.end(); first != last; ++first)
                        ht_.insert_multi_noresize(*first);
                    return *this;
                }

                ~unordered_multiset() = default;

                /* 迭代器相关*/

                iterator       begin()        noexcept
                { return ht_.begin(); }
                const_iterator begin()  const noexcept
                { return ht_.begin(); }
                iterator       end()          noexcept
                { return ht_.end(); }
                const_iterator end()    const noexcept
                { return ht_.end(); }
              
                const_iterator cbegin() const noexcept
                { return ht_.cbegin(); }
                const_iterator cend()   const noexcept
                { return ht_.cend(); }
              
                /* 容量相关*/
              
                bool      empty()    const noexcept { return ht_.empty(); }
                size_type size()     const noexcept { return ht_.size(); }
                size_type max_size() const noexcept { return ht_.max_size(); }
              
                /* 修改容器相关*/
              
                /* emplace / emplace_hint*/
              
                template <typename ...Args>
                iterator emplace(Args&& ...args)
                { return ht_.emplace_multi(leptstl::forward<Args>(args)...); }
              
                template <typename ...Args>
                iterator emplace_hint(const_iterator hint, Args&& ...args)
                { return ht_.emplace_multi_use_hint(hint, leptstl::forward<Args>(args)...); }
              
                /* insert*/
              
                iterator insert(const value_type& value)
                { return ht_.insert_multi(value); }
                iterator insert(value_type&& value)
                { return ht_.emplace_multi(leptstl::move(value)); }
              
                iterator insert(const_iterator hint, const value_type& value)
                { return ht_.insert_multi_use_hint(hint, value); }
                iterator insert(const_iterator hint, value_type&& value)
                { return ht_.emplace_multi_use_hint(hint, leptstl::move(value)); }
              
                template <typename InputIterator>
                void     insert(InputIterator first, InputIterator last)
                { ht_.insert_multi(first, last); }
              
                /* erase / clear*/
              
                void      erase(iterator it)
                { ht_.erase(it); }
                void      erase(iterator first, iterator last)
                { ht_.erase(first, last); }
              
                size_type erase(const key_type& key)
                { return ht_.erase_multi(key); }
              
                void      clear()
                { ht_.clear(); }
              
                void      swap(unordered_multiset& other) noexcept 
                { ht_.swap(other.ht_); }
              
                /* 查找相关*/
              
                size_type      count(const key_type& key) const 
                { return ht_.count(key); }
              
                iterator       find(const key_type& key) 
                { return ht_.find(key); }
                const_iterator find(const key_type& key)  const 
                { return ht_.find(key); }
              
                pair<iterator, iterator> equal_range(const key_type& key)
                { return ht_.equal_range_multi(key); }
                pair<const_iterator, const_iterator> equal_range(const key_type& key) const
                { return ht_.equal_range_multi(key); }
              
                /* bucket interface*/
              
                local_iterator       begin(size_type n)        noexcept
                { return ht_.begin(n); }
                const_local_iterator begin(size_type n)  const noexcept
                { return ht_.begin(n); }
                const_local_iterator cbegin(size_type n) const noexcept
                { return ht_.cbegin(n); }
              
                local_iterator       end(size_type n)          noexcept
                { return ht_.end(n); }
                const_local_iterator end(size_type n)    const noexcept
                { return ht_.end(n); }
                const_local_iterator cend(size_type n)   const noexcept
                { return ht_.cend(n); }
              
                size_type bucket_count()                 const noexcept
                { return ht_.bucket_count(); }
                size_type max_bucket_count()             const noexcept
                { return ht_.max_bucket_count(); }
              
                size_type bucket_size(size_type n)       const noexcept
                { return ht_.bucket_size(n); }
                size_type bucket(const key_type& key)    const
                { return ht_.bucket(key); }
              
                /* hash policy*/
              
                float     load_factor()            const noexcept { return ht_.load_factor(); }
              
                float     max_load_factor()        const noexcept { return ht_.max_load_factor(); }
                void      max_load_factor(float ml)               { ht_.max_load_factor(ml); }
              
                void      rehash(size_type count)                 { ht_.rehash(count); }
                void      reserve(size_type count)                { ht_.reserve(count); }
              
                hasher    hash_fcn()               const          { return ht_.hash_fcn(); }
                key_equal key_eq()                 const          { return ht_.key_eq(); }
              
              public:
                friend bool operator==(const unordered_multiset& lhs, const unordered_multiset& rhs)
                {
                    return lhs.ht_.equal_range_multi(rhs.ht_);
                }
                friend bool operator!=(const unordered_multiset& lhs, const unordered_multiset& rhs)
                {
                    return !lhs.ht_.equal_range_multi(rhs.ht_);
                }

        };  /* unordered_multiset */

    /* 重载比较操作符*/
    template <typename Key, typename Hash, typename KeyEqual, typename Alloc>
        bool operator==(const unordered_multiset<Key, Hash, KeyEqual>& lhs,
                        const unordered_multiset<Key, Hash, KeyEqual>& rhs)
        {
            return lhs == rhs;
        }
        
    template <typename Key, typename Hash, typename KeyEqual, typename Alloc>
        bool operator!=(const unordered_multiset<Key, Hash, KeyEqual>& lhs,
                        const unordered_multiset<Key, Hash, KeyEqual>& rhs)
        {
            return lhs != rhs;
        }
        
        /* 重载 leptstl 的 swap*/
    template <typename Key, typename Hash, typename KeyEqual, typename Alloc>
        void swap(unordered_multiset<Key, Hash, KeyEqual>& lhs,
                  unordered_multiset<Key, Hash, KeyEqual>& rhs)
        {
            lhs.swap(rhs);
        }

}   /*namespace leptstl*/

#endif  /*LEPTSTL_UNORDERED_SET_H__*/

