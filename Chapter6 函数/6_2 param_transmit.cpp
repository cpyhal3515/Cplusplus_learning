#include<iostream>
#include<vector>
using namespace std;

// 定义目前的题目序号
#define PROBLEM_6_26



#ifdef PROBLEM_6_10
void swap(int * num1, int* num2)
{
	int tmp;
	tmp = *num1;
	*num1 = *num2;
	*num2 = tmp;
	return;
}

#endif

#ifdef PROBLEM_6_17
void convert_to_lower(string& str)
{
	for (char &ch : str)
	{
		ch = tolower(ch);
	}
	return;
}

int capital_letters_num(const string& str)
{
	int num = 0;
	for (char ch : str)
	{
		if (isupper(ch))
			num++;
	}
	return num;
}

#endif


#ifdef PROBLEM_6_23
void print(int i, int j[], int j_len)
{
	cout << "i = " << i << endl;
	for (int k = 0; k < j_len; ++k)
	{
		cout << "j = " << j[k] << endl;
	}
	return;
}
#endif

#ifdef PROBLEM_6_26
int calu_add(initializer_list<int> num_list)
{
	int result = 0;
	for (int num : num_list)
	{
		result += num;
	}
	return result;
}
#endif

#ifndef PROBLEM_6_25

int main()
{
#ifdef PROBLEM_6_10
	/* ---------------- 6.10 ---------------- */
	// 交换两个 int 值
	int num1 = 3, num2 = 2;
	cout << "Before swap：num1 = " << num1 << " , num2 = " << num2 << endl;
	swap(&num1, &num2);
	cout << "After swap：num1 = " << num1 << " , num2 = " << num2 << endl;
	
#endif

#ifdef PROBLEM_6_17
	/* ---------------- 6.17 ---------------- */
	// 统计大写字符个数 + 将 string 全部转换成小写
	string str = "BUIOgudeHUafehipHI";
	int num = capital_letters_num(str);
	cout << "Capital letters number：num = " << num << endl;
	cout << "Before convert to lower：str = " << str << endl;
	convert_to_lower(str);
	cout << "After convert to lower：str = " << str << endl;

#endif

#ifdef PROBLEM_6_23
	/* ---------------- 6.23 ---------------- */
	// 定义 print 函数打印 i 与 j 的值
	int i = 0;
	int j[2] = { 0, 1 };
	print(i, j, 2);
#endif

#ifdef PROBLEM_6_26
	/* ---------------- 6.26 ---------------- */
	cout << "calu_add = " << calu_add({ 1,4,-2,5 }) << endl;
#endif


	return 0;
}
#endif

#ifdef PROBLEM_6_25
// 命令行测试 .\C++_Learning.exe ofile data0
int main(int argc, char* argv[])
{
	string combine;
	for (int i = 1; i < argc; ++i)
		combine += string(argv[i]);
	cout << "combine = " << combine << endl;
	system("pause");

	return 0;
}
#endif
