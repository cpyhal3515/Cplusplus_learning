#ifndef EMPLOYEE
#define EMPLOYEE

#include<iostream>
#include<string>
#include<vector>
#include<memory>
// 定义一个 Employee 类，它包含雇员的姓名和唯一的雇员证号。
// 为这个类定义默认构造函数，以及接受一个表示雇员姓名的 string 的构造函数。
// 每个构造函数应该通过递增一个 static 数据成员来生成一个唯一的证号
class Employee
{
public:
	Employee();
	Employee(const std::string&);
	Employee(const Employee&) = delete;
	Employee& operator=(const Employee&) = delete;
	std::string getname() { return name; }
	int get_id() { return id; }
	
private:
	std::string name;
	int id;
	static int id_cnt;
};

// 注意这里需要在类外进行定义
int Employee::id_cnt = 0;

Employee::Employee()
{
	++id_cnt;
}
Employee::Employee(const std::string& _name)
{
	name = _name;
	id = id_cnt++;
}

#endif // EMPLOYEE