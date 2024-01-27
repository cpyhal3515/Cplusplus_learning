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
#define PROBLEM_12_26




int main()
{
#ifdef  PROBLEM_12_26
	// 使用 allocate 实现算法
	int n = 5;
	// 开辟动态数组并读入数据
	allocator<string> aloc;
	auto p = aloc.allocate(n);
	auto q = p;

	string s;
	while (cin >> s && q != p + n)
		aloc.construct(q++, s);

	const size_t size = q - p;
	
	// 使用数组
	auto print_idx = p;
	while (print_idx != q)
		cout << *print_idx++ << endl;


	// 销毁动态数组
	while (q != p)
		aloc.destroy(--q);
	aloc.deallocate(p, n);





	
#endif





}