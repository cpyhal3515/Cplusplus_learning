#include "StringClass.h"
using namespace std;


std::allocator<char> String::alloc;

/* ---------------------- 拷贝控制 ---------------------- */
// 构造函数：
String::String(const char* s)
{
	char* s_ch = const_cast<char*>(s);
	while (*s_ch)
	{
		++s_ch;
	}

	auto new_data = alloc_n_copy(s, ++s_ch);
	begin = new_data.first;
	end = new_data.second;
}

// 拷贝构造函数
String::String(const String& orig)
{
	auto new_data = alloc_n_copy(orig.begin, orig.end);
	begin = new_data.first;
	end = new_data.second;
	cout << "拷贝构造" << endl;
}
// 移动构造函数
String::String(String&& orig) noexcept // 移动操作不应该抛出任何异常
// 成员初始化器接管 orig 中的资源
	: begin(orig.begin), end(orig.end)
{
	// 令 orig 进入可以析构的状态
	orig.begin = orig.end = nullptr;
	cout << "移动构造" << endl;
}

// 拷贝赋值运算符
String& String::operator=(const String& rhs)
{
	auto new_data = alloc_n_copy(rhs.begin, rhs.end);
	free();
	begin = new_data.first;
	end = new_data.second;
	cout << "拷贝赋值" << endl;
	return *this;
}
// 移动赋值运算符
String& String::operator=(String&& rhs) noexcept
{
	// 检测自赋值
	if (this != &rhs)
	{
		// 释放已有元素
		free();
		// 从 rhs 接管资源
		begin = rhs.begin;
		end = rhs.end;
		// 将 rhs 置于可析构的状态
		rhs.begin = rhs.end = nullptr;
	}
	cout << "移动赋值" << endl;
	return *this;
}

// 析构函数
String::~String()
{
	free();
}
/* ----------------------------------------------------- */


/* ---------------------- 功能函数 ---------------------- */

pair<char*, char* > String::alloc_n_copy(const char* b, const char* e)
{
	// 分配空间保存给定元素
	auto data = alloc.allocate(e - b);
	// 将原始数据拷贝到新分配的空间中
	return { data, uninitialized_copy(b, e, data) };
}

void String::free()
{
	if (begin)
	{
		// 逆序销毁旧元素
		for (auto p = end; p != begin;)
		{
			alloc.destroy(--p);
		}
		alloc.deallocate(begin, end - begin);
	}
}

/* ----------------------------------------------------- */


/* ---------------------- 函数重载 ---------------------- */
bool operator==(const String& lhs, const String& rhs)
{
	return (lhs.size() == rhs.size() && equal(lhs.begin, lhs.end, rhs.begin));
}
bool operator!=(const String& lhs, const String& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const String& lhs, const String& rhs) {
	// 标准库函数 lexicographical_compare
	// 检查第一个范围[first1, last1) 是否按字典序小于第二个范围[first2, last2) 
	return lexicographical_compare(lhs.begin, lhs.end, rhs.begin, rhs.end);
}
bool operator>(const String& lhs, const String& rhs) {
	return rhs < lhs;
}
bool operator<=(const String& lhs, const String& rhs) {
	return !(lhs > rhs);
}
bool operator>=(const String& lhs, const String& rhs) {
	return !(lhs < rhs);
}

/* ----------------------------------------------------- */