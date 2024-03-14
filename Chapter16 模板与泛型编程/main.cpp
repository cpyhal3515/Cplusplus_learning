#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<map>
#include<fstream>
#include <functional>
#include "section1.h"
#include "Blob_class.h"
#include "Vec_class.h"
using namespace std;

// 定义目前的题目序号
#define PROBLEM_16_19_20

#ifdef  PROBLEM_16_19_20
// 练习用 typename 指明类型成员
template <typename Container>
ostream& print19(const Container& c, ostream& os = cout)
{
    using size_type = typename Container::size_type;
    for (size_type i = 0; i != c.size(); ++i)
    {
        os << c.at(i) << " ";
    }
    return os;
}
// 练习定义函数模版，复习用迭代器遍历容器
template <typename Container>
ostream& print20(const Container& c, ostream& os = cout)
{
    for (auto iter = c.begin(); iter != c.end(); ++iter)
    {
        os << *iter << " ";
    }
    return os;
}
#endif



int main()
{
#ifdef  PROBLEM_16_04
    // 编写行为类似标准库 find 算法的模板
    vector<int> ivec{ 1, 2, 3, 4, 5, 6 };
    auto iter1 = Find(ivec.begin(), ivec.end(), 3);
    if (iter1 == ivec.end())
        cout << "Can not find 3" << endl;
    else
        cout << "Find 3 at position "
        << iter1 - ivec.begin() << endl;

    list<string> slis{ "c++", "primer", "5th" };
    auto iter2 = Find(slis.begin(), slis.end(), "5th");
    if (iter2 == slis.end())
        cout << "Can not find 5th" << endl;
    else
        cout << "Find \"5th\"" << endl;
    
#endif

#ifdef  PROBLEM_16_05
    // 为 print 函数编写模板版本，接受一个数组的引用，能处理任意大小、任意元素类型的数组
    int a[6] = { 0, 2, 4, 6, 8, 10 };
    string s[3] = { "c++", "primer", "5th" };

    print(a);
    print(s);
#endif

#ifdef  PROBLEM_16_12
    vector<int> v1(3, 43), v2(10);
    int temp[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    Blob<int> a1(v1.begin(), v1.end()),
        a2(temp, temp + sizeof(temp) / sizeof(*temp)),
        a3(v2.begin(), v2.end());

    cout << a1 << "\n\n" << a2 << "\n\n" << a3 << endl;

    cout << "\ncopy" << "\n\n";
    Blob<int> a5(a1);
    cout << a5 << endl;

    cout << "\nassignment" << "\n\n";

    a1 = a3;
    cout << a1 << "\n\n" << a2 << "\n\n" << a3 << endl;

    cout << "\nelement assignment" << "\n\n";
    a1[0] = 42;
    a1[a1.size() - 1] = 15;
    cout << a1 << "\n\n" << a3 << endl;

    Blob<string> s1;
    s1.push_back("hi");
    s1.push_back("bye");
    s1.push_back("now");
    BlobPtr<string> p(s1);    // p points to the vector inside s1
    *p = "okay";                 // assigns to the first element in s1
    cout << p->size() << endl;   // prints 4, the size of the first element in s1
    cout << (*p).size() << endl; // equivalent to p->size()

    Blob<string> s2;
    s2.push_back("one");
    s1.push_back("two");
    s1.push_back("three");
    // run the string empty function in the first element in s2
    if (s2[0].empty())
        s2[0] = "empty"; // assign a new value to the first string in s2

    cout << a1 << endl;
    cout << a2 << endl;
    a2.swap(a1);
    cout << a1 << endl;
    cout << a2 << endl;
#endif

#ifdef  PROBLEM_16_13
    Vec<int> svec;
    for (int i = 0; i < 10; ++i)
    {
        svec.push_back(i);
    }
    cout << "svec = " << svec.size() << endl;
    for_each(svec.begin(), svec.end(), [](const int& item) {cout << item << " "; });
    cout << endl;

    cout << "copy, svec2 = " << svec.size() << endl;
    Vec<int> svec2 = svec;
    for_each(svec2.begin(), svec2.end(), [](const int& item) {cout << item << " "; });
    cout << endl;

    cout << "assign, svec3 = " << endl;
    Vec<int> svec3;
    svec3 = svec2;
    for_each(svec3.begin(), svec3.end(), [](const int& item) {cout << item << " "; });
    cout << endl;
#endif

#ifdef  PROBLEM_16_19_20
    vector<int> ivec{ 1, 2, 3, 4, 5, 6 };
    print19(ivec) << "\n";
    print20(ivec) << "\n";



#endif
}