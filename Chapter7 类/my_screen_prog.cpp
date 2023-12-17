#include "my_screen_item.h"
using namespace std;

int main()
{
	// 构造函数
	Screen myScreen(5, 5, 'X');
	myScreen.move(2, 3).set('#').display(cout);
	cout << "\n";
	myScreen.display(cout);
	cout << "\n";

	return 0;
}