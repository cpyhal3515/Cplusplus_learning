# Chapter 10 泛型算法

## 说明

> 泛型算法通过迭代器将算法与容器类型进行了解耦。

## 记录笔记

### 概述

#### 泛型算法概述

- 迭代器使得算法不依赖于容器。

- 但是算法依赖于元素类型的操作，例如比较运算符 `==` 。

- 算法不会执行容器的操作，即只能修改容器中的元素而无法修改容器本身（例如删除元素之类的）。

#### 泛型算法结构

- 5 类迭代器：

  - 输入迭代器，只能读取序列中的元素。

  - 输出迭代器，只能给序列写入元素。

  - 前向迭代器，在序列中沿一个方向移动，可读可写。

  - 双向迭代器，可以正向/反向读写序列中的元素。

  - 随机访问迭代器，提供在常量时间内访问序列中任意元素的能力。

- 算法形参模式：

```C++
alg(beg, end, other args);
alg(beg, end, dest, other args);
alg(beg, end, beg2, other args);
alg(beg, end, beg2, end2, other args);
```

- 算法命名规范

  - 谓词的传递：

    - `unique(beg, end)` ：使用 `==` 运算符比较元素。

    - `unique(beg, end, comp)` ：使用 comp 比较元素。

  - if 版本的算法：

    - `find(beg, end, val)` ：查找输入范围中 val 第一次出现的位置。

    - `find_if(beg, end, pred)` ：查找第一个令 pred 为真的元素。

  - 区分拷贝元素的版本和不拷贝元素的版本：

    - `reverse(beg, end)` ：翻转输入范围中的元素的顺序。

    - `reverse_copy(beg, end, dest)` ：将元素按逆序拷贝到 dest。

### 定制操作

#### 向算法传递函数

- 谓词：是一个可调用的表达式，其返回结果是一个能用作条件的值。接受谓词的算法对输入序列中的元素调用谓词。

  - 一元谓词：只接受单一参数。

  - 二元谓词：有两个参数。

```C++
bool isShorter(const string &s1, const string &s2)
{
  return s1.size() < s2.size();
}

sort(words.begin(), words.end(), isShorter);
```

#### lambda 表达式

- 一个 lambda 表达式表示一个可调用的代码单元。

  - 捕获列表 capture list 是一个 lambda 所在函数中定义的局部变量的列表。

  - parameter list 表示参数列表。

  - function body 表示函数体。

  - return type 表示函数的返回类型。

```C++
[capture list](parameter list) -> return type {function body}
```

- 向 lambda 传递参数：

```C++
sort(words.begin(), words.end(), [](const string &a, const string &b){return a.size() < b.size();});
```

- 使用捕获列表：可以将局部变量包含在捕获列表中，并在之后使用这些局部变量。有值捕获以及引用捕获两种方式，引用捕获主要用于传递 ostream 形式的变量。

```c++
// 值捕获：查找第一个长度大于等于 sz 的元素
auto wc = find_if(words.begin(), words.end(), [sz](const string &a){return a.size() >= sz;});
// 值捕获：打印长度大于等于给定值的单词
for_each(wc, words.end(), [sz](const string &s){cout << s << " ";});
// 引用捕获：打印 words 中的单词到 os
for_each(words.begin(), words.end(), [&os, c](const string &s){os << s << " ";});
```

- 指定 lambda 返回类型：如果 lambda 体包含 return 之外的任何语句，则编译器假定此 lambda 返回 void，因此当需要为一个 lambda 定义返回类型时，必须使用尾置返回类型。

```C++
transform(vi.begin(), vi.end(), vi.begin(),
          [](int i) -> int
          {if(i < 0) return -i; else return i;});
```

### 迭代器

#### 插入迭代器

- 接受一个容器，生成一个迭代器，能实现向给定容器添加元素。由于算法不检查写操作，因此要保证写入的位置完成开辟，从而需要这些插入迭代器。

  - `back_inserter` ：创建一个使用 push_back 的迭代器。

  - `front_inserter` ：创建一个使用 push_front 的迭代器。

  - `inserter` ：创建一个使用 insert 的迭代器，在该函数的第二个参数中给定一个指向给定容器的迭代器，元素会被插到给定迭代器所表示的元素之前。

```C++
list<int> lst = {1,2,3,4};
list<int> lst2, lst3; // 空 list
// 拷贝完成之后，lst2 包含 4 3 2 1
copy(lst.cbegin(), lst.cend(), front_inserter(lst2));
// 拷贝完成之后，lst3 包含 1 2 3 4
copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin()));
```

#### iostream 迭代器

- 将它们对应的流当做一个特定类型的元素序列来处理，可以用泛型算法从流对象读取数据以及向其写入数据。

- istream_iterator：读取输入流。

```C++
istream_iterator<int> in_iter(cin), eof; // 从 cin 读取 int
vector<int> vec(in_iter, eof); // 从迭代器范围构造 vec
```

- ostream_iterator：向一个输出流写入数据。

```C++
ostream_iterator<int> out_iter(cout, " ");
// 调用 copy 来打印 vec 中的元素
copy(vec.begin(), vec.end(), out_iter);
cout << endl;
```

#### 反向迭代器

- 从尾元素向首元素反向移动的迭代器。

![](README_md_files/b8c5ffb0-aaf4-11ee-aaaa-27ef589b020d_20240104193054.jpeg?v=1&type=image&token=V1%3A683GZDvpQSlBfMCChBc5d_rdP9gXfulcyLpXYJkqbx8)
