#include<iostream>
#include<vector>
#include<list>
#include<string>
using namespace std;

// 定义目前的题目序号
#define PROBLEM_9_16 

#ifdef  PROBLEM_9_4
vector<int>::iterator find_iter(vector<int>::iterator begin_it, vector<int>::iterator end_it, int item)
{
	vector<int>::iterator find_it = begin_it;

	while (find_it != end_it)
	{
		if (*find_it == item)
		{
			cout << "Find it" << endl;
			return find_it;
		}
		++find_it;
	}

	cout << "Not find it" << endl;
	return find_it;
}
#endif

int main()
{
#ifdef  PROBLEM_9_4
	vector<int> test = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int>::iterator find_result = find_iter(test.begin() + 2, test.begin() + 5, 1);
#endif

#ifdef PROBLEM_9_13
	list<int> list_tmp = { 1,2,3,4,5,6,7,8,9,10 };
	vector<double> list_copy(list_tmp.begin(), list_tmp.end());
	cout << "list_copy = " << endl;
	for (auto it = list_copy.begin(); it != list_copy.end(); ++it)
	{
		cout << *it << " ";
	}
#endif // PROBLEM_9_13

#ifdef PROBLEM_9_14
	//list<char*> list_tmp = { 'N', 'i', 'H', 'a', 'o', 'H', 'e', 'l', 'l', 'o', 'W', 'o', 'r', 'l', 'd' };
	list<char*> list_tmp = { (char *)"Ni", (char *)"Hao", (char *)"Hello", (char *)"World"};
	vector<string> list_copy;
	list_copy.assign(list_tmp.cbegin(), list_tmp.cend());
	cout << "list_copy = " << endl;
	for (auto it = list_copy.begin(); it != list_copy.end(); ++it)
	{
		cout << *it << " ";
	}
#endif // PROBLEM_9_14

#ifdef PROBLEM_9_15 
	// 编写程序，判定两个 vector<int> 是否相等
	vector<int> vec1 = { 1,1,3,4,5,6,7,8,9,10 };
	vector<int> vec2 = { 1,2,3,4,5,6,7,8,9,10 };
	
	if (vec1 == vec2)
	{
		cout << "vec1 == vec2" << endl;
	}
	else if (vec1 > vec2)
	{
		cout << "vec1 > vec2" << endl;
	}
	else if (vec1 < vec2)
	{
		cout << "vec1 < vec2" << endl;
	}
#endif // PROBLEM_9_15

#ifdef PROBLEM_9_16 
	// 编写程序，比较一个 list<int> 中的元素
	// 和一个 vector<int> 中的元素
	list<int> list1 = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int> vec1(list1.begin(), list1.end());
	vector<int> vec2 = { 1,2,3,4,5,6,7,8,9,10 };

	if (vec1 == vec2)
	{
		cout << "vec1 == vec2" << endl;
	}
	else if (vec1 > vec2)
	{
		cout << "vec1 > vec2" << endl;
	}
	else if (vec1 < vec2)
	{
		cout << "vec1 < vec2" << endl;
	}
#endif // PROBLEM_9_16

	return 0;



}