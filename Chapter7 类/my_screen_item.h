#ifndef MY_SCREEN_ITEM_H
#define MY_SCREEN_ITEM_H

#include<iostream>
#include<string>
#include<vector>

class Window_mgr
{
public:
	// 声明类型别名
	using ScreenIndex = std::vector<Screen>::size_type;
	void clear(ScreenIndex);
private:
	std::vector<Screen> screens{ Screen(24, 80, ' ') };
};

void Window_mgr::clear(ScreenIndex i)
{
	Screen& s = screens[i];
	s.contents = std::string(s.height * s.width, ' ');
}


class Screen
{	
public:
	// 声明类型别名
	using pos = std::string::size_type;
	// 函数方式定义友元
	friend void Window_mgr::clear(ScreenIndex);
	// 类方式定义友元
	//friend class Window_mgr;
	Screen() = default;
	Screen(pos ht, pos wd) : height(ht), width(wd), contents(ht*wd, ' ') {};
	Screen(pos ht, pos wd, char ch) : height(ht), width(wd), contents(ht*wd, ch) {};

	inline Screen& move(pos, pos);
	inline Screen& set(const char);
	inline Screen& display(std::ostream&);

	pos size() const
	{
		return height * width;
	}

private:
	pos cursor = 0;
	pos height = 0, width = 0;
	std::string contents;
};


Screen& Screen::move(pos r, pos c)
{
	cursor = r * width + c;
	return *this;
}
Screen& Screen::set(const char ch)
{
	contents[cursor] = ch;
	return *this;
}
Screen& Screen::display(std::ostream& os)
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			os << contents[i * width + j];
		}
		os << std::endl;
	}
	return *this;
}





#endif