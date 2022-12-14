/**
 * @file base_string.h
 * @author ghy (ghy_mike@163.com)
 * @brief string 类的实现
 * 
 * @version 1.0
 * @date 2022-08-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#ifndef _BASE_STRING_H_
#define _BASE_STRING_H_

#include "../algorithm/algorithm.h"

#include <iostream>

namespace GHYSTL{

// 萃取器
template<class CharType>
struct char_traits
{
    typedef CharType char_type;

    static size_t length(const char_type* str){
        size_t len = 0;
        for(; *str != char_type(0); ++str) // char_type(0) ascii 空字符 null 相当于 \0
            ++len;
        return len;
    }

    static int compare(const char_type* s1, const char_type* s2, size_t n){
        for(; n != 0; --n, ++s1, ++s2){
            if(*s1 < *s2)
                return -1;
            if(*s2 < *s1)
                return 1;
        }

        return 0;
    }

    // src 和 dst 没有重叠
    static char_type* copy(char_type* dst, const char_type* src, size_t n){
        GHYSTL_DEBUG(src + n <= dst || dst + n <= src);
        char_type* r = dst;

        for(; n != 0; --n)
            *dst++ = *src++;
        return r;
    }

    // src 和 dst 重叠
    static char_type* move(char_type* dst, const char_type* src, size_t n){
        char_type* r = dst;

        if(dst < src){
            for(; n != 0; --n, ++dst, ++src)
                *dst = *src;
        }
        else if(src < dst){
            dst += n;
            src += n;
            for(; n != 0; --n)
                *--dst = *--src;
        }

        return r;
    }

    static char_type* fill(char_type* dst, char_type ch, size_t count){
        char_type* r = dst;
        for(; count > 0; --count, ++dst)
            *dst = ch;
        return r;
    }
};

// 特化 char_traits<char>
// 使用了 标准函数
template <> 
struct char_traits<char>
{
  typedef char char_type;

  static size_t length(const char_type* str) noexcept
  { return std::strlen(str); }

  static int compare(const char_type* s1, const char_type* s2, size_t n) noexcept
  { return std::memcmp(s1, s2, n); }

  static char_type* copy(char_type* dst, const char_type* src, size_t n) noexcept
  {
    GHYSTL_DEBUG(src + n <= dst || dst + n <= src);
    return static_cast<char_type*>(std::memcpy(dst, src, n));
  }

  static char_type* move(char_type* dst, const char_type* src, size_t n) noexcept
  {
    return static_cast<char_type*>(std::memmove(dst, src, n));
  }

  static char_type* fill(char_type* dst, char_type ch, size_t count) noexcept
  { 
    return static_cast<char_type*>(std::memset(dst, ch, count));
  }
};

// 特化. char_traits<wchar_t>
// 使用了标准函数
template <>
struct char_traits<wchar_t>
{
  typedef wchar_t char_type;

  static size_t length(const char_type* str) noexcept
  {
    return std::wcslen(str);
  }

  static int compare(const char_type* s1, const char_type* s2, size_t n) noexcept
  {
    return std::wmemcmp(s1, s2, n);
  }

  static char_type* copy(char_type* dst, const char_type* src, size_t n) noexcept
  {
    GHYSTL_DEBUG(src + n <= dst || dst + n <= src);
    return static_cast<char_type*>(std::wmemcpy(dst, src, n));
  }

  static char_type* move(char_type* dst, const char_type* src, size_t n) noexcept
  {
    return static_cast<char_type*>(std::wmemmove(dst, src, n));
  }

  static char_type* fill(char_type* dst, char_type ch, size_t count) noexcept
  { 
    return static_cast<char_type*>(std::wmemset(dst, ch, count));
  }
};

// 特化. char_traits<char16_t>
template <>
struct char_traits<char16_t>
{
  typedef char16_t char_type;

  static size_t length(const char_type* str) noexcept
  {
    size_t len = 0;
    for (; *str != char_type(0); ++str)
      ++len;
    return len;
  }

  static int compare(const char_type* s1, const char_type* s2, size_t n) noexcept
  {
    for (; n != 0; --n, ++s1, ++s2)
    {
      if (*s1 < *s2)
        return -1;
      if (*s2 < *s1)
        return 1;
    }
    return 0;
  }

  static char_type* copy(char_type* dst, const char_type* src, size_t n) noexcept
  {
    GHYSTL_DEBUG(src + n <= dst || dst + n <= src);
    char_type* r = dst;
    for (; n != 0; --n, ++dst, ++src)
      *dst = *src;
    return r;
  }

  static char_type* move(char_type* dst, const char_type* src, size_t n) noexcept
  {
    char_type* r = dst;
    if (dst < src)
    {
      for (; n != 0; --n, ++dst, ++src)
        *dst = *src;
    }
    else if (src < dst)
    {
      dst += n;
      src += n;
      for (; n != 0; --n)
        *--dst = *--src;
    }
    return r;
  }

  static char_type* fill(char_type* dst, char_type ch, size_t count) noexcept
  {
    char_type* r = dst;
    for (; count > 0; --count, ++dst)
      *dst = ch;
    return r;
  }
};

// 特化. char_traits<char32_t>
template <>
struct char_traits<char32_t>
{
  typedef char32_t char_type;

  static size_t length(const char_type* str) noexcept
  {
    size_t len = 0;
    for (; *str != char_type(0); ++str)
      ++len;
    return len;
  }

  static int compare(const char_type* s1, const char_type* s2, size_t n) noexcept
  {
    for (; n != 0; --n, ++s1, ++s2)
    {
      if (*s1 < *s2)
        return -1;
      if (*s2 < *s1)
        return 1;
    }
    return 0;
  }

  static char_type* copy(char_type* dst, const char_type* src, size_t n) noexcept
  {
    GHYSTL_DEBUG(src + n <= dst || dst + n <= src);
    char_type* r = dst;
    for (; n != 0; --n, ++dst, ++src)
      *dst = *src;
    return r;
  }

  static char_type* move(char_type* dst, const char_type* src, size_t n) noexcept
  {
    char_type* r = dst;
    if (dst < src)
    {
      for (; n != 0; --n, ++dst, ++src)
        *dst = *src;
    }
    else if (src < dst)
    {
      dst += n;
      src += n;
      for (; n != 0; --n)
        *--dst = *--src;
    }
    return r;
  }

  static char_type* fill(char_type* dst, char_type ch, size_t count) noexcept
  {
    char_type* r = dst;
    for (; count > 0; --count, ++dst)
      *dst = ch;
    return r;
  }
};

/************************************************** string 类 ***********************************************************/

template<class CharType, class CharTraits = GHYSTL::char_traits<CharType>>
class base_string{
public:
    typedef CharTraits                                  traits_type;
    typedef CharTraits                                  char_traits;

    typedef GHYSTL::allocator<CharType>                 allocator_type;
    typedef GHYSTL::allocator<CharType>                 data_allocator;

    typedef typename allocator_type::value_type         value_type;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::size_type          size_type;
    typedef typename allocator_type::difference_type    difference_type;

    typedef value_type*                                 iterator;
    typedef const value_type*                           const_iterator;
    typedef GHYSTL::reverse_iterator<iterator>          reverse_iterator;
    typedef GHYSTL::reverse_iterator<const_iterator>    const_reverse_iterator;

    allocator_type get_allocator() { return allocator_type(); }
    
    // 初始化 basi_string 尝试分配的最小 buffer 大小，可能被忽略
    // 可能是因为我电脑的内存问题,设置 32 会一直出问题 
    size_type STRING_INIT_SIZE = 35;

    // 类加载前先进行静态检查
    static_assert(GHYSTL::is_pod<CharType>::value, "Character type of basi_string must be a POD");
    static_assert(GHYSTL::is_same<CharType, typename traits_type::char_type>::value,
                "CharType must be same as traits_type::char_type");

public:
    // 字符串末尾的值
    // if (str.find('a') != string::npos) { /* do something */ }
    static constexpr size_type npos = static_cast<size_type>(-1);

private:
  iterator  buffer_;  // 储存字符串的起始位置
  size_type size_;    // 大小
  size_type cap_;     // 容量

public:
  /*-------------------------------------- 构造、复制、移动、析构函数 -----------------------------------------------*/

    base_string() noexcept { try_init(); } // 默认构造函数

    // 用 ch 字符填充字符串
    base_string(size_type n, value_type ch) : buffer_(nullptr), size_(0), cap_(0) {
        fill_init(n, ch);
    }

    // 从另一个字符串起始位置， 到  起始位置 + pos 初始化
    base_string(const base_string& other, size_type pos) : buffer_(nullptr), size_(0), cap_(0) {
        init_from(other.buffer_, pos, other.size_ - pos);
    }

    // 从另一个字符串起始位置， 到  起始位置 + pos 初始化
    base_string(const base_string& other, size_type pos, size_type count) :buffer_(nullptr), size_(0), cap_(0) {
        init_from(other.buffer_, pos, count);
    }


    base_string(const_pointer str) : buffer_(nullptr), size_(0), cap_(0) {
        init_from(str, 0, char_traits::length(str));
    }

    base_string(const_pointer str, size_type count) : buffer_(nullptr), size_(0), cap_(0) {
        init_from(str, 0, count);
    }

    template <class Iter,  typename GHYSTL::enable_if<GHYSTL::is_input_iterator<Iter>::value, int>::type = 0>
    base_string(Iter first, Iter last) : buffer_(nullptr), size_(0), cap_(0) {
        copy_init(first, last, GHYSTL::iterator_category(first)); 
    }

    base_string(const base_string& rhs) : buffer_(nullptr), size_(0), cap_(0){
        init_from(rhs.buffer_, 0, rhs.size_);
    }

    base_string(base_string&& rhs) noexcept : buffer_(rhs.buffer_), size_(rhs.size_), cap_(rhs.cap_) {
        rhs.buffer_ = nullptr;
        rhs.size_ = 0;
        rhs.cap_ = 0;
    }

    base_string& operator=(const base_string& rhs);
    base_string& operator=(base_string&& rhs) noexcept;

    base_string& operator=(const_pointer str);
    base_string& operator=(value_type ch);

    ~base_string() { destroy_buffer(); }

public:
  /*---------------------------------------------------- 迭代器相关操作 ------------------------------------*/
    iterator begin() noexcept { return buffer_; }
    iterator end()   noexcept { return buffer_ + size_; }

    const_iterator begin() const noexcept { return buffer_; }
    const_iterator end()   const noexcept { return buffer_ + size_; }

    const_iterator cbegin()  const noexcept { return begin(); }
    const_iterator cend()    const noexcept { return end(); }

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    reverse_iterator rend()   noexcept { return reverse_iterator(begin()); }

    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator rend()   const noexcept { return const_reverse_iterator(begin()); }

    const_reverse_iterator crbegin() const noexcept { return rbegin(); }
    const_reverse_iterator crend()   const noexcept { return rend(); }


/*---------------------------------------------- 容量相关操作 ---------------------------------------------------*/
    bool empty() const noexcept { return size_ == 0; }

    size_type size() const noexcept { return size_; }

    size_type length()  const noexcept { return size_; }

    size_type capacity() const noexcept { return cap_; }

    size_type max_size() const noexcept { return static_cast<size_type>(-1); }

    void reserve(size_type n); // 增加容量
    void shrink_to_fit();

/*--------------------------------------------- 访问元素相关操作 (重写了运算符) -----------------------------------*/
    reference operator[](size_type n) {
        GHYSTL_DEBUG(n <= size_);
        if (n == size_)
            *(buffer_ + n) = value_type();
        return *(buffer_ + n); 
    }

    const_reference operator[](size_type n) const{ 
        GHYSTL_DEBUG(n <= size_);
        if (n == size_)
            *(buffer_ + n) = value_type();
        return *(buffer_ + n);
    }

    reference at(size_type n) { 
    THROW_OUT_OF_RANGE_IF(n >= size_, "base_string<Char, Traits>::at()"
                        "subscript out of range");
        return (*this)[n]; 
    }

    const_reference at(size_type n) const {
        THROW_OUT_OF_RANGE_IF(n >= size_, "base_string<Char, Traits>::at()"
                            "subscript out of range");
        return (*this)[n]; 
    }

    reference front() { 
        GHYSTL_DEBUG(!empty());
        return *begin(); 
    }
    const_reference front() const { 
        GHYSTL_DEBUG(!empty());
        return *begin(); 
    }

    reference back() {
        GHYSTL_DEBUG(!empty()); 
        return *(end() - 1); 
    }
    const_reference back() const {
        GHYSTL_DEBUG(!empty()); 
        return *(end() - 1);
    }

    const_pointer data()  const noexcept { return to_raw_pointer(); }
    const_pointer c_str() const noexcept { return to_raw_pointer(); }

/*-------------------------------------------  添加删除相关操作 --------------------------------------*/
// insert
    iterator insert(const_iterator pos, value_type ch);
    
    iterator insert(const_iterator pos, size_type count, value_type ch);

    template <class Iter>
    iterator insert(const_iterator pos, Iter first, Iter last);


// push_back / pop_back
    void push_back(value_type ch) { append(1, ch); }

    void pop_back() {
        GHYSTL_DEBUG(!empty());
        --size_;
    }

// append
    base_string& append(size_type count, value_type ch);

    base_string& append(const base_string& str) { return append(str, 0, str.size_); }

    base_string& append(const base_string& str, size_type pos) { return append(str, pos, str.size_ - pos); }

    base_string& append(const base_string& str, size_type pos, size_type count);

    base_string& append(const_pointer s) { return append(s, char_traits::length(s)); }

    base_string& append(const_pointer s, size_type count);

    template <class Iter, typename GHYSTL::enable_if<GHYSTL::is_input_iterator<Iter>::value, int>::type = 0>
    base_string& append(Iter first, Iter last) {
        return append_range(first, last); 
    }

// erase /clear
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);

// resize
    void resize(size_type count) { resize(count, value_type()); }

    void resize(size_type count, value_type ch);

    void clear() noexcept { size_ = 0; } // 因为是pod类型，不用析构，后面空间可以重用

/*------------------------------------------------ 常规操作 ------------------------------------------------------*/

// compare
    int compare(const base_string& other) const;

    int compare(size_type pos1, size_type count1, const base_string& other) const;

    int compare(size_type pos1, size_type count1, const base_string& other, size_type pos2, size_type count2 = npos) const;

    int compare(const_pointer s) const;

    int compare(size_type pos1, size_type count1, const_pointer s) const;

    int compare(size_type pos1, size_type count1, const_pointer s, size_type count2) const;

// substr
    base_string substr(size_type index, size_type count = npos) { // 从某个位置开始截取到字符串末尾
        count = count < size_ - index ? count : size_ - index;
        return base_string(buffer_ + index, buffer_ + index + count);
    }


// replace
    base_string& replace(size_type pos, size_type count, const base_string& str) {
        THROW_OUT_OF_RANGE_IF(pos > size_, "base_string<Char, Traits>::replace's pos out of range");
        return replace_cstr(buffer_ + pos, count, str.buffer_, str.size_);
    }

    base_string& replace(const_iterator first, const_iterator last, const base_string& str) {
        GHYSTL_DEBUG(begin() <= first && last <= end() && first <= last);
        return replace_cstr(first, static_cast<size_type>(last - first), str.buffer_, str.size_);
    }

    base_string& replace(size_type pos, size_type count, const_pointer str) {
        THROW_OUT_OF_RANGE_IF(pos > size_, "base_string<Char, Traits>::replace's pos out of range");
        return replace_cstr(buffer_ + pos, count, str, char_traits::length(str));
    }

    base_string& replace(const_iterator first, const_iterator last, const_pointer str) {
        GHYSTL_DEBUG(begin() <= first && last <= end() && first <= last);
        return replace_cstr(first, static_cast<size_type>(last - first), str, char_traits::length(str));
    }

    base_string& replace(size_type pos, size_type count, const_pointer str, size_type count2) {
        THROW_OUT_OF_RANGE_IF(pos > size_, "base_string<Char, Traits>::replace's pos out of range");
        return replace_cstr(buffer_ + pos, count, str, count2);
    }

    base_string& replace(const_iterator first, const_iterator last, const_pointer str, size_type count) {
        GHYSTL_DEBUG(begin() <= first && last <= end() && first <= last);
        return replace_cstr(first, static_cast<size_type>(last - first), str, count);

    }

    base_string& replace(size_type pos, size_type count, size_type count2, value_type ch) {
        THROW_OUT_OF_RANGE_IF(pos > size_, "base_string<Char, Traits>::replace's pos out of range");
        return replace_fill(buffer_ + pos, count, count2, ch);
    }

    base_string& replace(const_iterator first, const_iterator last, size_type count, value_type ch) {
        GHYSTL_DEBUG(begin() <= first && last <= end() && first <= last);
        return replace_fill(first, static_cast<size_type>(last - first), count, ch);
    }

    base_string& replace(size_type pos1, size_type count1, const base_string& str,
                        size_type pos2, size_type count2 = npos)
    {
        THROW_OUT_OF_RANGE_IF(pos1 > size_ || pos2 > str.size_,
                                "base_string<Char, Traits>::replace's pos out of range");
        return replace_cstr(buffer_ + pos1, count1, str.buffer_ + pos2, count2);
    }

    template <class Iter, typename GHYSTL::enable_if<GHYSTL::is_input_iterator<Iter>::value, int>::type = 0>
    base_string& replace(const_iterator first, const_iterator last, Iter first2, Iter last2) {
        GHYSTL_DEBUG(begin() <= first && last <= end() && first <= last);
        return replace_copy(first, last, first2, last2);
    }

// reverse
    void reverse() noexcept;

// swap
    void swap(base_string& rhs) noexcept;

/*-------------------------------------------------- 查找相关操作 ---------------------------------------*/

    // find
    size_type find(value_type ch, size_type pos = 0)                             const noexcept;
    size_type find(const_pointer str, size_type pos = 0)                         const noexcept;
    size_type find(const_pointer str, size_type pos, size_type count)            const noexcept;
    size_type find(const base_string& str, size_type pos = 0)                   const noexcept;

    // rfind
    size_type rfind(value_type ch, size_type pos = npos)                         const noexcept;
    size_type rfind(const_pointer str, size_type pos = npos)                     const noexcept;
    size_type rfind(const_pointer str, size_type pos, size_type count)           const noexcept;
    size_type rfind(const base_string& str, size_type pos = npos)               const noexcept;

    // find_first_of
    size_type find_first_of(value_type ch, size_type pos = 0)                    const noexcept;
    size_type find_first_of(const_pointer s, size_type pos = 0)                  const noexcept;
    size_type find_first_of(const_pointer s, size_type pos, size_type count)     const noexcept;
    size_type find_first_of(const base_string& str, size_type pos = 0)          const noexcept;

    // find_first_not_of
    size_type find_first_not_of(value_type ch, size_type pos = 0)                const noexcept;
    size_type find_first_not_of(const_pointer s, size_type pos = 0)              const noexcept;
    size_type find_first_not_of(const_pointer s, size_type pos, size_type count) const noexcept;
    size_type find_first_not_of(const base_string& str, size_type pos = 0)      const noexcept;

    // find_last_of
    size_type find_last_of(value_type ch, size_type pos = 0)                     const noexcept;
    size_type find_last_of(const_pointer s, size_type pos = 0)                   const noexcept;
    size_type find_last_of(const_pointer s, size_type pos, size_type count)      const noexcept;
    size_type find_last_of(const base_string& str, size_type pos = 0)           const noexcept;

    // find_last_not_of
    size_type find_last_not_of(value_type ch, size_type pos = 0)                 const noexcept;
    size_type find_last_not_of(const_pointer s, size_type pos = 0)               const noexcept;
    size_type find_last_not_of(const_pointer s, size_type pos, size_type count)  const noexcept;
    size_type find_last_not_of(const base_string& str, size_type pos = 0)       const noexcept;


    // count
    size_type count(value_type ch, size_type pos = 0) const noexcept;

public:
    // 重载 operator+= 
    base_string& operator+=(const base_string& str) { return append(str); }

    base_string& operator+=(value_type ch) { return append(1, ch); }

    base_string& operator+=(const_pointer str) { return append(str, str + char_traits::length(str)); }

    // 重载 operator >> / operatror <<
    friend std::istream& operator >> (std::istream& is, base_string& str) {
        value_type* buf = new value_type[4096];
        is >> buf;
        base_string tmp(buf);
        str = std::move(tmp);
        delete[] buf;
        return is;
    }

    friend std::ostream& operator << (std::ostream& os, const base_string& str) {
        for (size_type i = 0; i < str.size_; ++i)
            os << *(str.buffer_ + i);
        return os;
    }

private:
/*---------------------------------------------- 底层操作 ------------------------------------*/

// init / destroy 
    void try_init() noexcept;

    void fill_init(size_type n, value_type ch);

    template <class Iter>
    void copy_init(Iter first, Iter last, GHYSTL::input_iterator_tag);

    template <class Iter>
    void copy_init(Iter first, Iter last, GHYSTL::forward_iterator_tag);

    void init_from(const_pointer src, size_type pos, size_type n);

    void destroy_buffer();

// get raw pointer
    const_pointer to_raw_pointer() const;

// shrink_to_fit
    void reinsert(size_type size);

// append
    template <class Iter>
    base_string& append_range(Iter first, Iter last);

// compare
    int compare_cstr(const_pointer s1, size_type n1, const_pointer s2, size_type n2) const;

// replace
    base_string& replace_cstr(const_iterator first, size_type count1, const_pointer str, size_type count2);

    base_string& replace_fill(const_iterator first, size_type count1, size_type count2, value_type ch);

    template <class Iter>
    base_string& replace_copy(const_iterator first, const_iterator last, Iter first2, Iter last2);

// reallocate
    void reallocate(size_type need);

    iterator reallocate_and_fill(iterator pos, size_type n, value_type ch);

    iterator reallocate_and_copy(iterator pos, const_iterator first, const_iterator last);
};

/****************************************** 方法的实现  ***********************************************/

// 复制赋值操作符
    template<class CharType, class CharTraits>
    base_string<CharType, CharTraits>&
    base_string<CharType, CharTraits>::
    operator=(const base_string& rhs){
        if(this != &rhs){
            base_string tmp(rhs);
            swap(tmp);
        }
        return *this;
    }
    
// 移动赋值操作符
    template<class CharType, class CharTraits>
    base_string<CharType, CharTraits>&
    base_string<CharType, CharTraits>::
    operator=(base_string&& rhs) noexcept {
        destroy_buffer();
        buffer_ = rhs.buffer_;
        size_ = rhs.size_;
        cap_ = rhs.cap_;
        rhs.buffer_ = nullptr;
        rhs.size_ = 0;
        rhs.cap_ = 0;
        return *this;
    }

// 用一个字符串赋值
    template<class CharType, class CharTraits>
    base_string<CharType, CharTraits>&
    base_string<CharType, CharTraits>::
    operator=(const_pointer str){
        const size_type len = char_traits::length(str);

        if(cap_ < len){
            auto new_buffer = data_allocator::allocate(len + 1);
            data_allocator::deallocate(buffer_);
            buffer_ = new_buffer;
            cap_ = len + 1;
        }

        char_traits::copy(buffer_, str, len);
        size_ = len;
        return *this;
    }

// 用一个字符赋值
    template<class CharType, class CharTraits>
    base_string<CharType, CharTraits>&
    base_string<CharType, CharTraits>::
    operator=(value_type ch){
        if(cap_ < 1){
            auto new_buffer = data_allocator::allocate(2);
            data_allocator::deallocate(buffer_);
            buffer_ = new_buffer;
            cap_ = 2;
        }

        *buffer_ = ch;
        size_ = 1;
        return *this;
    }

// 预留储存空间, 增加容量
    template<class CharType, class CharTraits>
    void base_string<CharType, CharTraits>::
    reserve(size_type n) {
        if(cap_ < n){
            THROW_LENGTH_ERROR_IF(n > max_size(), "n can not larger than max_size()"
                          "in base_string<Char,Traits>::reserve(n)");
            auto new_buffer = data_allocator::allocate(n);
            char_traits::move(new_buffer, buffer_, size_);
            buffer_ = new_buffer;
            cap_ = n;
        }
    }

// 减少不用的空间
    template<class CharType, class CharTraits>
    void base_string<CharType, CharTraits>::
    shrink_to_fit(){
        if(size_ != cap_)
            reinsert(size_);
    }

//在 pos 处插入一个元素
    template<class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::iterator
    base_string<CharType, CharTraits>::
    insert(const_iterator pos, value_type ch){
        iterator r = const_cast<iterator>(pos);
        if(size_ == cap_)
            reallocate_and_fill(r, 1, ch);
        char_traits::move(r + 1, r, end() - r);
        ++size_;
        *r = ch;
        return r;
    }

// 在 pos 处插入 n 个元素
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::iterator
    base_string<CharType, CharTraits>::
    insert(const_iterator pos, size_type count, value_type ch){
        iterator r = const_cast<iterator>(pos);
        if (count == 0)
            return r;

        if (cap_ - size_ < count)
            return reallocate_and_fill(r, count, ch);
        
        if (pos == end()) {
            char_traits::fill(end(), ch, count);
            size_ += count;
            return r;
        }

        char_traits::move(r + count, r, count);
        char_traits::fill(r, ch, count);
        size_ += count;
        return r;
    }

// 在 pos 处插入 [first, last) 内的元素
    template <class CharType, class CharTraits>
    template <class Iter>
    typename base_string<CharType, CharTraits>::iterator
    base_string<CharType, CharTraits>::
    insert(const_iterator pos, Iter first, Iter last){
        iterator r = const_cast<iterator>(pos);
        const size_type len = GHYSTL::distance(first, last);

        if (len == 0)
            return r;

        if (cap_ - size_ < len)
            return reallocate_and_copy(r, first, last);

        if (pos == end()){
            char_traits::copy(end(), first, len);
            size_ += len;
            return r;
        }

        char_traits::move(r + len, r, len);
        char_traits::copy(r, first, len);
        size_ += len;
        return r;
    }

// 在末尾添加 count 个 ch
    template <class CharType, class CharTraits>
    base_string<CharType, CharTraits>& 
    base_string<CharType, CharTraits>::
    append(size_type count, value_type ch){
        THROW_LENGTH_ERROR_IF(size_ > max_size() - count,
                            "base_string<Char, Tratis>'s size too big");
        if (cap_ - size_ < count)
            reallocate(count);
        
        char_traits::fill(buffer_ + size_, ch, count);
        size_ += count;
        return *this;
    }

// 在末尾添加 [str[pos] str[pos+count]) 一段
    template <class CharType, class CharTraits>
    base_string<CharType, CharTraits>& 
    base_string<CharType, CharTraits>::
    append(const base_string& str, size_type pos, size_type count) {
        THROW_LENGTH_ERROR_IF(size_ > max_size() - count,
                            "base_string<Char, Tratis>'s size too big"); 

        if (count == 0)
            return *this;
        if (cap_ - size_ < count)
            reallocate(count);

        char_traits::copy(buffer_ + size_, str.buffer_ + pos, count);
        size_ += count;
        return *this;
    }

// 在末尾添加 [s, s+count) 一段
    template <class CharType, class CharTraits>
    base_string<CharType, CharTraits>& 
    base_string<CharType, CharTraits>::
    append(const_pointer s, size_type count) {
        THROW_LENGTH_ERROR_IF(size_ > max_size() - count,
                                "base_string<Char, Tratis>'s size too big");
        if (cap_ - size_ < count)
            reallocate(count);        
   
        char_traits::copy(buffer_ + size_, s, count);
        size_ += count;
        return *this;
    }

// 删除 pos 处的元素
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::iterator
    base_string<CharType, CharTraits>::
    erase(const_iterator pos) {
        GHYSTL_DEBUG(pos != end());

        iterator r = const_cast<iterator>(pos);
        char_traits::move(r, pos + 1, end() - pos - 1);
        --size_;
        return r;
    }

// 删除 [first, last) 的元素
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::iterator
    base_string<CharType, CharTraits>::
    erase(const_iterator first, const_iterator last) {
        if (first == begin() && last == end()) {
            clear();
            return end();
        }

        const size_type n = end() - last;
        iterator r = const_cast<iterator>(first);
        char_traits::move(r, last, n); // 把 last 后面得元素移动到 first 处
        size_ -= (last - first);
        return r;
    }

// 重置容器大小
    template <class CharType, class CharTraits>
    void base_string<CharType, CharTraits>::
    resize(size_type count, value_type ch) {
        if (count < size_)
            erase(buffer_ + count, buffer_ + size_); // 比原来小，直接删除多余得
        else
            append(count - size_, ch); // 比原来大， 在末尾填充 ch 字符 
    }

// 比较两个 base_string，小于返回 -1，大于返回 1，等于返回 0
    template <class CharType, class CharTraits>
    int base_string<CharType, CharTraits>::
    compare(const base_string& other) const {
        return compare_cstr(buffer_, size_, other.buffer_, other.size_);
    }

// 从 pos1 下标开始的 count1 个字符跟另一个 base_string 比较
    template <class CharType, class CharTraits>
    int base_string<CharType, CharTraits>::
    compare(size_type pos1, size_type count1, const base_string& other) const {
        auto n1 = GHYSTL::min(count1, size_ - pos1);
        return compare_cstr(buffer_ + pos1, n1, other.buffer_, other.size_);
    }

// 从 pos1 下标开始的 count1 个字符跟另一个 base_string 下标 pos2 开始的 count2 个字符比较
    template <class CharType, class CharTraits>
    int base_string<CharType, CharTraits>::
    compare(size_type pos1, size_type count1, 
            const base_string& other, size_type pos2, size_type count2) const
    {
        auto n1 = GHYSTL::min(count1, size_ - pos1);
        auto n2 = GHYSTL::min(count2, other.size_ - pos2);
        return compare_cstr(buffer_ + pos1, n1, other.buffer_ + pos2, n2);
    }

// 跟一个字符串比较
    template <class CharType, class CharTraits>
    int base_string<CharType, CharTraits>::
    compare(const_pointer s) const {
        auto n2 = char_traits::length(s);
        return compare_cstr(buffer_, size_, s, n2);
    }

// 从下标 pos1 开始的 count1 个字符跟另一个字符串比较
    template <class CharType, class CharTraits>
    int base_string<CharType, CharTraits>::
    compare(size_type pos1, size_type count1, const_pointer s) const {
        auto n1 = GHYSTL::min(count1, size_ - pos1);
        auto n2 = char_traits::length(s);
        return compare_cstr(buffer_ + pos1, n1, s, n2);
    }

// 从下标 pos1 开始的 count1 个字符跟另一个字符串的前 count2 个字符比较
    template <class CharType, class CharTraits>
    int base_string<CharType, CharTraits>::
    compare(size_type pos1, size_type count1, const_pointer s, size_type count2) const
    {
        auto n1 = GHYSTL::min(count1, size_ - pos1);
        return compare_cstr(buffer_ + pos1, n1, s, count2);
    }

// 反转 base_string
    template<class CharType, class CharTraits>
    void base_string<CharType, CharTraits>::
    reverse() noexcept {
        // 双指针，一个在前，一个在后，两个不相交的时候， 就交换
        for(auto i = begin(), j = end(); i < j; )
            GHYSTL::iter_swap(i++, --j);
    }

// 交换两个 base_string
    template <class CharType, class CharTraits>
    void base_string<CharType, CharTraits>::
    swap(base_string& rhs) noexcept {
        if (this != &rhs) {
            GHYSTL::swap(buffer_, rhs.buffer_);
            GHYSTL::swap(size_, rhs.size_);
            GHYSTL::swap(cap_, rhs.cap_);
        }
    }

// 从下标 pos 开始查找字符为 ch 的元素，若找到返回其下标，否则返回 npos
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find(value_type ch, size_type pos) const noexcept {
        for (auto i = pos; i < size_; ++i) {
            if (*(buffer_ + i) == ch)
                return i;
        }

        return npos;
    }

// 从下标 pos 开始查找字符串 str，若找到返回起始位置的下标，否则返回 npos
    template<class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find(const_pointer str, size_type pos) const noexcept { // 指针类型
        const auto len = char_traits::length(str);

        if(len == 0) 
            return pos;

        if(size_ - pos < len)
            return npos;
        
        const auto left = size_ - len;
        for(auto i = pos; i <= left; ++i){ // 典型的滑动窗口
            if(*(buffer_ + i) == *str){
                size_type j = 1;
                for(; j < len; ++j){
                    if(*(buffer_ + i + j) != *(str + j))
                        break;
                }

                if(j == len)
                    return i;
            }
        }
        
        return npos;
    }


// 从下标 pos 开始查找字符串 str 的前 count 个字符，若找到返回起始位置的下标，否则返回 npos
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find(const_pointer str, size_type pos, size_type count) const noexcept
    {
        if (count == 0)
            return pos;

        if (size_ - pos < count)
            return npos;

        const auto left = size_ - count;
        for (auto i = pos; i <= left; ++i)
        {
            if (*(buffer_ + i) == *str)
            {
                size_type j = 1;
                for (; j < count; ++j){
                    if (*(buffer_ + i + j) != *(str + j))
                    break;
                }

                if (j == count)
                    return i;
            }
        }
        return npos;
    }

// 从下标 pos 开始查找字符串 str，若找到返回起始位置的下标，否则返回 npos
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find(const base_string& str, size_type pos) const noexcept // string类型
    {
        const size_type count = str.size_;
        if (count == 0)
            return pos;

        if (size_ - pos < count)
            return npos;

        const auto left = size_ - count;
        for (auto i = pos; i <= left; ++i)
        {
            if (*(buffer_ + i) == str.front())
            {
                size_type j = 1;
                for (; j < count; ++j)
                {
                    if (*(buffer_ + i + j) != str[j])
                    break;
                }
                if (j == count)
                    return i;
            }
        }
        return npos;
    }

// 从下标 pos 开始反向查找值为 ch 的元素，与 find 类似
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    rfind(value_type ch, size_type pos) const noexcept
    {
        if (pos >= size_)
            pos = size_ - 1;

        // pos 是 size_type (size_t) 类型，值始终大于等于0，无法判断 0 位置的字符
        for (auto i = pos; i != 0; --i) 
        {
            if (*(buffer_ + i) == ch)
                return i;
        }

        return front() == ch ? 0 : npos;
    }

// 从下标 pos 开始反向查找字符串 str，与 find 类似
    template<class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    rfind(const_pointer str, size_type pos) const noexcept {
        if(pos >= size_)
            pos = size_ - 1;
        
        const size_type len = char_traits::length(str);

        switch (len)
        {
            case 0:
                return pos;
            case 1:{
                for(auto i = pos; i != 0; --i){
                    if(*(buffer_ + i) == *str)
                        return i;
                }
                return front() == *str ? 0 : npos;
            }
            default:{
                // len >* 2
                for(auto i = pos; i >= len - 1; --i){ // 前面需要留够 len 个字符，否则一定不与 str 相等
                    if(*(buffer_ + i) == *(str + len - 1)){
                        size_type j = 1;
                        for(; j < len; ++j){
                            if(*(buffer_ + i - j) != *(str + len - j - 1)) // 从后向前比
                                break;
                        }

                        if(j == len)
                            return i - len + 1;
                    }
                }

                break;
            }
        }

        return npos;
    }

// 从下标 pos 开始反向查找字符串 str 前 count 个字符，与 find 类似
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    rfind(const_pointer str, size_type pos, size_type count) const noexcept
    {
        if (count == 0)
            return pos;

        if (pos >= size_)
            pos = size_ - 1;

        if (pos < count - 1)
            return npos;

        for (auto i = pos; i >= count - 1; --i)
        {
            if (*(buffer_ + i) == *(str + count - 1))
            {
                size_type j = 1;
                for (; j < count; ++j)
                {
                    if (*(buffer_ + i - j) != *(str + count - j - 1))
                    break;
                }
                if (j == count)
                    return i - count + 1;
                }
        }
        
        return npos;
    }

// 从下标 pos 开始反向查找字符串 str，与 find 类似
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    rfind(const base_string& str, size_type pos) const noexcept // 前面是指针类型，这个是 string 类型
    {
        const size_type count = str.size_;
        if (pos >= size_)
            pos = size_ - 1;

        if (count == 0)
            return pos;

        if (pos < count - 1)
            return npos;

        for (auto i = pos; i >= count - 1; --i)
        {
            if (*(buffer_ + i) == str[count - 1])
            {
                size_type j = 1;
                for (; j < count; ++j)
                {
                    if (*(buffer_ + i - j) != str[count - j - 1])
                        break;
                }
                if (j == count)
                    return i - count + 1;
            }
        }
        return npos;
    }

// 从下标 pos 开始查找 ch 出现的第一个位置
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find_first_of(value_type ch, size_type pos) const noexcept
    {
        for (auto i = pos; i < size_; ++i)
        {
            if (*(buffer_ + i) == ch)
                return i;
        }
        return npos;
    }

// 从下标 pos 开始查找字符串 s 其中的一个字符出现的第一个位置
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find_first_of(const_pointer s, size_type pos) const noexcept
    {
        const size_type len = char_traits::length(s);

        for (auto i = pos; i < size_; ++i)
        {
            value_type ch = *(buffer_ + i);
            for (size_type j = 0; j < len; ++j)
            {
                if (ch == *(s + j))
                    return i;
            }
        }
        return npos;
    }

// 从下标 pos 开始查找字符串 s 到 s + count  中的一个字符出现的第一个位置
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find_first_of(const_pointer s, size_type pos, size_type count) const noexcept
    {
        for (auto i = pos; i < size_; ++i)
        {
            value_type ch = *(buffer_ + i);
            for (size_type j = 0; j < count; ++j)
            {
                if (ch == *(s + j))
                    return i;
            }
        }
        return npos;
    }

// 从下标 pos 开始查找字符串 str 其中一个字符出现的第一个位置
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find_first_of(const base_string& str, size_type pos) const noexcept
    {
        for (auto i = pos; i < size_; ++i)
        {
            value_type ch = *(buffer_ + i);
            for (size_type j = 0; j < str.size_; ++j)
            {
                if (ch == str[j])
                    return i;
            }
        }
        return npos;
    }

// 从下标 pos 开始查找与 ch 不相等的第一个位置
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find_first_not_of(value_type ch, size_type pos) const noexcept
    {
        for (auto i = pos; i < size_; ++i)
        {
            if (*(buffer_ + i) != ch)
                return i;
        }
        return npos;
    }

// 从下标 pos 开始查找与字符串 s 其中一个字符不相等的第一个位置
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find_first_not_of(const_pointer s, size_type pos) const noexcept
    {
        const size_type len = char_traits::length(s);

        for (auto i = pos; i < size_; ++i)
        {
            value_type ch = *(buffer_ + i);
            for (size_type j = 0; j < len; ++j)
            {
                if (ch != *(s + j))
                    return i;
            }
        }
        return npos;
    }

// 从下标 pos 开始查找与字符串 s 前 count 个字符中不相等的第一个位置
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find_first_not_of(const_pointer s, size_type pos, size_type count) const noexcept
    {
        for (auto i = pos; i < size_; ++i)
        {
            value_type ch = *(buffer_ + i);
            for (size_type j = 0; j < count; ++j)
            {
                if (ch != *(s + j))
                    return i;
            }
        }
        return npos;
    }

// 从下标 pos 开始查找与字符串 str 的字符中不相等的第一个位置
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find_first_not_of(const base_string& str, size_type pos) const noexcept
    {
        for (auto i = pos; i < size_; ++i)
        {
            value_type ch = *(buffer_ + i);
            for (size_type j = 0; j < str.size_; ++j)
            {
                if (ch != str[j])
                    return i;
            }
        }
        return npos;
    }

// 从下标 pos 开始查找与 ch 相等的最后一个位置
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find_last_of(value_type ch, size_type pos) const noexcept
    {
        for (auto i = size_ - 1; i >= pos; --i)
        {
            if (*(buffer_ + i) == ch)
                return i;
        }
        return npos;
    }

// 从下标 pos 开始查找与字符串 s 其中一个字符相等的最后一个位置
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find_last_of(const_pointer s, size_type pos) const noexcept
    {
        const size_type len = char_traits::length(s);
        for (auto i = size_ - 1; i >= pos; --i)
        {
            value_type ch = *(buffer_ + i);
            for (size_type j = 0; j < len; ++j)
            {
                if (ch == *(s + j))
                    return i;
            }
        }
        return npos;
    }

// 从下标 pos 开始查找与字符串 s 前 count 个字符中相等的最后一个位置
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find_last_of(const_pointer s, size_type pos, size_type count) const noexcept
    {
        for (auto i = size_ - 1; i >= pos; --i)
        {
            value_type ch = *(buffer_ + i);
            for (size_type j = 0; j < count; ++j)
            {
                if (ch == *(s + j))
                    return i;
            }
        }
        return npos;
    }

// 从下标 pos 开始查找与字符串 str 字符中相等的最后一个位置
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find_last_of(const base_string& str, size_type pos) const noexcept
    {
        for (auto i = size_ - 1; i >= pos; --i)
        {
            value_type ch = *(buffer_ + i);
            for (size_type j = 0; j < str.size_; ++j)
            {
                if (ch == str[j])
                    return i;
            }
        }
        return npos;
    }

// 从下标 pos 开始查找与 ch 字符不相等的最后一个位置
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find_last_not_of(value_type ch, size_type pos) const noexcept
    {
        for (auto i = size_ - 1; i >= pos; --i)
        {
            if (*(buffer_ + i) != ch)
                return i;
        }
        return npos;
    }

// 从下标 pos 开始查找与字符串 s 的字符中不相等的最后一个位置
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find_last_not_of(const_pointer s, size_type pos) const noexcept
    {
        const size_type len = char_traits::length(s);
        for (auto i = size_ - 1; i >= pos; --i)
        {
            value_type ch = *(buffer_ + i);
            for (size_type j = 0; j < len; ++j)
            {
                if (ch != *(s + j))
                    return i;
            }
        }
        return npos;
    }

// 从下标 pos 开始查找与字符串 s 前 count 个字符中不相等的最后一个位置
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find_last_not_of(const_pointer s, size_type pos, size_type count) const noexcept
    {
        for (auto i = size_ - 1; i >= pos; --i)
        {
            value_type ch = *(buffer_ + i);
            for (size_type j = 0; j < count; ++j)
            {
                if (ch != *(s + j))
                    return i;
            }
        }
        return npos;
    }

// 从下标 pos 开始查找与字符串 str 字符中不相等的最后一个位置
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    find_last_not_of(const base_string& str, size_type pos) const noexcept
    {
        for (auto i = size_ - 1; i >= pos; --i)
        {
            value_type ch = *(buffer_ + i);
            for (size_type j = 0; j < str.size_; ++j)
            {
                if (ch != str[j])
                    return i;
            }
        }
        return npos;
    }

// 返回从下标 pos 开始字符为 ch 的元素出现的次数
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::size_type
    base_string<CharType, CharTraits>::
    count(value_type ch, size_type pos) const noexcept
    {
        size_type n = 0;
        for (auto i = pos; i < size_; ++i)
        {
            if (*(buffer_ + i) == ch)
                ++n;
        }
        return n;
    }

/************************************************* 底层操作实现 *******************************************************/

// 尝试初始化一段 buffer，若分配失败则忽略，不会抛出异常
    template<class CharType, class CharTraits>
    void base_string<CharType, CharTraits>::
    try_init() noexcept {
        try{
            buffer_ = data_allocator::allocate(STRING_INIT_SIZE);
            size_ = 0;
            cap_ = 0;
        }
        catch(...){
            buffer_ = nullptr;
            size_ = 0;
            cap_ = 0;
            // 不抛异常
        }
    }

// fill_init 函数
    template<class CharType, class CharTraits>
    void base_string<CharType, CharTraits>::
    fill_init(size_type n, value_type ch){
        size_t init_size = GHYSTL::max(STRING_INIT_SIZE, n + 1);
        buffer_ = data_allocator::allocate(init_size);
        char_traits::fill(buffer_, ch, n);
        size_ = n;
        cap_ = init_size;
    }

// copy_init 函数
    template<class CharType, class CharTraits>
    template<class Iter>
    void base_string<CharType, CharTraits>::
    copy_init(Iter first, Iter last, GHYSTL::input_iterator_tag){
        size_type n = GHYSTL::distance(first, last);
        size_t init_size = GHYSTL::max(STRING_INIT_SIZE, n + 1);

        try{
            buffer_ = data_allocator::allocate(init_size);
            size_ = n;
            cap_ = init_size;
        }
        catch(...){
            buffer_ = nullptr;
            size_ = 0;
            cap_ = 0;
            throw;
        }

        for(; n > 0; --n, first++)
            append(first);
    }

    template<class CharType, class CharTraits>
    template<class Iter>
    void base_string<CharType, CharTraits>::
    copy_init(Iter first, Iter last, GHYSTL::forward_iterator_tag){
        size_type n = GHYSTL::distance(first, last);
        size_t init_size = GHYSTL::max(STRING_INIT_SIZE, n + 1);

        try{
            buffer_ = data_allocator::allocate(init_size);
            size_ = n;
            cap_ = init_size;
            char_traits::copy(buffer_, first, n);
        }
        catch(...){
            buffer_ = nullptr;
            size_ = 0;
            cap_ = 0;
            throw;
        }
    }

// init_from 函数
    template <class CharType, class CharTraits>
    void base_string<CharType, CharTraits>::
    init_from(const_pointer src, size_type pos, size_type count)
    {
        size_t init_size = GHYSTL::max(count + 1, STRING_INIT_SIZE);
        buffer_ = data_allocator::allocate(init_size);
        char_traits::copy(buffer_, src + pos, count);
        size_ = count;
        cap_ = init_size;
    }

// destroy_buffer 函数
    template <class CharType, class CharTraits>
    void base_string<CharType, CharTraits>::
    destroy_buffer()
    {
        if (buffer_ != nullptr)
        {
            data_allocator::deallocate(buffer_, cap_);
            buffer_ = nullptr;
            size_ = 0;
            cap_ = 0;
        }
    }

// to_raw_pointer 函数
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::const_pointer
    base_string<CharType, CharTraits>::
    to_raw_pointer() const
    {
        *(buffer_ + size_) = value_type(); // size 上的空间初始化成字符
        return buffer_;
    }

// reinsert 函数
    template <class CharType, class CharTraits>
    void base_string<CharType, CharTraits>::
    reinsert(size_type size)
    {
        auto new_buffer = data_allocator::allocate(size);

        try{
            char_traits::move(new_buffer, buffer_, size);
        }
        catch (...){
            data_allocator::deallocate(new_buffer);
        }

        buffer_ = new_buffer;
        size_ = size;
        cap_ = size;
    }

// append_range，末尾追加一段 [first, last) 内的字符
    template<class CharType, class CharTraits>
    template<class Iter>
    base_string<CharType, CharTraits>&
    base_string<CharType, CharTraits>::
    append_range(Iter first, Iter last){
        const size_type n = GHYSTL::distance(first, last);
        THROW_LENGTH_ERROR_IF(size_ > max_size() - n,
                        "base_string<Char, Tratis>'s size too big");
        if(cap_ - size_ < n)
            reallocate(n);

        char_traits::copy(buffer_ + size_, first, n);
        size_ += n;
        return *this;
    }

// 比较字符串
    template <class CharType, class CharTraits>
    int base_string<CharType, CharTraits>::
    compare_cstr(const_pointer s1, size_type n1, const_pointer s2, size_type n2) const
    {
        auto rlen = GHYSTL::min(n1, n2);
        auto res = char_traits::compare(s1, s2, rlen);
        if (res != 0) return res;
        if (n1 < n2) return -1;
        if (n1 > n2) return 1;
        return 0;
    }

// 把 first 开始的 count1 个字符替换成 str 开始的 count2 个字符
    template <class CharType, class CharTraits>
    base_string<CharType, CharTraits>& 
    base_string<CharType, CharTraits>::
    replace_cstr(const_iterator first, size_type count1, const_pointer str, size_type count2)
    {
        if (static_cast<size_type>(cend() - first) < count1) {
            count1 = cend() - first;
        }

        if (count1 < count2) {
            const size_type add = count2 - count1;
            THROW_LENGTH_ERROR_IF(size_ > max_size() - add,
                                "base_string<Char, Traits>'s size too big");

            if (add > cap_ - size_)
                reallocate(add);
            
            pointer r = const_cast<pointer>(first);
            char_traits::move(r + count2, first + count1, end() - (first + count1)); // 把 count1 的数据向后移动
            char_traits::copy(r, str, count2);// 把 str2 的数据放到本字符串中
            size_ += add;
        }
        else {
            pointer r = const_cast<pointer>(first);
            char_traits::move(r + count2, first + count1, end() - (first + count1)); // 把 count1 的数据向前移动 
            char_traits::copy(r, str, count2);// 把 str2 的数据放到本字符串中
            size_ -= (count1 - count2);
        }

        return *this;
    }

// 把 first 开始的 count1 个字符替换成 count2 个 ch 字符
    template <class CharType, class CharTraits>
    base_string<CharType, CharTraits>&
    base_string<CharType, CharTraits>::
    replace_fill(const_iterator first, size_type count1, size_type count2, value_type ch)
    {
        if (static_cast<size_type>(cend() - first) < count1)
            count1 = cend() - first;
        
        if (count1 < count2)
        {
            const size_type add = count2 - count1;
            THROW_LENGTH_ERROR_IF(size_ > max_size() - add,
                                "base_string<Char, Traits>'s size too big");
            if (add > cap_ - size_)
                reallocate(add);
            
            pointer r = const_cast<pointer>(first);
            char_traits::move(r + count2, first + count1, end() - (first + count1));
            char_traits::fill(r, ch, count2);
            size_ += add;
        }
        else{
            pointer r = const_cast<pointer>(first);
            char_traits::move(r + count2, first + count1, end() - (first + count1));
            char_traits::fill(r, ch, count2);
            size_ -= (count1 - count2);
        }
        return *this;
    }

// 把 [first, last) 的字符替换成 [first2, last2)
    template <class CharType, class CharTraits>
    template <class Iter>
    base_string<CharType, CharTraits>&
    base_string<CharType, CharTraits>::
    replace_copy(const_iterator first, const_iterator last, Iter first2, Iter last2)
    {
        size_type len1 = last - first;
        size_type len2 = last2 - first2;
        if (len1 < len2)
        {
            const size_type add = len2 - len1;
            THROW_LENGTH_ERROR_IF(size_ > max_size() - add,
                                "base_string<Char, Traits>'s size too big");
            if (size_ > cap_ - add)
                reallocate(add);

            pointer r = const_cast<pointer>(first);
            char_traits::move(r + len2, first + len1, end() - (first + len1));
            char_traits::copy(r, first2, len2);
            size_ += add;
        }
        else
        {
            pointer r = const_cast<pointer>(first);
            char_traits::move(r + len2, first + len1, end() - (first + len1));
            char_traits::copy(r, first2, len2);
            size_ -= (len1 - len2);
        }
        return *this;
    }

// reallocate 函数
    template<class CharType, class CharTraits>
    void base_string<CharType, CharTraits>::
    reallocate(size_type need){
        const auto new_cap = GHYSTL::max(cap_ + need, cap_ + (cap_ >> 1));
        auto new_buffer = data_allocator::allocate(new_cap);
        char_traits::move(new_buffer, buffer_, size_);
        buffer_ = new_buffer;
        cap_ = new_cap;
    }

// reallocate_and_fill 函数
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::iterator
    base_string<CharType, CharTraits>::
    reallocate_and_fill(iterator pos, size_type n, value_type ch)
    {
        const auto r = pos - buffer_;
        const auto old_cap = cap_;
        const auto new_cap = GHYSTL::max(old_cap + n, old_cap + (old_cap >> 1));
        auto new_buffer = data_allocator::allocate(new_cap);
        auto e1 = char_traits::move(new_buffer, buffer_, r) + r;
        auto e2 = char_traits::fill(e1, ch, n) + n;
        char_traits::move(e2, buffer_ + r, size_ - r);
        data_allocator::deallocate(buffer_, old_cap);
        buffer_ = new_buffer;
        size_ += n;
        cap_ = new_cap;
        return buffer_ + r; // 返回插入点
    }

// reallocate_and_copy 函数
    template <class CharType, class CharTraits>
    typename base_string<CharType, CharTraits>::iterator
    base_string<CharType, CharTraits>::
    reallocate_and_copy(iterator pos, const_iterator first, const_iterator last)
    {
        const auto r = pos - buffer_;
        const auto old_cap = cap_;
        const size_type n = GHYSTL::distance(first, last);
        const auto new_cap = GHYSTL::max(old_cap + n, old_cap + (old_cap >> 1));
        auto new_buffer = data_allocator::allocate(new_cap);
        auto e1 = char_traits::move(new_buffer, buffer_, r) + r;
        auto e2 = char_traits::move(e1, first, n) + n;
        char_traits::move(e2, buffer_ + r, size_ - r);
        data_allocator::deallocate(buffer_, old_cap);
        buffer_ = new_buffer;
        size_ += n;
        cap_ = new_cap;
        return buffer_ + r;
    }

/*************************************** 重载全局操作符 **************************************************/
// 重载 operator+
template <class CharType, class CharTraits>
base_string<CharType, CharTraits>
operator+(const base_string<CharType, CharTraits>& lhs, 
          const base_string<CharType, CharTraits>& rhs)
{
  base_string<CharType, CharTraits> tmp(lhs);
  tmp.append(rhs);
  return tmp;
}

template <class CharType, class CharTraits>
base_string<CharType, CharTraits>
operator+(const CharType* lhs, const base_string<CharType, CharTraits>& rhs)
{
  base_string<CharType, CharTraits> tmp(lhs);
  tmp.append(rhs);
  return tmp;
}

template <class CharType, class CharTraits>
base_string<CharType, CharTraits>
operator+(CharType ch, const base_string<CharType, CharTraits>& rhs)
{
  base_string<CharType, CharTraits> tmp(1, ch);
  tmp.append(rhs);
  return tmp;
}

template <class CharType, class CharTraits>
base_string<CharType, CharTraits>
operator+(const base_string<CharType, CharTraits>& lhs, const CharType* rhs)
{
  base_string<CharType, CharTraits> tmp(lhs);
  tmp.append(rhs);
  return tmp;
}

template <class CharType, class CharTraits>
base_string<CharType, CharTraits>
operator+(const base_string<CharType, CharTraits>& lhs, CharType ch)
{
  base_string<CharType, CharTraits> tmp(lhs);
  tmp.append(1, ch);
  return tmp;
}

template <class CharType, class CharTraits>
base_string<CharType, CharTraits>
operator+(base_string<CharType, CharTraits>&& lhs,
          const base_string<CharType, CharTraits>& rhs)
{
  base_string<CharType, CharTraits> tmp(std::move(lhs));
  tmp.append(rhs);
  return tmp;
}

template <class CharType, class CharTraits>
base_string<CharType, CharTraits>
operator+(const base_string<CharType, CharTraits>& lhs,
          base_string<CharType, CharTraits>&& rhs)
{
  base_string<CharType, CharTraits> tmp(std::move(rhs));
  tmp.insert(tmp.begin(), lhs.begin(), lhs.end());
  return tmp;
}

template <class CharType, class CharTraits>
base_string<CharType, CharTraits>
operator+(base_string<CharType, CharTraits>&& lhs,
          base_string<CharType, CharTraits>&& rhs)
{
  base_string<CharType, CharTraits> tmp(std::move(lhs));
  tmp.append(rhs);
  return tmp;
}

template <class CharType, class CharTraits>
base_string<CharType, CharTraits>
operator+(const CharType* lhs, base_string<CharType, CharTraits>&& rhs)
{
  base_string<CharType, CharTraits> tmp(std::move(rhs));
  tmp.insert(tmp.begin(), lhs, lhs + char_traits<CharType>::length(lhs));
  return tmp;
}

template <class CharType, class CharTraits>
base_string<CharType, CharTraits>
operator+(CharType ch, base_string<CharType, CharTraits>&& rhs)
{
  base_string<CharType, CharTraits> tmp(std::move(rhs));
  tmp.insert(tmp.begin(), ch);
  return tmp;
}

template <class CharType, class CharTraits>
base_string<CharType, CharTraits>
operator+(base_string<CharType, CharTraits>&& lhs, const CharType* rhs)
{
  base_string<CharType, CharTraits> tmp(std::move(lhs));
  tmp.append(rhs);
  return tmp;
}

template <class CharType, class CharTraits>
base_string<CharType, CharTraits>
operator+(base_string<CharType, CharTraits>&& lhs, CharType ch)
{
  base_string<CharType, CharTraits> tmp(std::move(lhs));
  tmp.append(1, ch);
  return tmp;
}

// 重载比较操作符
template <class CharType, class CharTraits>
bool operator==(const base_string<CharType, CharTraits>& lhs,
                const base_string<CharType, CharTraits>& rhs)
{
  return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
}

template <class CharType, class CharTraits>
bool operator!=(const base_string<CharType, CharTraits>& lhs,
                const base_string<CharType, CharTraits>& rhs)
{
  return lhs.size() != rhs.size() || lhs.compare(rhs) != 0;
}

template <class CharType, class CharTraits>
bool operator<(const base_string<CharType, CharTraits>& lhs,
               const base_string<CharType, CharTraits>& rhs)
{
  return lhs.compare(rhs) < 0;
}

template <class CharType, class CharTraits>
bool operator<=(const base_string<CharType, CharTraits>& lhs,
                const base_string<CharType, CharTraits>& rhs)
{
  return lhs.compare(rhs) <= 0;
}

template <class CharType, class CharTraits>
bool operator>(const base_string<CharType, CharTraits>& lhs,
               const base_string<CharType, CharTraits>& rhs)
{
  return lhs.compare(rhs) > 0;
}

template <class CharType, class CharTraits>
bool operator>=(const base_string<CharType, CharTraits>& lhs,
                const base_string<CharType, CharTraits>& rhs)
{
  return lhs.compare(rhs) >= 0;
}

// 重载 GHYSTL 的 swap
template <class CharType, class CharTraits>
void swap(base_string<CharType, CharTraits>& lhs,
          base_string<CharType, CharTraits>& rhs) noexcept
{
  lhs.swap(rhs);
}

}
#endif