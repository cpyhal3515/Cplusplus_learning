# Chapter 14 重载运算与类型转换

## 说明

> 重载运算就是用户自定义一些基本的操作符。

## 记录笔记

### 基本概念

*   重载运算符是具有特殊名字的函数：它们的名字由关键字 `operator` 和其后要定义的运算符号共同组成。和其它函数一样，重载的运算符也包含返回类型、参数列表以及函数体。

*   一元运算符有一个参数，二元运算符有两个。如果一个运算符函数是成员函数，则它的第一个（左侧）运算对象绑定到隐式的 `this` 指针上，即显示参数比一般的情况少一个。

*   重载运算符函数的调用既可以使用符号形式，也可以使用函数形式：

```C++
// 普通的表达式
data1 + data2;
// 等价的函数调用
operator+(data1, data2);
```

*   尽量不要重载 `&&` 以及 `||` 符号，因为重载无法保证短路求值属性。

### 输入输出运算符

*   输入输出运算符必须是非成员函数，一般被声明为友元。

#### 重载输出运算符 <<

*   第一个参量是非常量`ostream`对象的引用，第二个参量是要输出的常量引用。

```C++
ostream& operator<<(std::ostream& os, const Sales_data& item)
{
	os << "isbn = " << item.isbn() << " , " \
		<< "units_sold = " << item.units_sold << " , " \
		<< "revenue = " << item.revenue << " , " \
		<< "avg_price = " << item.avg_price();
	return os;
}
```

#### 重载输入运算符 >>

*   第一个参量是非常量`istream`对象的引用，第二个参量是将要读入到的非常量引用。

```C++
istream& operator>>(std::istream& is, Sales_data& item)
{
	double price;
	is >> item.bookNo >> item.units_sold >> price;
	if (is)
	{
		// 检查输入是否成功
		item.revenue = item.units_sold * price;
	}
	else
	{
		// 输入失败：对象被赋予默认的状态
		item = Sales_data();
	}
	return is;
}
```

### 赋值、算数和关系运算符

#### 赋值运算符

*   在拷贝赋值和移动赋值中说过了，Chapter13。

#### 算数运算符

*   一般先定义复合赋值运算符，再通过该运算符定义算数运算符。

```C++
// 定义复合赋值运算符
Sales_data& operator+=(const Sales_data& rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum += rhs;
	return sum;
}
```

#### 相等运算符

*   比较对象的每一个数据成员，只有当所有对应的成员都相等时才认为两个对象相等，不相等的运算符可以委托给相等运算符来定义。

```C++
bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
  return lhs.isbn() == rhs.isbn() && lhs.units_sold == rhs.units_sold && lhs.revenue == rhs.revenue;
}

bool operator!=(const Sales_data &lhs, const Sales_data &rhs)
{
  return !(lhs == rhs);
}
```

#### 关系运算符

*   比较大小等，**需要注意**只有存在唯一可靠的关系逻辑时才可以定义关系运算符，比如对 Sales\_data 来说，如果 `operator<` 比较的是 isbn，则两个 isbn 相同但 revenue 以及 units\_sold 不同的元素并不相等，但是双方又互不满足 < 关系，因此最好不要对 Sales\_data 定义关系运算符。

### 下标运算符

*   通过元素在容器中的位置访问元素，通常返回所访问元素的引用。最好同时定义下标运算符的常量版本以及非常量版本（当作用与一个常量对象时，下标运算符返回常量引用），当非常量时，因为返回的是引用，可以给元素赋值。

```C++
// 下标运算符
std::string& operator[](std::size_t n)
{
	return elements[n];
}
// 下标运算符 const 版本
const std::string& operator[](std::size_t n) const
{
	return elements[n];
}
```

### 递增和递减运算符

*   实现前置以及后置的 `++` 与 `--` 功能，建议将其设定为成员函数，注意区分前置以及后置运算符。后置版本接受一个额外的（不被使用）的 int 类型的形参，后置版本可以通过委托前置版本的方式实现。

```C++
StrBlobPtr& StrBlobPtr::operator++()
{
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}
StrBlobPtr& StrBlobPtr::operator--()
{
	// 如果 curr 是 0，则继续递减它会产生一个无效下标
	--curr;
	check(curr, "decrement past begin of StrBlobPtr");
	return *this;
}

// 后置版本：递增/递减对象的值但是返回原值
StrBlobPtr& StrBlobPtr::operator++(int) {
	// 此处无需检查有效性，调用前置递增运算时才需要检查
	StrBlobPtr ret = *this;         // 记录当前的值
	++*this;        // 向前移动一个元素，前置++需要检查递增的有效性
	return ret;     // 返回之前记录的状态
}
StrBlobPtr& StrBlobPtr::operator--(int) {
	// 此处无需检查有效性，调用前置递减运算时才需要检查
	StrBlobPtr ret = *this;         // 记录当前的值
	++*this;        // 向后移动一个元素，前置--需要检查递减的有效性
	return ret;     // 返回之前记录的状态
}
```

### 函数调用运算符

*   如果类重载了函数调用运算符 `operator()`，则我们可以像使用函数一样使用该类的对象。

```C++
class absInt
{
  int operator()(int val) const
  {
    return val < 0 ? -val : val;
  }
}

int i = -42;
absInt absObj;
int ui = absObj(i);
```

#### lambda 是函数对象

*   即可以使用函数对象的方式对 lambda 进行替换。

```C++
auto wc = find_if(words.begin(), words.end(), [sz](const string &a) {return a.size() >= sz;});
```

该 lambda 表达式产生的类将形如：

```C++
class SizeComp
{
public:
  SizeComp(size_t n): sz(n) {} // 该形参对应捕获的变量
  // 该调用运算符的返回类型、形参和函数体都与 lambda 一致
  bool operator()(const string &s) const
    {return s.size() >= sz;}
private:
  size_t sz; // 该数据成员对应通过值捕获的变量
}

auto wc = find_if(words.begin(), words.end(), SizeComp(sz));
```

#### 标准库定义的函数对象

*   定义在 `functional` 头文件中。

*   标准库定义了一组表示算术运算符、关系运算符和逻辑运算符的类，每个类分别定义了一个执行命名操作的调用运算符。这些类都定义成了模板的形式，我们可以为其指定具体的应用类型。

```C++
plus<int> intAdd; // 可执行 int 加法的函数对
negate<int> intNegate; // 可对 int 值取反的函数对象
// 使用 intAdd::operator(int, int) 求 10 和 20 的和
int sum = intAdd(10, 20); // 等价于 sum = 30
sum = intNegate(intAdd(10, 20)) // 等价于 sum = 30
```

*   在默认情况下 `sort` 排序算法使用的是 `operator<` ，将序列按照升序排列，如果要进行降序排列的话，我们可以传入一个 `greater` 类型的对象，该类将产生一个调用运算符，并执行待排序类型的大于运算，例如：

```C++
// 如果 svec 是一个 vector<string> 
sort(svec.begin(), svec.end(), greater<string>());
```

#### 可调用对象与 function

*   两个不同类型的可调用对象可能共享同一种**调用形式**，调用形式指明了调用返回的类型以及传递给调用的实参类型，例如 `int(int, int)` 。

*   可以定义一个**函数表**，用于存储指向这些可调用对象的“指针”，当程序需要执行某个特定的操作时，从表中查找该调用的函数。

```C++
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

binops["+"](1, 2)
binops["-"](1, 2)
binops["/"](1, 2)
binops["*"](1, 2)
binops["%"](1, 2)
```

### 重载、类型转换与运算符

*   类类型转换运算符是类的一种特殊成员函数，它负责将一个类的类型值转换成其他类型，类型转换的一般形式如下 `operator type() const;` ，但是在大多数情况下，如果类型转换自动发生，用户可能会感觉比较意外，因此类很少提供类型转换运算符，并且提供的话最好用显式的类型转换运算符。

```C++
class SmallInt
{
  public:
    // 编译器不会自动执行这一类型的转换
    explicit operator int() const { return val;}
};


SmallInt si = 3;
static_cast<int>(si) + 3; // 显式的请求转换
```



















































