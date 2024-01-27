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


private:
	std::shared_ptr<std::vector<std::string>> data;
	//如果 data[i] 不合法，抛出一个异常
	void check(size_type i, const std::string& msg) const
	{
		if (i >= data->size())
			throw std::out_of_range(msg);
	}

};


// 如果访问一个不存在的元素则 StrBlobPtr 抛出一个异常
class StrBlobPtr
{
	friend bool eq(const StrBlobPtr&, const StrBlobPtr&);
public:
	StrBlobPtr() : curr(0) {}
	StrBlobPtr(StrBlob& a, size_t sz = 0) :
		wptr(a.data), curr(sz) {}
	std::string& deref() const
	{
		auto p = check(curr, "dereference past end");
		return (*p)[curr];
	}
	StrBlobPtr& incr()
	{
		// 如果 curr 已经在容器的尾后就不能递增
		check(curr, "increment past end of StrBlobPtr");
		++curr;
		return *this;
	}



private:
	// 若检查成功，check 返回一个指向 vector 的 shared_ptr
	std::shared_ptr<std::vector<std::string>>
		check(std::size_t i, const std::string& msg) const
	{
		// 判断 vector 是否存在
		auto ret = wptr.lock();
		if (!ret)
			throw std::runtime_error("unbound StrBlobPtr");
		if (i >= ret->size())
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

// 实现等于以及不等的函数
inline
bool eq(const StrBlobPtr& lhs, const StrBlobPtr& rhs)
{
	auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
	if (l == r)
		// 都是 null 或者指向相同元素说明相等
		return (!r || lhs.curr == rhs.curr);
	else
		return false; // 如果指向不同的 vector，说明不等
}

inline
bool neq(const StrBlobPtr& lhs, const StrBlobPtr& rhs)
{
	return !eq(lhs, rhs);
}

#endif // STRBLOB