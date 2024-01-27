#include "StrVecClass.h"
using namespace std;


std::allocator<std::string> StrVec::alloc;

/* ---------------------- 拷贝控制 ---------------------- */
// 构造函数：使用 initializer_list 进行构造
StrVec::StrVec(std::initializer_list<std::string> input_list)
{
	auto new_data = alloc_n_copy(input_list.begin(), input_list.end());
	elements = new_data.first;
	first_free = cap = new_data.second;
}
// 拷贝构造函数
StrVec::StrVec(const StrVec& orig)
{
	auto new_data = alloc_n_copy(orig.begin(), orig.end());
	elements = new_data.first;
	first_free = cap = new_data.second;

}
// 移动构造函数
StrVec::StrVec(StrVec&& orig) noexcept // 移动操作不应该抛出任何异常
	// 成员初始化器接管 orig 中的资源
	: elements(orig.elements), first_free(orig.first_free), cap(orig.cap)
{
	// 令 orig 进入可以析构的状态
	orig.elements = orig.first_free = orig.cap = nullptr;

}
// 拷贝赋值运算符
StrVec& StrVec::operator=(const StrVec& rhs)
{
	auto new_data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = new_data.first;
	first_free = cap = new_data.second;
	return *this;
}
// 移动赋值运算符
StrVec& StrVec::operator=(StrVec&& rhs) noexcept
{
	// 检测自赋值
	if (this != &rhs)
	{
		// 释放已有元素
		free();
		// 从 rhs 接管资源
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		// 将 rhs 置于可析构的状态
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	
	return *this;
}
// 析构函数
StrVec::~StrVec()
{
	free();
}
/* ----------------------------------------------------- */


/* ---------------------- 功能函数 ---------------------- */
void StrVec::push_back(const string& str)
{
	// 确保有空间容纳新元素
	chk_n_alloc();
	// 在 first_free 指向的元素中构造 str 的副本
	alloc.construct(first_free++, str);
}


pair<string*, string* > StrVec::alloc_n_copy(const string* b, const string* e)
{
	// 分配空间保存给定元素
	auto data = alloc.allocate(e - b);
	// 将原始数据拷贝到新分配的空间中
	return { data, uninitialized_copy(b, e, data) };
}

void StrVec::free()
{
	if (elements)
	{
		// 逆序销毁旧元素
		for (auto p = first_free; p != elements;)
		{
			alloc.destroy(--p);
		}
		alloc.deallocate(elements, cap - elements);
	}
}

void StrVec::reallocate()
{
	// 分配当前大小两倍的空间
	auto new_cap = (size() == 0) ? 1 : 2 * size();
	// 分配新内存
	auto new_data = alloc.allocate(new_cap);
	// 将数据从旧内存移向新内存
	auto dest = new_data;
	auto elem = elements;

	for (size_t i = 0; i != size(); ++i)
	{
		alloc.construct(dest++, move(*elem++));
	}

	// 释放旧内存空间
	free();
	// 更新元素
	elements = new_data;
	first_free = dest;
	cap = elements + new_cap;
}
/* ----------------------------------------------------- */