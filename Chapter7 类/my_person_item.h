#ifndef MY_PERSON_ITEM_H
#define MY_PERSON_ITEM_H

#include<iostream>
#include<string>

class Person
{
	// 定义 istream 以及 ostream 为友元
	friend std::istream& read(std::istream&, Person&);
	friend std::ostream& print(std::ostream&, const Person&);
public:
	// 定义 Person 类的构造函数
	Person() = default;
	Person(const std::string name = "") : name(name) {};
	Person(const std::string name = "", const std::string address = "") :
		name(name), address(address) {}; 


	// 返回 Person 类对应的姓名
	std::string get_name() const
	{
		return name;
	}
	// 返回 Person 类对应的地址
	std::string get_address() const
	{
		return address;
	}
	

private:
	// 定义 Person 拥有的私有数据类型
	std::string name;
	std::string address;

};


// 声明 read 函数
std::istream& read(std::istream& is, Person& ps);
// 声明 print 函数
std::ostream& print(std::ostream& os, const Person& ps);
// 定义 read 函数
std::istream& read(std::istream& is, Person& ps)
{
	is >> ps.name >> ps.address;
	return is;
}
// 定义 print 函数
std::ostream& print(std::ostream& os, const Person& ps)
{
	os << "Name = " << ps.name << " , Address = " << ps.address;
	return os;
}


#endif