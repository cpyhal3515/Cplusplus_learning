#ifndef VEC_H
#define VEC_H

#include <memory>

template <typename T>
class Vec 
{
public:
    Vec() : elements(0), first_free(0), cap(0) { }
    Vec(const Vec&);                    // 拷贝构造函数
    Vec& operator=(const Vec&);         // 拷贝赋值
    ~Vec();                             // 析构函数

    // 增添元素
    void push_back(const T&);

    // 大小和容量
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }

    // 获取元素
    T& operator[](size_t n) { return elements[n]; }
    const T& operator[](size_t n) const { return elements[n]; }

    // 迭代器接口
    T* begin() const { return elements; }
    T* end() const { return first_free; }

private:
    static std::allocator<T> alloc;     // 分配元素
    // 向 Vec 中添加元素的函数使用 
    void chk_n_alloc() { if (first_free == cap) reallocate(); }

  
    std::pair<T*, T*> alloc_n_copy(const T*, const T*);
    void free();
    void reallocate();  // 获取更多存储空间，并且将元素拷贝过去
    T* elements;        // 指向数组中第一个元素的指针
    T* first_free;      // 指向数组中第一个空闲元素的指针（最后一个元素的下一个）
    T* cap;             // 指向数组容量大小的指针
};

// 静态数据成员的定义
template <typename T> std::allocator<T> Vec<T>::alloc;

template <typename T>
inline
Vec<T>::~Vec() { free(); }

template <typename T>
inline
std::pair<T*, T*> Vec<T>::alloc_n_copy(const T* b, const T* e) 
{
    T* data = alloc.allocate(e - b);
    return std::make_pair(data, std::uninitialized_copy(b, e, data));
}

template <typename T>
inline
Vec<T>::Vec(const Vec& s) 
{
    // 调用 copy 来分配与 s 中相同数量的元素 
    std::pair<T*, T*> newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

template <typename T>
inline
void Vec<T>::free() 
{
    // 以相反的顺序销毁旧的元素
    for (T* p = first_free; p != elements; /* empty */)
        alloc.destroy(--p);     

    // 不能在空指针上调用 Deallocate
    if (elements)
        alloc.deallocate(elements, cap - elements);
}

template <typename T>
inline
Vec<T>& Vec<T>::operator=(const Vec& rhs) 
{
    // 调用 copy 来分配与 RHS 中相同数量的元素 
    std::pair<T*, T*> data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

template <typename T>
inline
void Vec<T>::reallocate() 
{
    // 为两倍于当前大小的元素分配空间 
    size_t newcapacity = size() ? 2 * size() : 2;

    // 分配新空间
    T* first = alloc.allocate(newcapacity);
    T* dest = first;
    T* elem = elements;

    // 复制元素
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, *elem++);
    free();     // 完成元素移动后释放旧空间 

    // 更新我们的数据结构并指向新的元素 
    elements = first;
    first_free = dest;
    cap = elements + newcapacity;
}

template <typename T>
inline
void Vec<T>::push_back(const T& s) 
{
    chk_n_alloc();      // 必要时重新分配空间
    // 将 s 存入 first_free 当前指向的元素，之后递增 first_free
    alloc.construct(first_free++, s);
}

#endif //VEC_H
