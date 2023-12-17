#ifndef MY_ACCOUNT_ITEM_H
#define MY_ACCOUNT_ITEM_H

#include<iostream>
#include<string>
#include<vector>

class Account
{
public:
	void calculate() { amount += amount * interestRate; };
	// 静态成员变量
	static double rate() { return interestRate; };
	static void rate(double);

private:
	std::string owner;
	double amount;
	static double interestRate;
	static double initRate();

	// 类内字面值常量静态成员
	static constexpr int period = 30;
	double daily_tbl[period];
};

void Account::rate(double newRate)
{
	interestRate = newRate;
}

double Account::initRate()
{
	interestRate = 1.5;
}

#endif