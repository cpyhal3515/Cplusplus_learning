#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include "my_sales_item_class.h"
using namespace std;

// 定义目前的题目序号
#define PROBLEM_8_6

#ifdef PROBLEM_8_4

void read_str_vec(vector<string>& str_vec, string file_name)
{
	ifstream file_in;
	file_in.open(file_name);
	string str_tmp;
	if (file_in)
	{
		while (getline(file_in, str_tmp))
		{
			str_vec.push_back(str_tmp);
		}
	}
	else
	{
		cerr << "Couldn't open: " + file_name << endl;
	}
	return;
}

#endif


#ifdef PROBLEM_8_5

void read_str_wd_vec(vector<string>& str_wd_vec, string file_name)
{
	ifstream file_in;
	file_in.open(file_name);
	string str_tmp;
	if (file_in)
	{
		while (file_in >> str_tmp)
		{
			str_wd_vec.push_back(str_tmp);
		}
	}
	else
	{
		cerr << "Couldn't open: " + file_name << endl;
	}
	return;
}

#endif

#ifndef PROBLEM_8_6
int main()
{
#ifdef PROBLEM_8_4
	vector<string> str_vec;
	string file_name;
	/* ---------------- 8.4 ---------------- */
	file_name = "./data.txt";
	read_str_vec(str_vec, file_name);
	cout << "str_vec length = " << str_vec.size() << endl;
#endif

#ifdef PROBLEM_8_5
	vector<string> str_wd_vec;
	string file_name;
	/* ---------------- 8.5 ---------------- */
	file_name = "./data.txt";
	read_str_wd_vec(str_wd_vec, file_name);
	cout << "str_wd_vec length = " << str_wd_vec.size() << endl;
#endif

	return 0;
}
#endif

#ifdef PROBLEM_8_6
int main(int argc, char* argv[])
{

	ifstream file_in(argv[1]);
	ofstream file_out(argv[2], ofstream::app);
	Sales_data total("X123", 0, 0);
	if (read(file_in, total))
	{
		Sales_data trans("X123", 0, 0);
		while (read(file_in, trans))
		{
			if (total.isbn() == trans.isbn())
				total.combine(trans);
			else
			{
				print(file_out, total) << endl;
				total = trans;
			}
		}
		print(file_out, total) << endl;
	}
	else
		cerr << "No data" << endl;
}
#endif