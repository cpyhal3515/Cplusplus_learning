#include<iostream>
#include<vector>
using namespace std;

// 定义目前的题目序号
#define PROBLEM_5_20

int main()
{
	
	#ifdef PROBLEM_5_20
	string str, str_last;
	while (cin >> str)
	{
		if (!str.empty() && str != str_last)
		{
			str_last = str;
		}
		else
		{
			cout << "Pepeat Word : " << str << endl;
			break;
		}
	}

	if (!cin)
	{
		cout << "There is no repeat word" << endl;
	}


	#endif


	return 0;
}