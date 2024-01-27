#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<map>
#include<fstream>
#include "TextQuery_class.h"
using namespace std;

void run_queries(ifstream& infile)
{
	// infile 是我们要处理的文件
	TextQuery tq(infile); // 保存文件并建立查询 map

	while (true)
	{
		cout << "Enter word to look for, or q to quit: ";
		string s;
		// 若遇到文件尾或用户输入了 'q' 时循环终止
		if (!(cin >> s) || s == "q") break;
		QueryResult qres = tq.query(s);
		// 指向查询并打印结果
		print(cout, qres) << endl;
	}

}

int main()
{
	ifstream file_in("./storyDataFile");
	run_queries(file_in);

}