/*--------------- 使用 class 定义类 ---------------*/
#ifndef QUOTE_CLASS_H
#define QUOTE_CLASS_H

#include<iostream>
#include<string>

// 定义 Quote 类
class Quote
{
public:
	Quote()
	{
		std::cout << "Quote Default Constructor" << std::endl;
	}
	Quote(const std::string& book, double sales_price) :
		bookNo(book), price(sales_price)
	{
		std::cout << "Quote Constructor taking two parameters" << std::endl;
	}
	std::string isbn() const { return bookNo; }

	// 返回给定数量的书籍的销售总额
	// 派生类负责改写并使用不同的折扣计算算法
	virtual double net_price(std::size_t n) const
	{
		return n * price;
	}
	// 对析构函数进行动态绑定
	virtual ~Quote()
	{
		std::cout << "Quote Destructor" << std::endl;
	}

	// 拷贝构造函数
	Quote(const Quote& rhs) : bookNo(rhs.bookNo), price(rhs.price) 
	{
		std::cout << "Quote Copy Constructor" << std::endl;
	}
	// 拷贝赋值运算符
	Quote& operator=(const Quote& rhs) 
	{
		std::cout << "Quote Copy assignment operator" << std::endl;

		price = rhs.price;
		bookNo = rhs.bookNo;
		return *this;
	}
	// 移动构造函数
	Quote(Quote&& rhs) noexcept : bookNo(std::move(rhs.bookNo)), price(std::move(rhs.price)) 
	{
		std::cout << "Quote Move Constructor" << std::endl;
	}
	// 移动赋值运算符
	Quote& operator=(Quote&& rhs) noexcept 
	{
		std::cout << "Quote Move assignment operator" << std::endl;
		bookNo = std::move(rhs.bookNo);
		price = std::move(rhs.price);
		return *this;
	}

	// 该函数返回当前对象的一份动态分配的拷贝
	virtual Quote* clone() const&
	{
		return new Quote(*this);
	}
	virtual Quote* clone() &&
	{
		return new Quote(std::move(*this));
	}

	
private:
	std::string bookNo; // 书籍的 ISBN 编号
protected:
	double price = 0.0; // 表示普通状态下不打折的价格
};

// 定义 Disc_quote 类. Disc_quote 类继承自 Quote
// 用于保存折扣值和购买量的类，派生类适用这些数据可以实现不同的价格策略
class Disc_quote : public Quote
{
public:
	Disc_quote() = default;
	Disc_quote(const std::string& book, double price, std::size_t qty, double disc) :
		Quote(book, price), quantity(qty), discount(disc) {}
	double net_price(std::size_t) const = 0;
protected:
	std::size_t quantity = 0;	// 折扣适用的购买量
	double discount = 0.0;		// 表示折扣的小数值
};


// 定义 Bulk_quote 类. Bulk_quote 类继承自 Disc_quote
class Bulk_quote : public Disc_quote
{
public:
	using Disc_quote::Disc_quote;
	// 覆盖基类的函数版本以实现基于大量购买的折扣政策
	double net_price(std::size_t) const override;

	// 该函数返回当前对象的一份动态分配的拷贝
	Bulk_quote* clone() const&
	{
		return new Bulk_quote(*this);
	}
	Bulk_quote* clone()&&
	{
		return new Bulk_quote(std::move(*this));
	}
};


double print_total(std::ostream& os, const Quote& item, std::size_t n);
#endif // QUOTE_CLASS_H