#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<map>
using namespace std;

// 定义目前的题目序号
#define PROBLEM_11_3_4

int main()
{
#ifdef  PROBLEM_11_3_4
	// 编写单词计数程序
	// 忽略大小写和标点
	map<string, int> word_list;
	string word;
	ifstream in("./data.txt");
	while (in >> word)
	{
		word.erase(find_if(word.begin(), word.end(), ispunct), word.end());
		transform(word.begin(), word.end(), word.begin(), tolower);

		++word_list[word];
	}

	for (auto w : word_list)
	{
		cout << w.first << " : " << w.second << endl;
	}

#endif



}