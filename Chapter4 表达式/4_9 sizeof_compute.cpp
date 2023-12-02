#include<iostream>
using namespace std;

int main()
{
	/* ---------------- 4.28 ---------------- */
	// 判断内置类型的大小
	cout << "sizeof(short) = " << sizeof(short) << endl;
	cout << "sizeof(int) = " << sizeof(int) << endl;
	cout << "sizeof(char) = " << sizeof(char) << endl;
	cout << "sizeof(long) = " << sizeof(long) << endl;
	cout << "sizeof(long long) = " << sizeof(long long) << endl;

	/* ---------------- 4.29 ---------------- */
	// 判断代码输出结果是否相同
	int x[10];
	int* p = x;
	cout << sizeof(x) / sizeof(*x) << endl;
	cout << sizeof(p) / sizeof(*p) << endl;

	int i;
	double d;
	const string* ps;
	char* pc;
	void* pv;
	pv = (void*)ps;
	pv = static_cast<void*> (const_cast<string*>(ps));


	return 0;

}