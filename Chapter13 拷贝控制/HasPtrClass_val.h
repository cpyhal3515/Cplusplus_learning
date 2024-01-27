#ifndef HASPTR
#define HASPTR
// 行为类似值的 HasPtr 类
#include<iostream>
#include<string>
#include<vector>
#include<memory>
class HasPtr
{
	friend void swap(HasPtr&, HasPtr&);
public:
	// 构造函数
	HasPtr(const std::string &s = std::string()): ps(new std::string(s)), i(0) {}
	HasPtr(std::string& _s, int _i) : 
		ps(new std::string(_s)), i(_i) {}
	// 拷贝构造函数
	HasPtr(const HasPtr& orig) : ps(new std::string(*orig.ps)), i(orig.i) {}
	bool operator<(const HasPtr& rhs);
	// 拷贝赋值运算符
	HasPtr& operator=(const HasPtr&);

	void print()
	{
		std::cout << i << std::endl;
	}
	// 析构函数
	~HasPtr()
	{
		delete ps;
	}
private:
	std::string* ps;
	int i;
};

// 拷贝赋值运算符
HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
	std::string* new_ps = new std::string(*rhs.ps);
	delete ps;
	ps = new_ps;
	i = rhs.i;
	return *this;
}

bool HasPtr::operator<(const HasPtr& rhs)
{
	return i < rhs.i;
}

inline
void swap(HasPtr& lhs, HasPtr& rhs)
{
	using std::swap;
	// 交换指针
	swap(lhs.ps, rhs.ps);
	swap(lhs.i, rhs.i);
	std::cout << "call swap(HasPtr& lhs, HasPtr& rhs)" << std::endl;
}
#endif // HASPTR