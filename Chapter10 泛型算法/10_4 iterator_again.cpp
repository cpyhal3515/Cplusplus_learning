#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<numeric>
#include<fstream>
using namespace std;

// 定义目前的题目序号
#define PROBLEM_10_36



#ifdef  PROBLEM_10_33
void write2file(string& file_in_name, string& file_out1_name, string& file_out2_name)
{
	ifstream in(file_in_name);
	istream_iterator<int> str_it(in);
	istream_iterator<int> eof;
	vector<int> vec(str_it, eof);

	ofstream out1(file_out1_name);
	ofstream out2(file_out2_name);
	ostream_iterator<int> str_ot1(out1);
	ostream_iterator<int> str_ot2(out2);

	for (auto it : vec)
	{
		if (it % 2 == 1)
		{
			*str_ot1++ = it;
			out1 << " ";
		}
		else if (it % 2 == 0)
		{
			*str_ot2++ = it;
			out2 << endl;
		}
	}




	

}

#endif

int main()
{

#ifdef  PROBLEM_10_27
	// 拷贝 vector 中的不重复元素到一个初始化为空的 list 中
	vector<int> vec = { 1,1,3,5,3,6,2,4,6,2 };
	list<int> vec_copy;
	sort(vec.begin(), vec.end());
	unique_copy(vec.begin(), vec.end(), back_inserter(vec_copy) );
	// 将结果打印出来
	for_each(vec_copy.begin(), vec_copy.end(), [](const int& i) { cout << i << endl; });
	
#endif

#ifdef  PROBLEM_10_28
	// 使用三种方式将 1-9 拷贝到其它容器中
	vector<int> vec = {1,2,3,4,5,6,7,8,9};
	list<int> vec_copy;
	list<int> vec_copy_back;
	list<int> vec_copy_front;

	copy(vec.begin(), vec.end(), inserter(vec_copy, vec_copy.begin()));
	copy(vec.begin(), vec.end(), front_inserter(vec_copy_front));
	copy(vec.begin(), vec.end(), back_inserter(vec_copy_back));
	// 将结果打印出来
	cout << "inserter result = ";
	for_each(vec_copy.begin(), vec_copy.end(), [](const int& i) { cout << i << " "; });
	cout << endl;
	cout << "front_inserter result = ";
	for_each(vec_copy_front.begin(), vec_copy_front.end(), [](const int& i) { cout << i << " "; });
	cout << endl;
	cout << "back_inserter result = ";
	for_each(vec_copy_back.begin(), vec_copy_back.end(), [](const int& i) { cout << i << " "; });
	cout << endl;

#endif

#ifdef  PROBLEM_10_29
	// 使用流迭代器读取文本文件
	ifstream in("./data.txt");
	istream_iterator<string> str_it(in);
	istream_iterator<string> eof;

	vector<string> vec(str_it, eof);

	for_each(vec.begin(), vec.end(), [](const string& str) {cout << str << " "; });
	cout << endl;

#endif

#ifdef  PROBLEM_10_30_31
	// 使用流迭代器
	// 1 1 3 5 3 6 2 4 6 2
	istream_iterator<int> int_it(cin);
	istream_iterator<int> eof;

	ostream_iterator<int> ont_it(cout);

	vector<int> vec;

	// 输入
	copy(int_it, eof, back_inserter(vec));
	// 排序
	sort(vec.begin(), vec.end());
	// 打印不重复元素
	unique_copy(vec.begin(), vec.end(), ont_it);

	// 刷新输出流
	cout << endl;


#endif
#ifdef  PROBLEM_10_33
	// istream_iterator 读取输入文件
	// ostream_iterator 奇数写入第一个输出文件，偶数写入第二个输出文件
	string data_in = "./data_int.txt";
	string data_out1 = "./data_out1.txt";
	string data_out2 = "./data_out2.txt";
	write2file(data_in, data_out1, data_out2);
#endif

#ifdef  PROBLEM_10_34_35
	// 逆序打印 vector
	vector<int> vec = { 1,2,3,4,5,6,7,8,9 };
	ostream_iterator<int> ont_it(cout);
	// 逆序迭代器
	copy(vec.rbegin(), vec.rend(), ont_it);
	cout << endl;
	// 普通迭代器
	for (auto it = vec.end(); it != vec.begin();)
	{
		--it;
		cout << *it;
	}

#endif

#ifdef  PROBLEM_10_36
	// find 查找 list 中最后一个为 0 的元素
	list<int> vec = { 1,2,0, 3,4,5, 0 ,6,7,8,9 };
	auto it = find(vec.rbegin(), vec.rend(), 0);
	cout << "it = " << *it << endl;

#endif

	return 0;



}