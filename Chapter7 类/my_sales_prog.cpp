

#define CLASS_TYPE

#ifdef STRUCT_TYPE
#include "my_sales_item_struct.h"
#endif // STRUCT_TYPE
#ifdef CLASS_TYPE
#include "my_sales_item_class.h"
#endif // CLASS_TYPE
using namespace std;

int main()
{
	Sales_data total("X123");
	if (read(cin, total))
	{
		Sales_data trans("X123", 0, 0);
		while (read(cin, trans))
		{
			if (total.isbn() == trans.isbn())
				total.combine(trans);
			else
			{
				print(cout, total) << endl;
				total = trans;
			}
		}
		print(cout, total) << endl;
	}
	else
		cerr << "No data" << endl;
}