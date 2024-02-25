#include "my_sales_item_class.h"
using namespace std;


Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum += rhs;
	return sum;
}

ostream& operator<<(std::ostream& os, const Sales_data& item)
{
	os << "isbn = " << item.isbn() << " , " \
		<< "units_sold = " << item.units_sold << " , " \
		<< "revenue = " << item.revenue << " , " \
		<< "avg_price = " << item.avg_price();
	return os;
}

istream& operator>>(std::istream& is, Sales_data& item)
{
	double price;
	is >> item.bookNo >> item.units_sold >> price;
	if (is)
	{
		// 检查输入是否成功
		item.revenue = item.units_sold * price;
	}
	else
	{
		// 输入失败：对象被赋予默认的状态
		item = Sales_data();
	}
	return is;
}