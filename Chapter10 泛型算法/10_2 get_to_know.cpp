#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<numeric>
#include "my_sales_item_class.h"
using namespace std;

// 定义目前的题目序号
#define PROBLEM_10_9


#ifdef  PROBLEM_10_9
bool isShorter(const string& s1, const string& s2)
{
	return s1.size() < s2.size();
}
void elimDups(vector<string>& vec)
{
	sort(vec.begin(), vec.end());
	auto end_unique = unique(vec.begin(), vec.end());
	vec.erase(end_unique, vec.end());
	return;
}
#endif




int main()
{
#ifdef  PROBLEM_10_3
	// accumulate 计算 vector<int> 的和
	cout << "Int accumulate result: ";
	vector<int> int_list = {2,5,13,23,542,121,3,5,2,5,9};
	cout << accumulate(int_list.begin(), int_list.end(), 0) << endl;
#endif

#ifdef  PROBLEM_10_6
	// 使用 fill_n 将序列中的 int 值置 0
	vector<int> int_list = { 2,5,13,23,542,121,3,5,2,5,9 };
	fill_n(int_list.begin(), int_list.size(), 0);
	for (int it : int_list)
	{
		cout << it << " ";
	}
	cout << endl;

#endif
#ifdef  PROBLEM_10_9
	// 去除 vector 列表中相同的元素
	vector<string> vec = { "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	cout << "initial result: ";
	for (auto it : vec)
	{
		cout << it << " ";
	}
	cout << endl;

	elimDups(vec);
	cout << "erase result: ";
	for (auto it : vec)
	{
		cout << it << " ";
	}
	cout << endl;
#endif

	return 0;



}