#include "Quote_class.h"
using namespace std;


double print_total(ostream& os, const Quote& item, size_t n)
{

	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
	return ret;
}

/*------------Bulk_quote Àà³ÉÔ±------------*/
double Bulk_quote::net_price(size_t cnt) const
{
	if (cnt >= quantity)
	{
		return cnt * discount * price;
	}
	else
	{
		return cnt * price;
	}
}
/*-----------------------------------------*/