/*--------------- 使用 class 定义类 ---------------*/
#ifndef MY_SALES_ITEM_CLASS_H
#define MY_SALES_ITEM_CLASS_H

#include<iostream>
#include<string>

// 定义 Sales_data 类
class Sales_data
{
	// 友元：让类外的函数可以访问类内的私有数据
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend std::ostream& print(std::ostream&, const Sales_data&);
	friend std::istream& read(std::istream&, Sales_data&);
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
	Sales_data(const std::string& s) : Sales_data(s, 0, 0) \
	{ 
		std::cout << "Running Sales_data(const std::string& s)" << std::endl;
	};
	Sales_data(std::istream& is) :Sales_data() 
	{ 
		read(is, *this); 
		std::cout << "Running Sales_data(std::istream& is)" << std::endl;
	};

	// 类的公有函数操作
	std::string isbn() const { return bookNo; };
	Sales_data& combine(const Sales_data&);
	
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

// 定义类中的 combine 操作
Sales_data& Sales_data::combine(const Sales_data& data)
{
	units_sold += data.units_sold;
	revenue += data.revenue;
	return *this;
}

// 定义类中的 add、print、read 操作
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream& print(std::ostream&, const Sales_data&);
std::istream& read(std::istream&, Sales_data&);

Sales_data add(const Sales_data& data1, const Sales_data& data2)
{
	Sales_data item = data1;
	item.combine(data2);
	return item;
}

std::ostream& print(std::ostream& os, const Sales_data& data)
{
	os << "isbn = " << data.isbn() << " , " \
		<< "units_sold = " << data.units_sold << " , " \
		<< "revenue = " << data.revenue << " , " \
		<< "avg_price = " << data.avg_price();
	return os;
}

std::istream& read(std::istream& is, Sales_data& data)
{
	double price;
	is >> data.bookNo >> data.units_sold >> price;
	data.revenue = data.units_sold * price;
	return is;
}


#endif // MY_SALES_ITEM_CLASS_H