#include "Basket.h"
using namespace std;



/*------------Basket 类成员------------*/
double Basket::total_receipt(ostream& os) const
{
	double sum = 0.0;	// 保存实时计算出的总价格
	// iter 指向 ISBN 相同的一批元素中的第一个
	// upper_bound 返回一个尾后迭代器
	for (auto iter = item.cbegin(); iter != item.cend(); iter = item.upper_bound(*iter))
	{
		sum += print_total(os, **iter, item.count(*iter));
	}
	os << "Total Sale: " << sum << endl;	// 打印最终的价格
	return sum;
}
/*-----------------------------------------*/