#ifndef STRVEC
#define STRVEC
// 定义模板为 string 的 vector 类型 
#include<iostream>
#include<string>
#include<vector>
#include<memory>
class StrVec
{
public:
	// 构造函数
	StrVec() : 
		elements(nullptr), first_free(nullptr), cap(nullptr) {}
	// 使用 initializer_list 进行构造
	StrVec(std::initializer_list<std::string>);

	// 拷贝构造函数
	StrVec(const StrVec&);
	// 移动构造函数
	StrVec(StrVec&&) noexcept;
	// 拷贝赋值运算符
	StrVec& operator=(const StrVec&);
	// 移动赋值运算符
	StrVec& operator=(StrVec&& rhs) noexcept;

	// 析构函数
	~StrVec();

	// 将元素加入 vector
	void push_back(const std::string&);
	// 返回 vector 已经容纳元素的大小
	std::size_t size() const { return first_free - elements; }
	// 返回 vector 的容量
	std::size_t capacity() const { return cap - elements; }
	// 返回起始元素的位置
	std::string* begin() const { return elements; }
	// 返回终止元素的位置
	std::string* end() const { return first_free; }
	

private:
	// 第一个元素所在位置
	std::string* elements;
	// 第一个非元素所在位置
	std::string* first_free;
	// 指示整个 vector 的最后容纳元素的位置
	std::string* cap;
	// 分配元素
	static std::allocator<std::string> alloc;
	// 保证有容纳新元素的空间
	void chk_n_alloc()
	{
		if (size() == capacity())
		{
			reallocate();
		}
	}
	// 分配内存并拷贝给定范围内元素
	std::pair<std::string* , std::string* > alloc_n_copy(const std::string* , const std::string* );
	// 销毁构造的元素并释放内存
	void free();
	// 在内存用完时为 StrVec 分配新内存
	void reallocate();
};



#endif // STRVEC