#ifndef MY_SALES_ITEM_STRUCT_H
#define MY_SALES_ITEM_STRUCT_H


#include<iostream>
#include<string>
struct Sales_data
{
	// 构造函数
	Sales_data() = default;
	Sales_data(const std::string &s) : bookNo(s) {}
	Sales_data(const std::string& s, unsigned n, double p):
		bookNo(s), units_sold(n), revenue(p*n) {}
	Sales_data(std::istream&);
	// 使用 istream 初始化
	Sales_data(std::istream& is)
	{
		read(is, *this);
	}
	// 对象操作
	std::string isbn() const {return bookNo; }
	Sales_data& combine(const Sales_data&);
	double avg_price() const;

	// 数据成员
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

// Sales_data 的非成员接口函数
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream& print(std::ostream&, const Sales_data&);
std::istream& read(std::istream&, Sales_data&);

// 定义 avg_price 函数
double Sales_data::avg_price() const
{
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}
// 定义 combine 函数
Sales_data& Sales_data::combine(const Sales_data& rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}
// 定义 add 函数
Sales_data add(const Sales_data&  data1, const Sales_data& data2)
{
	Sales_data sum = data1;
	sum.combine(data2);
	return sum;
}
// 定义 print 函数
std::ostream& print(std::ostream& os, const Sales_data& data)
{
	os << "isbn = " << data.isbn() << " , " \
		<< "units_sold = " << data.units_sold << " , " \
		<< "revenue = " << data.revenue << " , " \
		<< "avg_price = " << data.avg_price();
	return os;
}
// 定义 read 函数
std::istream& read(std::istream& is, Sales_data& data)
{
	double price = 0;
	is >> data.bookNo >> data.units_sold >> price;
	data.revenue = data.units_sold * price;
	return is;
}


#endif // MY_SALES_ITEM_H