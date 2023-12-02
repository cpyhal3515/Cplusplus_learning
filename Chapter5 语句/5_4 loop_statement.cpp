#include<iostream>
#include<vector>
using namespace std;

// 定义目前的题目序号
#define PROBLEM_5_19

int main()
{
	#ifdef PROBLEM_5_14
	/* ---------------- 5.14 ---------------- */
	// 查找 string 对象中重复出现的词
	// 测试案例：
	// 1 : how now now now brown cow cow
	// 2 : how now brown cow 
	int repeat_max_time = 0;
	int repeat_time_cnt = 0;
	string str;
	string str_last = "";
	while (cin >> str)
	{
		if (str == str_last)
		{
			repeat_time_cnt++;
		}
		else
		{ 
			str_last = str;
			repeat_max_time = max(repeat_max_time, repeat_time_cnt);
			repeat_time_cnt = 0;
		}

	}

	repeat_max_time = (repeat_max_time > 0) ? repeat_max_time + 1 : 0;


	cout << "repeat_max_time = " << repeat_max_time << endl;
	

	#endif // PROBLEM_5_14

	
	#ifdef PROBLEM_5_17
	/* ---------------- 5.17 ---------------- */
	// 检测一个 vector 对象是否是另一个 vector 对象的前缀
	//vector<int> vec1 = { 0, 1, 1, 2 };
	vector<int> vec1 = { 0, 1, 1, 3 };
	vector<int> vec2 = {0, 1, 1, 2, 3, 5, 8};
	decltype(vec1.begin()) iter1 = vec1.begin();
	decltype(vec2.begin()) iter2 = vec2.begin();

	for ( ;iter1 != vec1.end() && iter2 != vec2.end(); ++iter1, ++iter2)
	{
		if (*iter1 != *iter2)
		{
			cout << "Not equal" << endl;
			return 0;
		}
	}

	cout << "Is equal" << endl;
	#endif 
	
	#ifdef PROBLEM_5_19
	string str1, str2;
	do 
	{
		cout << "Please input two string: " << endl;
		cin >> str1 >> str2;
		cout << ((str1.size() < str2.size()) ? str1 : str2) << endl;
		str1 = "";
		str2 = "";
	} while (cin);



	#endif


	return 0;
}