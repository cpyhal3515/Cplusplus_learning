#include<iostream>
#include<vector>
using namespace std;

// 定义目前的题目序号
#define PROBLEM_8_1

#ifdef PROBLEM_8_1
istream& read_stream(istream& stream)
{
	string str;
	while (stream >> str)
	{
		cout << "str is :" << str << endl;
	}
	stream.clear();

	return stream;
}
#endif


int main()
{
#ifdef PROBLEM_8_1
	/* ---------------- 8.1 ---------------- */
	read_stream(cin);
#endif


	return 0;
}