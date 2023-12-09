# Chapter 4 表达式

## 说明

> 由于之前学习过 C 语言和一部分 C++ 的内容，因此这里主要把一些之前不太熟悉的部分记录下来，这里感觉叫 C2C++ 比较好

## 记录笔记

### 求值顺序

- 大多数情况下，不会明确指定求值的顺序，比如在表达式 `int i = f1() * f2()` 中，我们肯定知道 `f1()` 与 `f2()` 在乘法前被调用，但是先调用 `f1()` 还是先调用 `f2()` 是不确定的。

### 短路求值

- 当左侧运算对象无法确定表达式的结果时才计算右侧运算对象的值，例如逻辑与 && 以及逻辑 || 运算。

### 递增和递减运算符

- 前置版本：`++i --i`首先将运算对象加 1（或减 1），然后将改变后的对象作为求值结果。

- 后置版本：`i++ i--` 将运算对象加 1（或减 1），但是求值结果是运算对象改变之前那个值的副本。

**Tips：除非必须，否则不要使用后置版本，因为这样会存储原始值，带来不必要的开销。**

- 使用运算符简化代码的示例：

```c
auto pbeg = v.begin();
// 输出元素直到遇到第一个负值为止
while(pbeg != v.end() && *pbeg >= 0)
  cout << *pbeg++ << endl; // 输出当前值并将 pbeg 向前移动一个元素
```

### 成员访问运算符

- 点运算符：获取类对象的一个成员。

- 箭头运算符：与点运算符有关。

`ptr->mem` 等价于 `(*ptr).mem`&#x20;

- 因为解引用运算符的优先级低于点运算符，所以执行解引用运算的子表达式两端必须加上括号。

### sizeof 运算符

- 对 `char` 或者类型为 `char` 的表达式执行 `sizeof` 运算，结果得 1。

- 对引用类型执行 `sizeof` 运算得到被引用对象所占空间的大小。

- 对指针执行 `sizeof` 运算得到指针本身所占空间的大小。

- 对解引用指针执行 `sizeof` 运算得到指针指向的对象所占空间的大小，指针不需要有效。

- 对数组执行 `sizeof` 运算可以得到整个数组所占空间的大小。

### 逗号运算符

- 可以用在 for 循环中，例如在下面的例子中每次循环迭代 `ix`和 `cnt`相应改变。

```c
auto cnt = ivec.size();
for(decltype(cnt) ix = 0; ix != ivec.size(); ++ix, --cnt)
  ivec[ix] = cnt;
```

### 命名强制类型转换

- `static_cast` ：任何具有明确定义的类型转换，只要不包含底层 const，例如：

```c
double slope = static_cast<double>(j)/i;
```

- `const_cast` ：只能改变运算对象的底层 const，常用于有函数重载的上下文中。例如在下面的函数中：

```C++
const string &shorterString(const string &s1, const string &s2)
{
  return s1.size() <= s2.size() ? s1 : s2;
}
```

当我们需要一种新的 `shorterString` 函数时，当参量不是常量时返回一个普通的引用就可以使用 `const_cast` 实现这一点：

```C++
const string &shorterString(string &s1, string &s2)
{
  auto &r = shorterString(const_cast<const string&>(s1), const_cast<const string&>(s2));
  return const_cast<const string&>(r);
}
```

**Tips：非必要不要使用强制类型转换**
