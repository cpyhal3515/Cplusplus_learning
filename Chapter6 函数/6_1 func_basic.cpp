#include<iostream>
#include<vector>
#include "chapter6.h"
using namespace std;

// 定义目前的题目序号
#define PROBLEM_6_7



#ifdef PROBLEM_6_7
int count_calls()
{
	static int cnt = 0;
	return cnt++;
}

#endif


int main()
{
#ifdef PROBLEM_6_3_4
	/* ---------------- 6.3 6.4 ---------------- */
	int input_num = 0;
	cout << "Please input a num to calcuate its fact：" << endl;
	cin >> input_num;
	int result = fact(input_num);
	cout << "Result = " << result << endl;
	
#endif

#ifdef PROBLEM_6_7
	for (int i = 0; i < 10; i++)
	{
		cout << count_calls() << endl;
	}

#endif


	return 0;
}