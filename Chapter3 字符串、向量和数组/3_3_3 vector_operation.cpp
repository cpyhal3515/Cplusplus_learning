#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main()
{
	/*------------------ 3.16 ------------------*/
	// 将所有输入的词先存入一个 vector，之后将 vector 中的元素改写成
	// 大写的形式
	vector<string> word_list;
	string word_tmp;
	while (cin >> word_tmp)
	{
		word_list.push_back(word_tmp);
	}
	for (auto &item : word_list)
	{
		for (auto &ch : item)
		{
			ch = toupper(ch);
		}
	}
	for (auto item : word_list)
	{
		cout << item << endl;
	}


	/*------------------ 3.20 ------------------*/
	// input 1 2 3 4 5 6 7 8 9 10
	int tmp;
	vector<int> int_list;
	while (cin >> tmp)
	{
		int_list.push_back(tmp);
	}
	 // 相邻的元素相加
	for (decltype(int_list.size()) i = 0; i < int_list.size()/2; i++)
	{
		cout << int_list[2*i] + int_list[2*i + 1] << endl;
	}
	 // 首尾元素相加
	for (decltype(int_list.size()) i = 0; i < int_list.size() / 2; i++)
	{
		cout << int_list[i] + int_list[int_list.size() - 1 - i] << endl;
	}


	return 0;
}