#ifndef HASPTR
#define HASPTR
// 行为类似指针的 HasPtr 类
#include<iostream>
#include<string>
#include<vector>
#include<memory>
class HasPtr
{
public:
	// 构造函数
	HasPtr(const std::string &s = std::string()): 
		ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
	// 拷贝构造函数
	HasPtr(const HasPtr& orig) : 
		ps(new std::string(*orig.ps)), i(orig.i), use(orig.use) 
	{
		// 增加引用计数
		++*use;
	}
	// 拷贝赋值运算符
	HasPtr& operator=(const HasPtr&);
	// 析构函数
	~HasPtr() {}
private:
	std::string* ps;
	int i;
	// use 用来表示引用计数的值
	std::size_t* use;
};

// 拷贝赋值运算符
HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
	// 递增右侧对象的引用计数值
	++*rhs.use;
	// 递减本对象的引用计数值，若没有其余用户引用本对象，则释放本对象
	if (--*use == 0)
	{
		delete ps;
		delete use;
	}
	// 将数据从 rhs 拷贝到本对象
	ps = rhs.ps;
	i = rhs.i;
	use = rhs.use;
	return *this;
}

// 拷贝赋值运算符
HasPtr::~HasPtr()
{
	// 如果引用计数变为 0 
	if (--*use == 0)
	{
		// 释放 string 内存
		delete ps;
		// 释放计数器内存
		delete use;
	}
}

#endif // HASPTR