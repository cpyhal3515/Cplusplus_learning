/*--------------- 使用 class 定义类 ---------------*/
#ifndef MY_SALES_ITEM_CLASS_H
#define MY_SALES_ITEM_CLASS_H

#include<iostream>
#include<string>

// 定义 Sales_data 类
class Sales_data
{
	// 友元：让类外的函数可以访问类内的私有数据
	friend Sales_data operator+(const Sales_data&, const Sales_data&);
	friend std::ostream& operator<<(std::ostream &os, const Sales_data &item);
	friend std::istream& operator>>(std::istream& is, Sales_data& item);
public:
	// 构造函数：完成类的初始化操作
	Sales_data(const std::string& s, unsigned n, double p) :
		bookNo(s), units_sold(n), revenue(p* n) 
	{
		std::cout << "Running Sales_data(const std::string& s, unsigned n, double p)" << std::endl;
	};
	// 委托构造函数：将实际的构造任务交给构造函数完成
	Sales_data() : Sales_data(" ", 0, 0) 
	{ 
		std::cout << "Running Sales_data()" << std::endl;
	};
	Sales_data(const std::string& s) : Sales_data(s, 0, 0)
	{ 
		std::cout << "Running Sales_data(const std::string& s)" << std::endl;
	};
	Sales_data(std::istream& is) :Sales_data() 
	{ 
		is >> *this;
		std::cout << "Running is >> *this" << std::endl;
	};

	// 类的公有函数操作
	std::string isbn() const { return bookNo; };
	// 定义复合赋值运算符
	Sales_data& operator+=(const Sales_data& rhs)
	{
		units_sold += rhs.units_sold;
		revenue += rhs.revenue;
		return *this;
	}
	// 定义赋值运算符
	Sales_data& operator=(const std::string& isbn)
	{
		bookNo = isbn;
		return *this;
	}
	
private:
	// 类的私有函数操作
	double avg_price() const
	{
		return (units_sold > 0) ? revenue / units_sold : 0 ;
	}
	// 类的私有数据
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;

};



#endif // MY_SALES_ITEM_CLASS_H