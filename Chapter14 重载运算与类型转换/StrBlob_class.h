#ifndef STRBLOB
#define STRBLOB

#include<iostream>
#include<string>
#include<vector>
#include<memory>

class StrBlobPtr;
class StrBlob
{
friend class StrBlobPtr;
friend bool operator==(const StrBlob&, const StrBlob&);
friend bool operator!=(const StrBlob&, const StrBlob&);
friend bool operator<(const StrBlob&, const StrBlob&);
friend bool operator<=(const StrBlob&, const StrBlob&);
friend bool operator>(const StrBlob&, const StrBlob&);
friend bool operator>=(const StrBlob&, const StrBlob&);
public:
	typedef std::vector<std::string>::size_type size_type;

	StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}
	StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}
	// 拷贝构造函数
	StrBlob(const StrBlob& orig) : data(std::make_shared<std::vector<std::string>>(*orig.data)) {}
	// 拷贝赋值运算符
	StrBlob& operator=(const StrBlob& orig)  
	{
		data = std::make_shared<std::vector<std::string>>(*orig.data);
		return *this;
	}



	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	
	// 添加和删除元素
	void push_back(const std::string& t) 
	{ 
		data->push_back(t); 
	}
	void pop_back()
	{
		check(0, "pop_back on empty StrBlob");
		data->pop_back();
	}

	//元素访问
	std::string& front()
	{
		check(0, "front on empty StrBlob");
		return data->front();
	}
	std::string& back()
	{
		check(0, "back on empty StrBlob");
		return data->back();
	}

	// 取出首元素，在这里不能实现 begin 以及 end，因为 StrBlobPtr 还没被定义
	StrBlobPtr begin();
	// 取出末元素
	StrBlobPtr end();

	// 下标运算符
	std::string& operator[](std::size_t n)
	{
		check(n, "out of range");
		return (*data).at(n);
	}
	// 下标运算符 const 版本
	const std::string& operator[](std::size_t n) const
	{
		check(n, "out of range");
		return (*data).at(n);
	}


private:
	std::shared_ptr<std::vector<std::string>> data;
	//如果 data[i] 不合法，抛出一个异常
	void check(size_type i, const std::string& msg) const
	{
		if (i >= data->size())
			throw std::out_of_range(msg);
	}

};

/* ---------------------- 函数重载 ---------------------- */
// 相等运算符
bool operator==(const StrBlob& lhs, const StrBlob& rhs) {
	return *(lhs.data) == *(rhs.data);            // 所指向的 vector 相等
}
// 不相等运算符
bool operator!=(const StrBlob& lhs, const StrBlob& rhs) {
	return !(lhs == rhs);
}

bool operator<(const StrBlob& lhs, const StrBlob& rhs) { 
	return *(lhs.data) < *(rhs.data);
}
bool operator>(const StrBlob& lhs, const StrBlob& rhs) {
	return rhs < lhs;
}
bool operator<=(const StrBlob& lhs, const StrBlob& rhs) {
	return !(lhs > rhs);
}
bool operator>=(const StrBlob& lhs, const StrBlob& rhs) {
	return !(lhs < rhs);
}
/* ----------------------------------------------------- */


// 如果访问一个不存在的元素则 StrBlobPtr 抛出一个异常
class StrBlobPtr
{
	friend bool operator==(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator!=(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator<(const StrBlobPtr& , const StrBlobPtr& );
	friend bool operator<=(const StrBlobPtr& , const StrBlobPtr& );
	friend bool operator>(const StrBlobPtr& , const StrBlobPtr& );
	friend bool operator>=(const StrBlobPtr& , const StrBlobPtr& );
public:
	StrBlobPtr() : curr(0) {}
	StrBlobPtr(StrBlob& a, size_t sz = 0) :
		wptr(a.data), curr(sz) {}
	std::string& deref() const
	{
		auto p = check(curr, "dereference past end");
		return (*p)[curr];
	}
	// 下标运算符 const 版本
	const std::string& operator[](std::size_t n) const
	{
		auto p = check(n, "out of range");
		return (*p)[n];
	}
	// 递增与递减运算符（前置）
	StrBlobPtr& operator++();
	StrBlobPtr& operator--();
	// 递增与递减运算符（后置）
	StrBlobPtr& operator++(int);
	StrBlobPtr& operator--(int);

	// 复合运算符进行指针值的更新
	StrBlobPtr& operator+=(size_t n);
	StrBlobPtr& operator-=(size_t n);
	// +、- 运算符进行指针值的更新
	StrBlobPtr operator+(size_t n) const;
	StrBlobPtr operator-(size_t n) const;
private:
	// 若检查成功，check 返回一个指向 vector 的 shared_ptr
	std::shared_ptr<std::vector<std::string>>
		check(std::size_t i, const std::string& msg) const
	{
		// 判断 vector 是否存在
		auto ret = wptr.lock();
		if (!ret)
			throw std::runtime_error("unbound StrBlobPtr");
		if (i >= ret->size() || i < 0)
			throw std::out_of_range(msg);
		return ret;
	}
	std::weak_ptr<std::vector<std::string>> wptr;

	// 在数组中当前的位置
	std::size_t curr;

};


// begin and end members for StrBlob
inline
StrBlobPtr
StrBlob::begin()
{
	return StrBlobPtr(*this);
}

inline
StrBlobPtr
StrBlob::end()
{
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}
/* ---------------------- 函数重载 ---------------------- */
// 实现等于以及不等的函数
bool operator==(const StrBlobPtr& lhs, const StrBlobPtr& rhs)
{
	auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
	if (l == r)
		// 都是 null 或者指向相同元素说明相等
		return (!r || lhs.curr == rhs.curr);
	else
		return false; // 如果指向不同的 vector，说明不等
}

bool operator!=(const StrBlobPtr& lhs, const StrBlobPtr& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
	auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
	return lexicographical_compare(l->begin(), l->end(), r->begin(), r->end());
}
bool operator>(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
	return rhs < lhs;
}
bool operator<=(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
	return !(lhs > rhs);
}
bool operator>=(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
	return !(lhs < rhs);
}

StrBlobPtr& StrBlobPtr::operator++()
{
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}
StrBlobPtr& StrBlobPtr::operator--()
{
	// 如果 curr 是 0，则继续递减它会产生一个无效下标
	--curr;
	check(curr, "decrement past begin of StrBlobPtr");
	return *this;
}

// 后置版本：递增/递减对象的值但是返回原值
StrBlobPtr& StrBlobPtr::operator++(int) {
	// 此处无需检查有效性，调用前置递增运算时才需要检查
	StrBlobPtr ret = *this;         // 记录当前的值
	++*this;        // 向前移动一个元素，前置++需要检查递增的有效性
	return ret;     // 返回之前记录的状态
}
StrBlobPtr& StrBlobPtr::operator--(int) {
	// 此处无需检查有效性，调用前置递减运算时才需要检查
	StrBlobPtr ret = *this;         // 记录当前的值
	++*this;        // 向后移动一个元素，前置--需要检查递减的有效性
	return ret;     // 返回之前记录的状态
}

StrBlobPtr& StrBlobPtr::operator+=(size_t n)
{
	curr += n;
	check(curr, "increment past end of StrBlobPtr");
	return *this;
}
StrBlobPtr& StrBlobPtr::operator-=(size_t n)
{
	curr -= n;
	check(curr, "decrement past begin of StrBlobPtr");
	return *this;
}
StrBlobPtr StrBlobPtr::operator+(size_t n) const
{
	StrBlobPtr ret = *this;         // 记录当前的值
	ret += n;       
	return ret;     // 返回之前记录的状态
}
StrBlobPtr StrBlobPtr::operator-(size_t n) const
{
	StrBlobPtr ret = *this;         // 记录当前的值
	ret -= n;
	return ret;     // 返回之前记录的状态
}
/* ----------------------------------------------------- */
#endif // STRBLOB