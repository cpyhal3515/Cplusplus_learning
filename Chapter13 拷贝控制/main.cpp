#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<map>
#include<fstream>
//#include "XClass.h"
//#include "EmployeeClass.h"
//#include "HasPtrClass_val.h"
#include "StrVecClass.h"
#include "StringClass.h"
using namespace std;

// 定义目前的题目序号
#define PROBLEM_13_39_40


#ifdef  PROBLEM_13_14_15_16
class numbered 
{
public:
    numbered() 
    {
        mysn = unique++;
    }
    numbered(const numbered& n)
    {
        mysn = unique++;
    }

    int mysn;
    static int unique;
};

int numbered::unique = 10;

void f(numbered& s) 
{
    std::cout << s.mysn << std::endl;
}

#endif

int main()
{
#ifdef  PROBLEM_13_13
    // 理解拷贝控制成员和构造函数的一个好方法的定义一个简单的类，为该类定义这些成员，每个成员都打印出自己的名字
	X* x = new X;
	delete x;
#endif
  
#ifdef  PROBLEM_13_14_15_16
    // 假定 numbered 是一个类，它有一个默认构造函数，
    // 能为每个对象生成一个唯一的序号，保存在名为 mysn 的数据成员中。
    numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);
#endif

#ifdef PROBLEM_13_18
     // 定义一个 Employee 类，它包含雇员的姓名和唯一的雇员证号。
    Employee member1("Zhang San");
    Employee member2("Li Si");
    cout << "member1 name = " << member1.getname() << " , member1 id = " << member1.get_id() << endl;
    cout << "member2 name = " << member2.getname() << " , member2 id = " << member2.get_id() << endl;

#endif // PROBLEM_13_18

#ifdef PROBLEM_13_31
    vector<HasPtr> vec;
    for (int i = 0; i < 10; ++i)
    {
        string str = "a";
        HasPtr tmp(str, 10-i);
        vec.push_back(tmp);
    }
    sort(vec.begin(), vec.end());
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        it->print();
    }

#endif
#ifdef PROBLEM_13_39_40
    // 测试 StrVec
    StrVec test = {"a", "b", "c"};
    test.push_back("nihao1");
    test.push_back("nihao2");
    test.push_back("nihao3");

    for (auto it = test.begin(); it != test.end(); ++it)
    {
        cout << *it << endl;
    }

    // 测试 String
    vector<String> tmp;
    tmp.push_back("nihao1");
    tmp.push_back("nihao2");
    tmp.push_back("nihao3");
    tmp[2] = tmp[1];
    for (auto it = tmp.begin(); it != tmp.end(); ++it)
    {
        auto beg = it->c_str();

        for (int i = 0; i < it->size(); ++i)
        {
            cout << beg[i];
        }
        cout << endl;
    }
    
#endif // PROBLEM_13_39





}