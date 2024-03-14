#ifndef BLOB_CLASS_H
#define BLOB_CLASS_H

#include <iterator>
#include <string>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <memory>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <stdexcept>

// Blob 的友元定义中需要用到
template <typename>
class BlobPtr;
// operator== 的定义中需要用到
template <typename>
class Blob;

template <typename T>
bool operator==(const Blob<T>&, const Blob<T>&);



template <typename T>
class Blob 
{
    // Blob 以及 BlobPtr 对应的实例化结果应该是相同的类型
    friend class BlobPtr<T>;

    friend bool operator==<T>
        (const Blob<T>&, const Blob<T>&);


public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;

    // 构造函数
    Blob();
    // 注意这里面又叠了一层来声明迭代器的 It
    template <typename It>
    Blob(It b, It e);
    Blob(T*, std::size_t);

    // 返回 BlobPtr 的第一个元素以及最后一个元素
    BlobPtr<T> begin() 
    { 
        return BlobPtr<T>(*this); 
    }
    BlobPtr<T> end() 
    {
        BlobPtr<T> ret = BlobPtr<T>(*this, data->size());
        return ret;
    }

    // Blob 中的元素个数
    size_type size() const { return data->size(); }
    // Blob 是否为空
    bool empty() const { return data->empty(); }

    // 添加与删除元素
    void push_back(const T& t) { data->push_back(t); }
    void pop_back();

    // 元素访问
    T& front();
    T& back();
    T& at(size_type);
    // 第一个 const 表示函数返回的是对常量的引用。
    // 第二个 const 表示该成员函数不会修改对象的内部状态。
    const T& front() const;
    const T& back() const;
    const T& at(size_type) const;

    T& operator[](size_type i);
    const T& operator[](size_type i) const;

    void swap(Blob& b) { data.swap(b.data); }

private:
    // 数据
    std::shared_ptr<std::vector<T>> data;
    // 如果 data[i] 不存在就抛出 msg
    void check(size_type i, const std::string& msg) const;
};


/*------------Blob 类的成员函数------------*/
// 构造函数
template <typename T>
Blob<T>::Blob(T* p, size_t n) :
    data(new std::vector<T>(p, p + n)) {}

template <typename T>
Blob<T>::Blob() :
    data(new std::vector<T>()) {}

// T 表示 class 的 typename，It 表示迭代器的 typename
template <typename T>
template <typename It>
Blob<T>::Blob(It b, It e) :
    data(new std::vector<T>(b, e)) {}

// 检测索引是否越界
template <typename T>
void Blob<T>::check(size_type i, const std::string& msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

// 元素成员访问
template <typename T>
T& Blob<T>::front()
{
    // 如果 vector 是空的，就会抛出如下所示的报错
    check(0, "front on empty Blob");
    return data->front();
}

template <typename T>
T& Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

template <typename T>
const T& Blob<T>::front() const
{
    check(0, "front on empty Blob");
    return data->front();
}

template <typename T>
const T& Blob<T>::back() const
{
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T>
T& Blob<T>::at(size_type i)
{
    // 检测索引是否越界
    check(i, "subscript out of range");
    return (*data)[i];  // 返回对应的值
}

template <typename T>
const T&
Blob<T>::at(size_type i) const
{
    check(i, "subscript out of range");
    return (*data)[i];
}

template <typename T>
T& Blob<T>::operator[](size_type i)
{
    // 检测索引是否越界
    check(i, "subscript out of range");
    return (*data)[i];
}

template <typename T>
const T&
Blob<T>::operator[](size_type i) const
{
    check(i, "subscript out of range");
    return (*data)[i];
}

// 操作类型
template <typename T>
std::ostream& operator<<(std::ostream& os, const Blob<T> a)
{
    os << "< ";
    for (size_t i = 0; i < a.size(); ++i)
        os << a[i] << " ";
    os << " >";
    return os;
}

template <typename T>
bool operator==(const Blob<T>& lhs, const Blob<T>& rhs)
{
    if (rhs.size() != lhs.size())
        return false;
    for (size_t i = 0; i < lhs.size(); ++i)
    {
        if (lhs[i] != rhs[i])
            return false;
    }
    return true;
}
/*-----------------------------------*/

template <typename T>
bool operator==(const BlobPtr<T>&, const BlobPtr<T>&);

template <typename T>
class BlobPtr 
{
    friend bool
        operator==<T>(const BlobPtr<T>&, const BlobPtr<T>&);

public:
    BlobPtr() : curr(0) {}

    BlobPtr(Blob<T>& a, size_t sz = 0) :
        wptr(a.data), curr(sz) {}

    T& operator[](std::size_t i) 
    {
        std::shared_ptr<std::vector<T> > p = check(i, "subscript out of range");
        return (*p)[i];  // (*p) 是一个 vector
    }

    const T& operator[](std::size_t i) const 
    {
        std::shared_ptr<std::vector<T> > p = check(i, "subscript out of range");
        return (*p)[i];  // (*p) 是一个 vector
    }

    T& operator*() const 
    {
        std::shared_ptr<std::vector<T> > p = check(curr, "dereference past end");
        return (*p)[curr]; 
    }

    T* operator->() const 
    { 
        // 将实际工作委托给解引用操作符 
        return &this->operator*();
    }

    // 递增以及递减
    BlobPtr& operator++();       // 前置运算符
    BlobPtr& operator--();

    BlobPtr operator++(int);     // 后置运算符
    BlobPtr operator--(int);

private:
    // check 成功的话就返回 vector 对应的 shared_ptr
    std::shared_ptr<std::vector<T> >
        check(std::size_t, const std::string&) const;

    // 存储一个 weak_ptr
    std::weak_ptr<std::vector<T> > wptr;
    std::size_t curr;      // 数组中当前的位置
};

/*------------BlobPtr 类的成员函数------------*/
// 相等运算符
template <typename T>
bool operator==(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs)
{
    return lhs.wptr.lock().get() == rhs.wptr.lock().get() && lhs.curr == rhs.curr;
}
// 不等运算符
template <typename T>
bool operator!=(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs)
{
    return !(lhs == rhs);
}

// 检查
template <typename T>
std::shared_ptr<std::vector<T> >
BlobPtr<T>::check(std::size_t i, const std::string& msg) const
{
    std::shared_ptr<std::vector<T> > ret = wptr.lock();   // 检测向量是否还存在
    if (!ret)
        throw std::runtime_error("unbound BlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret; // 否则，返回指向 vector 的指针
}

// 后置运算符
template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int)
{
    // 这里不需要 check，check 在前置运算中完成
    BlobPtr ret = *this;   // 保存当前值
    ++*this;     // 调用前置运算符
    return ret;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator--(int) {
    // 这里不需要 check，check 在前置运算中完成
    BlobPtr ret = *this;  // 保存当前值
    --*this;     // 调用前置运算符
    return ret;
}

// 前置运算符
template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
    // 如果 curr 已经指向容器的末尾，就不能再增加了
    check(curr, "increment past end of BlobPtr");
    ++curr;       // 增加 curr 的状态
    return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
    // 如果 curr 已经指向容器的开始，就不能再减少了
    --curr;
    check(-1, "decrement past begin of BlobPtr");
    return *this;
}
/*-------------------------------------------*/

#endif //BLOB_CLASS_H
