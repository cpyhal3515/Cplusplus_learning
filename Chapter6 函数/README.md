# Chapter 6 函数

## 说明

> 由于之前学习过 C 语言和一部分 C++ 的内容，因此这里主要把一些之前不太熟悉的部分记录下来，这里感觉叫 C2C++ 比较好

## 记录笔记

### 函数基础

#### 局部对象

- 内置类型的未初始化局部变量将产生未定义的值。

- 局部静态对象：在程序第一次执行到这条语句的时候初始化，直到程序终止才被销毁，在此期间即使对象所在的函数结束执行也不会对它有影响，比如在下面这个函数中，函数每被调用一次 `cnt`的值就会加一。

```C++
int count_calls()
{
	static int cnt = 0;
	return ++cnt;
}

int main()
{
	for (int i = 0; i < 10; i++)
	{
		cout << count_calls() << endl;
	}
	return 0;
}
// 输出：1,2,3,4,5,6,7,8,9
```

### 参数传递

#### 传引用参数

- 使用引用可以**避免拷贝**。

- 使用引用可以**传递额外的信息**。

- 对于函数不会改变的形参值，最好**不要定义成普通的引用**，而是要**定义成常量引用**。一方面定义成常量引用不怕在函数中被错误修改，另一方面可以传递的参数类型较多（const 对象，字面值都可以传递）。

#### 命令行选项

- 对于 `int main(int argc, char *argv[]) {}` 这种类型的 `main` 函数的定义，可以传递实参，`argc` 表示数组中字符串的数量，`argv` 表示字符串数组，保存传入的字符串列表选项。**注意**：可选的实参从 `argv[1]`开始，`argv[0]` 保存程序的名字。

#### 可变形参

- 对于无法提前预知需要传递的实参个数的情况，如果所有的实参类型相同则可以通过 `initializer_list` 的标准库类型传递这些实参，例如在下面的例子中：

```C++
void error_msg(initializer_list<string> i1)
{
  for(auto beg = il.begin(); beg != il.end(); ++beg)
    {
      cout << *beg << " ";
    }
  cout << endl;
}
```

### 返回类型和 return 语句

- 返回类类型的函数可以实现调用：例如在这样一条语句中 `auto sz = shorterString(s1, s2).size() `，函数返回一个 `string` 类型的数据，则可以调用对应的 `size` 运算。

- 引用返回左值：可以为返回类型是非常量引用的函数的结果赋值，例如在下面的例子中：

```C++
char &get_val(string &str, string::size_type ix)
{
  return str[ix];
}

get_val(s, 0) = 'A'; // 将 s[0] 的值改为 A
```

- 列表初始化返回值：函数可以返回花括号包围的值的列表，例如在下面的例子中：

```C++
vector<string> process()
{
  // expected 和 actual 是 string 对象
  if(expected.empty()) // 返回一个空 vector 对象
    return {};
  else if(expected == actual)
    return {"functionX", "okay"}; // 返回列表初始化的 vector 对象
  else
    return {"functionX", expected, actual};
}
```

#### 返回数组指针

- 声明一个返回数组指针的函数 `int (*func(int i))[10];`：

  - `func(int i)` ：表示调用 `func` 函数时需要一个 int 类型的实参。

  - `(*func(int i))` ：表示可以对函数调用的结果执行解引用操作。

  - `(*func(int i))[10]` ：表示解引用后可以得到一个大小是 10 的数组。

  - `int (*func(int i))[10]` ：表示数组中的元素是 int 类型。

### 函数重载

- **重载函数**：同一作用域内的几个函数名字相同但是形参列表不同。

  - 对于重载的函数，应该在形参数量或者形参类型上有所不同。

  - 不允许两个函数除了返回类型外其它所有的要素都相同。

```C++
// 这是一种典型的数据库应用
Record lookup(const Account&);
Record lookup(const Phone&);

Account acct;
Phone phone;
Record r1 = lookup(acct);// 调用接受 Account 的版本
Record r2 = lookup(phone);// 调用接受 Phone 的版本
```

#### 函数匹配

```C++
void f();
void f(int);
void f(int ,int);
void f(double, double = 3.14);
```

- Step1：确定候选函数和可行函数。

  - 候选函数：与被调用函数同名 +声明在调用点可见。

  - 可行函数：形参数量与实参数量相等 + 实参类型与对应的形参类型相同，或者能转换成形参的类型。

- Step2：寻找最佳匹配（如果有的话）

  - 实参类型与形参类型越接近，它们匹配得越好。对于 `f(3.6)` 这个调用 `f(double, double = 3.14)` 就比 `f(int)` 匹配的更好，因为 int 还要转换成 double。

- 对于多个形参：只有存在一个函数满足别的参数都更别的函数差不多，并且有一个参数明显更好，这样才能正确匹配出来一个函数，否则这个调用会因为二义性而被拒绝，例如对 `f(42, 2.56)` 就会有 `f(int ,int)` 以及 `f(double, double = 3.14)` 匹配的程度差不多，因此会有二义性。

### 特殊用途语言特性

#### 默认实参

- 把函数调用中多次重复使用的相同的值设定为一个默认实参，这样在参数传递的过程中就可以省略这个参数了，下面是一个例子：

```C++
typedef string::size_type sz;
string screen(sz ht = 24, sz wid = 80; char backgrnd = '');
// 下面是可选的调用方式：
screen();
screen(66);
screen(66, 256);
screen(66, 256, '#');
```

- 在默认实参的函数调用过程中，只能将输入参数覆盖函数的前几个参量，后面的参数会被默认实参自动填补，因此需要合理设计形参的顺序。
