#ifndef MY_DEBUG_ITEM_H
#define MY_DEBUG_ITEM_H

#include<iostream>
#include<string>
#include<vector>

class Debug
{
public:
	// 常量值
	constexpr Debug(bool b = true) : hw(b), io(b), other(b) {}
	constexpr Debug(bool h, bool i, bool o) : hw(h), io(i), other(o) {}
	constexpr bool any() { return hw || io || other; }

	void set_io(bool b) { io = b; };
	void set_hw(bool b) { hw = b; };
	void set_other(bool b) { other = b; };

private:
	bool hw;
	bool io;
	bool other;
};



#endif