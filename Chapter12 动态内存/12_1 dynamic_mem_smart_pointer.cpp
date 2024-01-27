#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<map>
#include<fstream>
#include "StrBlob_class.h"
using namespace std;

// 定义目前的题目序号
#define PROBLEM_12_20


#ifdef  PROBLEM_12_6
void vector_gen(vector<int>* vec)
{
	int num;
	while (cin >> num)
	{
		vec->push_back(num);
	}
}
void vector_printf(vector<int>* vec)
{
	for_each(vec->begin(), vec->end(), [](int num) {cout << num << endl; });
	delete vec;
}

#endif

#ifdef  PROBLEM_12_7
void vector_gen(shared_ptr<vector<int>> vec)
{
	int num;
	while (cin >> num)
	{
		vec->push_back(num);
	}
}
void vector_printf(shared_ptr<vector<int>> vec)
{
	for_each(vec->begin(), vec->end(), [](int num) {cout << num << endl; });
}

#endif

int main()
{
#ifdef  PROBLEM_12_1
	// 在代码的结尾 b1 与 b2 中的元素各有多少
	StrBlob b1;
	{
		StrBlob b2 = { "a", "an", "the" };
		b1 = b2;
		b2.push_back("about");
		cout << "b1.size() = " << b1.size() << " , b2.size() = " << b2.size() << endl;
	}
#endif

#ifdef  PROBLEM_12_6
	// 动态分配的 vector
	// vector_gen 读取输入到该 vector
	// vector_printf 将 vector 中的数据打印出来
	vector<int>* vec = new vector<int>;
	vector_gen(vec);
	vector_printf(vec);

#endif

#ifdef  PROBLEM_12_7
	// 与 12_6 类似，但是用智能指针
	shared_ptr<vector<int>> vec = make_shared<vector<int>>();
	vector_gen(vec);
	vector_printf(vec);

#endif

#ifdef  PROBLEM_12_20
	StrBlob read_data;
	ifstream in("./data.txt");
	string line;
	while (getline(in, line))
	{
		read_data.push_back(line);
	}

	for (StrBlobPtr item = read_data.begin(); neq(item, read_data.end()); item.incr())
	{
		cout << item.deref() << endl;
	}




#endif




}