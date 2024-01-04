#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<numeric>
#include "my_sales_item_class.h"
using namespace std;

// 定义目前的题目序号
#define PROBLEM_10_11


#ifdef  PROBLEM_10_11
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

#ifdef  PROBLEM_10_12
bool compareIsbn(const Sales_data& s1, const Sales_data& s2)
{
	return s1.isbn() < s2.isbn();
}
#endif

#ifdef  PROBLEM_10_13
bool moreThan5(const string& s)
{
	return s.size() >= 5;
}
#endif


#ifdef  PROBLEM_10_16_18
void elimDups(vector<string>& vec)
{
	sort(vec.begin(), vec.end());
	auto end_unique = unique(vec.begin(), vec.end());
	vec.erase(end_unique, vec.end());
	return;
}
void biggies(vector<string>& words, vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(), words.end(), [](const string& a, const string& b) {return a.size() < b.size(); });
	auto iter = partition(words.begin(), words.end(), [sz](const string& str) {return str.size() >= sz; });

	// 下面这两种写法都可以计数长度超过 sz 的单词的个数
	//auto cnt = iter - words.begin();
	auto cnt = count_if(words.begin(), words.end(), [sz](const string& str) {return str.size() >= sz; });
	cout << "Count of words more than 5 alphabet are: " << cnt << endl;

	for_each(words.begin(), iter, [](const string& str) { cout << str << endl; });
}

#endif


int main()
{

#ifdef  PROBLEM_10_11
	// 去除 vector 列表中相同的元素，对去除后的列表按照单词长度进行 stable_sort
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

	stable_sort(vec.begin(), vec.end(), isShorter);
	cout << "stable_sort result: ";
	for (auto it : vec)
	{
		cout << it << " ";
	}
	cout << endl;
#endif

#ifdef  PROBLEM_10_12
	// 编写名为 compareIsbn 的函数，比较 Sales_data() 的 isbn 成员
	vector<Sales_data> sales_data_list = { {"X234", 5, 2.1}, {"X123", 2, 3.1}, {"X524", 1, 2.8} };
	sort(sales_data_list.begin(), sales_data_list.end(), compareIsbn);
	for (auto it : sales_data_list)
	{
		print(cout, it);
		cout << endl;
	}
#endif

#ifdef  PROBLEM_10_13
	// partition，谓词为 true 在前半部分，谓词为 false 在后半部分
	vector<string> string_list = { "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	auto ture_res_pos = partition(string_list.begin(), string_list.end(), moreThan5);
	for (auto it = string_list.begin(); it != ture_res_pos; ++it)
	{
		cout << *it << " ";
	}
	cout << endl;



#endif


#ifdef  PROBLEM_10_16_18
	// 使用 lambda 函数重写 biggies，找到所有长度比 sz 大的元素，输出数量以及这些元素
	vector<string> words = { "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	biggies(words, 5);
#endif

#ifdef  PROBLEM_10_21
	// lambda 函数捕获局部 int 变量，递减变量值直到 0，为 0 则返回 true，否则返回 false
	int cnt = 0;
	auto f = [&cnt]()->bool {if (cnt == 0) { return true; } else { --cnt; return false; } };
	auto res = f();
	cout << "res == " << res << " , cnt = " << cnt << endl;
#endif

	return 0;



}