#include "my_person_item.h"
using namespace std;

int main()
{
	// 构造函数
	Person person_inform("Linus", "American");
	cout << "Name = " << person_inform.get_name() << " , Address = " << person_inform.get_address() << endl;
	while (read(cin, person_inform))
	{
		print(cout, person_inform);
	}
	
	return 0;
}