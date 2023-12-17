#include "my_debug_item.h"
using namespace std;

int main()
{
	// 调试 IO
	Debug io_sub(false, true, false);
	if (io_sub.any())
		cerr << "输出适当的错误信息" << endl;
	// 无调试
	Debug prod(false);
	if (prod.any())
		cerr << "输出一条错误信息" << endl;
	
	return 0;
}