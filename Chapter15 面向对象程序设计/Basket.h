/*--------------- 使用 class 定义类 ---------------*/
#ifndef BASKET_CLASS_H
#define BASKET_CLASS_H

#include<iostream>
#include<string>
#include<set>
#include "Quote_class.h"

// 定义 Basket 类
class Basket
{
public:
	// Basket 使用默认合成的构造函数与拷贝控制成员

	void add_item(const Quote& sale)
	{
		item.insert(std::shared_ptr<Quote>(sale.clone()));	// 拷贝给定的对象
	}
	void add_item(const Quote&& sale)
	{
		item.insert(std::shared_ptr<Quote>(std::move(sale).clone()));	// 移动给定的对象
	}
	// 打印每本书的总价和购物篮中所有书的总价
	double total_receipt(std::ostream&) const;

private:
	// multiset 用到的比较函数
	static bool compare(const std::shared_ptr<Quote>& lhs,
		const std::shared_ptr<Quote>& rhs)
	{
		return lhs->isbn() < rhs->isbn();
	}

	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> item{ compare };
	
};


#endif // BASKET_CLASS_H