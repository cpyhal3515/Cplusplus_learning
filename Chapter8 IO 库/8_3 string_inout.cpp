#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include "my_sales_item_class.h"
using namespace std;

// 定义目前的题目序号
#define PROBLEM_8_10


#ifdef PROBLEM_8_10
int main()
{
	string file_name("./data.txt");
	ifstream file_in(file_name);

	vector<string> string_vec;

	string line_word;
	while (getline(file_in, line_word))
	{
		string_vec.push_back(line_word);
	}


	for (int i = 0; i < string_vec.size(); ++i)
	{
		string word_tmp;
		istringstream per_word(string_vec[i]);
		while (per_word >> word_tmp)
		{
			cout << "word tmp = " << word_tmp << endl;
		}
	}
	
	

}
#endif