#include<iostream>
#include<string>

using namespace std;

int main()
{
	/*------------------ 3.2 ------------------*/
	/*------- 1、一次读入一个词 -------*/
	//string word;
	//while (cin >> word)
	//{
	//	cout << word << endl;
	//}

	/*-------- 2、一次读入一行 --------*/
	//string line;
	//while (getline(cin, line))
	//{
	//	if (!line.empty())
	//	{
	//		cout << line << endl;
	//	}
	//}

	/*------------------ 3.4 ------------------*/
	/*-------- 1、比较字符串是否相等 --------*/
	//string str1, str2;
	//cin >> str1;
	//cin >> str2;
	//if (str1 > str2)
	//	cout << str1 << endl;
	//else if (str1 < str2)
	//	cout << str2 << endl;
	//else
	//	cout << str1 << endl;
	
	/*-------- 2、比较字符串是否等长 --------*/
	//string str1, str2;
	//cin >> str1;
	//cin >> str2;
	//if (str1.size() == str2.size())
	//	cout << "输入字符串等长！" << endl;
	//else if (str1.size() > str2.size())
	//	cout << str1 << endl;
	//else
	//	cout << str2 << endl;

	/*------------------ 3.5 ------------------*/
	/*-------- 1、从标准输入中读取多个字符串 --------*/
	//string word;
	//string result;
	//while (cin >> word)
	//{
	//	result += word;
	//}
	//cout << "最终的拼接字符串为：result = " << result << endl;

	/*-------- 2、用空格分割多个字符串 --------*/
	string word;
	string result;
	while (cin >> word)
	{
		result += word +' ';
	}
	cout << "最终的拼接字符串为：result = " << result << endl;


	return 0;
}