# Chapter 5 语句

## 说明

> 由于之前学习过 C 语言和一部分 C++ 的内容，因此这里主要把一些之前不太熟悉的部分记录下来，这里感觉叫 C2C++ 比较好

## 记录笔记

### try 语句块与异常处理

- 异常处理机制主要包含**异常检测**以及**异常处理**。

  - `throw` ：异常检测部分使用它表示遇到无法处理的问题，`throw` 引发了异常。

  - `try - catch` ：异常处理部分，在语句块中编写异常处理代码。

- 下面给一个例子，用来检测除法中分母为 0 的情况：

```C++
int num1, num2;
  cout << "Please input two num, num1 / num2" << endl;
  while (cin >> num1 >> num2)
  {
      try
      {
          if (num2 == 0)
          {
              throw runtime_error("num2 cannot be 0!");
          }

          cout << num1 / num2 << endl;
      }
      catch (runtime_error err)
      {
          cout << err.what() << endl;
          cout << "Try again? Enter y or n" << endl;
          string str;
          cin >> str;
          if (!cin || str == "n")
              break;
      }
  }
```
