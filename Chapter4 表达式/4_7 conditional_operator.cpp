#include<iostream>
#include<vector>
using namespace std;

int main()
{
	/* ---------------- 4.21 ---------------- */
	// 使用条件运算符找到 num_list 中的奇数并翻倍
	vector<int> num_list = { 1,2,3,4,5,6,7,8,9,10 };
	for (int& item : num_list)
	{
		item = (item % 2) ? item * 2 : item;
	}
	for (const int item : num_list)
	{
		cout << item << endl;
	}



	return 0;
}