#include<iostream>
#include<vector>
using namespace std;

// 定义目前的题目序号
#define PROBLEM_6_33


#ifdef PROBLEM_6_32
	int& get(int* array, int index)
	{
		return array[index];
	}
#endif
#ifdef PROBLEM_6_33
	void print_recursion(const vector<int> & vec_list, int index)
	{
		if (index == vec_list.size())
			return;
		cout << "vec_list[" << index << "] = " << vec_list[index] << endl;
		print_recursion(vec_list, index + 1);
	}
#endif


int main()
{
#ifdef PROBLEM_6_32
	/* ---------------- 6.32 ---------------- */
	int ia[10];
	for (int i = 0; i != 10; ++i)
		get(ia, i) = i;
	for (int i = 0; i != 10; ++i)
	{
		cout << "ia[" << i << "] = " << ia[i] << endl;
	}

#endif

#ifdef PROBLEM_6_33
	/* ---------------- 6.33 ---------------- */
	// 递归打印 vector 对象的内容
	vector<int> vec_list = { 1, 4, 6, 2, 9 };
	print_recursion(vec_list, 0);

#endif

	return 0;
}
