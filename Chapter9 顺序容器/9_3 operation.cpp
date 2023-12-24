#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<deque>
#include<forward_list>
using namespace std;

// 定义目前的题目序号
#define PROBLEM_9_32

#ifdef PROBLEM_9_28
void insert_str(forward_list<string>& fl_str, string find_str, string ins_str)
{
	auto pre = fl_str.before_begin();
	auto cur = fl_str.begin();
	while (cur != fl_str.end())
	{
		if (*cur == find_str)
		{
			fl_str.insert_after(pre, ins_str);
			return;
		}
		pre = cur;
		++cur;
	}
	fl_str.insert_after(pre, ins_str);
	return;
}

#endif
 



int main()
{
#ifdef PROBLEM_9_18
	// 从标准输入读取 string 序列，存入一个 deque 中
	// 编写一个循环，用迭代器打印 deque 中的元素
	deque<string> deque_list;
	string str_tmp;
	while (cin >> str_tmp)
	{
		deque_list.push_back(str_tmp);
	}
	cout << "str_tmp = ";
	for (auto it = deque_list.cbegin(); it != deque_list.cend(); ++it)
	{
		cout << *it << " ";
	}

#endif // PROBLEM_9_18

#ifdef PROBLEM_9_19
	// 从标准输入读取 string 序列，存入一个 deque 中
	// 编写一个循环，用迭代器打印 deque 中的元素

	list<int> list_tmp = { 1,2,3,4,5,6,7,8,9,10 }; 
	deque<int> list_tmp_odd;
	deque<int> list_tmp_even;
	
	
	for (auto it = list_tmp.cbegin(); it != list_tmp.cend(); ++it)
	{
		if (*it % 2)
		{
			list_tmp_odd.push_back(*it);
		}
		else
		{
			list_tmp_even.push_back(*it);
		}
	}
	 
	cout << "list_tmp_odd = ";
	for (auto it = list_tmp_odd.cbegin(); it != list_tmp_odd.cend(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << "list_tmp_even = ";
	for (auto it = list_tmp_even.cbegin(); it != list_tmp_even.cend(); ++it)
	{
		cout << *it << " ";
	}

#endif // PROBLEM_9_19


#ifdef PROBLEM_9_24
	// 通过以下 4 种方式访问一个空的 vector
	vector<int> empty_vec;
	try 
	{
		//cout << empty_vec.at(0) << endl;
		//cout << empty_vec[0] << endl;
		cout << empty_vec.front() << endl;
		//cout << *empty_vec.begin() << endl;
	}
	catch (out_of_range)
	{
		cout << "out of range" << endl;
	}

#endif // PROBLEM_9_24

#ifdef PROBLEM_9_25
	// 将 ia 拷贝到一个 vector 或者 list 中
	// 从 list 中删除奇数元素，从 vector 中删除偶数元素
	int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
	vector<int> ia_vec(begin(ia), end(ia));
	list<int> ia_list(begin(ia), end(ia));

	auto it1 = ia_vec.begin();
	while (it1 != ia_vec.end())
	{
		if (*it1 % 2 == 0)
		{
			it1 = ia_vec.erase(it1);
		}
		else
		{
			++it1;
		}
	}

	for (auto it1 = ia_vec.begin(); it1 != ia_vec.end(); ++it1)
	{
		cout << *it1 << " ";
	}
	cout << endl;

	auto it2 = ia_list.begin();
	while (it2 != ia_list.end())
	{
		if (*it2 % 2)
		{
			it2 = ia_list.erase(it2);
		}
		else
		{
			++it2;
		}
	}
	for (auto it2 = ia_list.begin(); it2 != ia_list.end(); ++it2)
	{
		cout << *it2 << " ";
	}
	cout << endl;
#endif

#ifdef PROBLEM_9_27
	// 查找并删除 forward_list<int> 中的奇数元素
	forward_list<int> fl_int = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
	auto prev = fl_int.before_begin();
	auto curr = fl_int.begin();
	while (curr != fl_int.end())
	{
		if (*curr % 2)
		{
			curr = fl_int.erase_after(prev);
		}
		else
		{
			prev = curr;
			++curr;
		}
	}

	for (auto it = fl_int.begin(); it != fl_int.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;


#endif


#ifdef PROBLEM_9_28
	forward_list<string> fl_str = { "Hello", "world", "this", "is", "a", "new", "day" };
	string find_str = "days";
	string ins_str = "aha";
	insert_str(fl_str, find_str, ins_str);

	for (auto it = fl_str.begin(); it != fl_str.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;


#endif


#ifdef PROBLEM_9_31
	//vector<int> vi = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };s
	list<int> vi = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto iter = vi.begin();
	while (iter != vi.end())
	{
		if (*iter % 2)
		{
			iter = vi.insert(iter, *iter);
			++iter;
			++iter;
		}
		else
		{
			iter = vi.erase(iter);
		}
	}

	for (auto it = vi.begin(); it != vi.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
#endif

	return 0;



}