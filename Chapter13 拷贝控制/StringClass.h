#ifndef STRING
#define STRING
// 定义 String 类型
#include<iostream>
#include<memory>
class String
{
public:
	// 构造函数
	String() : String("") {}
	String(const char*);

	// 拷贝构造函数
	String(const String&);
	// 移动构造函数
	String(String&&) noexcept;
	// 拷贝赋值运算符
	String& operator=(const String&);
	// 移动赋值运算符
	String& operator=(String&& rhs) noexcept;
	// 析构函数
	~String();
	
	
	// 返回起始指针
	const char* c_str() const { return begin; }
	// 返回 string 已经容纳元素的大小
	std::size_t size() const { return end - begin; }
	// 返回 string 的长度
	std::size_t length() const { return end - begin + 1; }


private:
	// 第一个元素所在位置
	char* begin;
	// 第一个元素所在位置
	char* end;
	// 分配元素
	static std::allocator<char> alloc;
	// 分配内存并拷贝给定范围内元素
	std::pair<char*, char* > alloc_n_copy(const char*, const char*);
	// 销毁构造的元素并释放内存
	void free();
};



#endif // STRING