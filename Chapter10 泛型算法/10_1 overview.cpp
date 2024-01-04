#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
using namespace std;

// 定义目前的题目序号
#define PROBLEM_10_1_2

int main()
{
#ifdef  PROBLEM_10_1_2
	// count 计算给定值在序列中出现过的次数
	cout << "Int list: ";
	vector<int> int_list = {2,5,13,23,542,121,3,5,2,5,8};
	cout << count(int_list.begin(), int_list.end(), 5) << endl;

	cout << "String list: ";
	vector<string> string_list = { "hello", "world", "ni", "hao", "shi", "jie", "ni"};
	cout << count(string_list.begin(), string_list.end(), "ni") << endl;
#endif


	return 0;



}