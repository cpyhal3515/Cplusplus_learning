#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<map>
#include<fstream>
#include <functional>
#include "my_sales_item_class.h"
#include "StrBlob_class.h"
#include "StrVecClass.h"
#include "StringClass.h"
using namespace std;

// 定义目前的题目序号
#define PROBLEM_14_44


#ifdef  PROBLEM_14_35
class GetInput
{
public:
    GetInput(istream& in = cin) : is(in){}
    string operator()() 
    { 
        string str;
        getline(is, str);
        return is ? str : string();
    }

private:
    istream& is; // 用于写入的目的流

};
#endif


#ifdef  PROBLEM_14_38
class LenJudge
{
public:
    LenJudge(int len_) :len(len_) {};
    bool operator()(const string& str) const 
    {
        return str.size() == len;
    }
private:
    int len;
};

#endif

#ifdef  PROBLEM_14_44
// 普通函数
int add(int i, int j)
{
    return i + j;
}
// lambda，其产生一个未命名的函数对象类
auto mod = [](int i, int j) { return i % j; };
// 函数对象类
struct divide
{
    int operator() (int denominator, int divisor)
    {
        return denominator / divisor;
    }
};

#endif
int main()
{
#ifdef  PROBLEM_14_2
    // 测试数据：978-7-121-15535-2 200 99.9
    // 另一个有问题的测试数据 200 99.9 978-7-121-15535-2
    //Sales_data data_test;
    //cin >> data_test;
    //cout << data_test << endl;

    Sales_data b1("978-7-121-15535-2", 1, 97.9);
    Sales_data b2("978-7-121-15535-2", 1, 99.9);

    std::cout << b1 + b2 << std::endl;
    b1 += b2;
    std::cout << b1 << std::endl;
#endif

#ifdef  PROBLEM_14_18
    StrBlob b1 = { "a", "an", "the" };
    StrBlob b2 = { "a", "an", "the" };
    StrBlob b3 = { "a", "an", "the", "haha" };
    // StrBlob 重载运算符 != 的调用
    if (b1 == b2)
    {
        // StrBlobPtr 重载运算符 != 的调用
        for (StrBlobPtr iter = b1.begin(); iter != b1.end(); ++iter)
            cout << iter.deref() << " ";
    }
    cout << endl;

    std::cout << "b1 > b2 : " << (b1 > b2) << std::endl;
    std::cout << "b1 < b3 :" << (b1 < b3) << std::endl;
    std::cout << "b1 >= b3 :" << (b1 >= b3) << std::endl;
    std::cout << "b2 <= b3 :" << (b2 <= b3) << std::endl;

    StrVec con_vec_list_1{ "c++", "primer", "5th" };
    //StrVec con_vec_list_2{ "c++", "primer", "5th" };
    StrVec con_vec_list_2{ "c++", "primer", "4th" };
    if (con_vec_list_1 == con_vec_list_2)
    {
        cout << "con_vec_list_1 == con_vec_list_2" << endl;
    }
    else
    {
        cout << "con_vec_list_1 != con_vec_list_2" << endl;
    }
    StrVec vec_list{ "c++", "primer", "5th", "lippman" };
    std::cout << "vec_list > con_vec_list_1 : " << (vec_list > con_vec_list_1) << std::endl;
    std::cout << "vec_list < con_vec_list_1 :" << (vec_list < con_vec_list_1) << std::endl;
    std::cout << "con_vec_list_2 < vec_list :" << (con_vec_list_2 < vec_list) << std::endl;
    std::cout << "con_vec_list_2 >= con_vec_list_1 :" << (con_vec_list_2 >= con_vec_list_1) << std::endl;

    String A("Ni Hao");
    //String B("Ni Hao");
    String B("Ni Hao Ma");
    if (A == B)
    {
        cout << "A == B" << endl;
    }
    else
    {
        cout << "A != B" << endl;
    }

    String s1("One"), s2("Oneone");
    String s3(s2);
    if (s1 < s2)
        cout << "s1 < s2" << endl;
    else
        cout << "s1 >= s2 " << endl;
    if (s3 >= s2)
        cout << "s3 >= s2" << endl;
    else
        cout << "s3 < s2 " << endl;

#endif

#ifdef  PROBLEM_14_23
    StrVec con_vec_list_1 = { "c++", "primer", "5th" };
    for (auto iter = con_vec_list_1.begin(); iter != con_vec_list_1.end(); ++iter)
    {
        cout << *iter << endl;
    }


#endif

#ifdef  PROBLEM_14_26

    // 测试 StrBlob
    StrBlob b1 = { "a", "an", "the" };
    for (int i = 0; i < b1.size(); ++i)
    {
        cout << b1[i] << " ";
    }
    cout << endl;
    b1[1] = "haha";
    for (int i = 0; i < b1.size(); ++i)
    {
        cout << b1[i] << " ";
    }
    cout << endl;


    // 测试 StrVec
    StrVec con_vec_list_1{ "c++", "primer", "5th" };
    cout << con_vec_list_1[0] << endl;

    // 测试 String
    String s1("One");
    cout << s1[2] << endl;
#endif

#ifdef  PROBLEM_14_28
    StrBlob b1 = { "a", "an", "the" };
    StrBlobPtr itr(b1);
    itr += 1;
    cout << itr.deref() << endl;
#endif

#ifdef  PROBLEM_14_35
    // Welcome To CPlusPlus
    GetInput getInput;
    cout << getInput() << endl;
#endif

#ifdef  PROBLEM_14_38
    int len = 3;
    LenJudge lenjudge(len);
    vector<string> svec = {"haha", "ni", "hao", "hello", "world"};
    std::cout << "len : " << len << ", cnt : "
        << std::count_if(svec.begin(), svec.end(), lenjudge)
        << std::endl;
#endif

#ifdef  PROBLEM_14_42
    // 统计大于 1024 的值有多少个
    // _1 是一个占位符，代表新可调用对象的第一个参数。
    // 当std::count_if在ivec的每个元素上调用这个可调用对象时，
    // 每个元素都会作为第一个参数（即占位符_1所在的位置），
    // 而1024是作为std::greater<int>的第二个参数固定下来的。
    // 在这里，bind 实际上是把 greater<int>() 这个双参数函数转换为一个单参数函数，
    // 固定第二个参数为1024。
    // 所以每次调用这个新的单参数函数时，它实际上是在比较容器中的每个元素（作为第一个参数）是否大于1024。
    vector<int> ivec{ 1000, 2000, 3000, 4000, 5000 };
    cout << count_if(ivec.begin(), ivec.end(),
        bind(std::greater<int>(), placeholders::_1, 1024)) << endl;

    // 找到第一个不等于 pooth 的字符串
    vector<string> svec{ "pooth", "pooth", "abc", "pooth" };
    cout << *find_if(svec.begin(), svec.end(),
        bind(not_equal_to<string>(), placeholders::_1, "pooth"))
        << endl;

    // 将所有的值乘以 2
    transform(ivec.begin(), ivec.end(), ivec.begin(),
        std::bind(std::multiplies<int>(), placeholders::_1, 2));
    for (const auto& i : ivec)
        cout << i << " ";
#endif

#ifdef  PROBLEM_14_44
    // 列举了可调用对象与二元运算符对应关系的表格
    // 所有可调用对象都必须接受两个 int，返回一个 int
    // 其中的元素可以是函数指针、函数对象或者 lambda
    map<string, function<int(int, int)>> binops =
    {
        {"+", add},
        {"-", minus<int>()},
        {"/", divide()},
        {"*", [](int i, int j) {return i * j; }},
        {"%", mod}

    };
    cout << binops["+"](1, 2) << endl;
    cout << binops["-"](1, 2) << endl;
    cout << binops["/"](1, 2) << endl;
    cout << binops["*"](1, 2) << endl;
    cout << binops["%"](1, 2) << endl;


#endif
}