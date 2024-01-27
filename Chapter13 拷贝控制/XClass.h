#ifndef XCLASS
#define XCLASS

#include<iostream>
#include<string>
#include<vector>
#include<memory>
struct X
{
	// 构造函数
	X()  { std::cout << "X()" << std::endl; }
	// 拷贝构造函数
	X(const X& )  { std::cout << "X(const X&)" << std::endl; }

	// 拷贝赋值运算符
	X& operator=(const X& ) 
	{ 
		std::cout << "X& operator=(const X&)" << std::endl; 
		return *this; 
	}
	// 析构函数
	~X() 
	{ 
		std::cout << "~X()" << std::endl; 
	}
};


#endif // HASPTR