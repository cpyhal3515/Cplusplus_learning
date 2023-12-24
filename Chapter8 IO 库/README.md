# Chapter 8 IO 类

## 说明

> 这一部分主要是 IO 类的应用，因此这里把主要内容梳理一下，一些比较细节的比如调用函数之类的内容可以之后在书上看。

## 记录笔记

### IO 类

- 条件状态：IO 类定义了一些函数和标志，可以帮助我们访问和操作流的条件状态。

- 输出缓冲

  - 每个输出流都管理一个缓冲区，用来保存程序读写的数据。由于设备的写操作可能很耗时，允许操作系统将多个输出操作组合为单一的设备写操作可以带来很大的性能提升。

  - `endl` 操作符可以完成换行并刷新缓冲区的工作。

  - **如果程序崩溃，输出缓冲区不会被刷新，它所输出的数据很可能停留在输出缓冲区中等待打印。**

### 读写流

- 头文件为 `iostream` ，定义了 `istream` （输入流）类型，提供输入操作，以及 `ostream` （输出流）类型，提供输出操作。

- `cin` 一个 `istream` 对象，从标准输入读取数据。

- `cout` 一个 `ostream` 对象，向标准输出写入数据。

- 文件输出输出以及 string 流均继承自读写流，因此也可以正常使用 `cin` 以及 `cout` 。

### 文件流

- 头文件为 `fstream` ，定义了 `ifstream` 类型，提供读操作， `ofstream` 类型，提供写操作，以及 `fstream` 类型，提供读写操作。

- 可以使用 `getline` 从一个 ifstream 中读取数据。

- 创建文件流对象时，我们可以提供文件名，如果提供一个文件名，则 `open` 会被自动调用：

```C++
ifstream in(ifile); // 构造一个 ifstream 并打开给定文件
ofstream out; // 输出文件流未与任何文件相关联
out.open(ifile); // 打开指定文件
in.close(); // 关闭文件
```

- 文件模式：每个流都有一个关联的文件模式，用来指出如何使用文件，包括读/写/追加等。

```C++
ofstream out;
out.open("scratchpad"); // 模式隐含设置为输出和截断
out.close(); // 关闭 out
out.open("precious", ofstream::app); // 模式为输出和追加
out.close;
```

### string 流

- 头文件为 `sstream` ，定义了 `istringstream` 类型，从 string 中读取数据，以及 `ostringstream` 类型，向 string 写入数据，`stringstream` 可读可写。

- 当某些工作是对整行文本进行处理，而另一些工作是处理行内的某个单词的时候通常可以使用 `istringstream` 类型。

```C++
string line, word;
while(getline(cin, line))
  {
    string word;
    istringstream record(line); // 将记录绑定到刚读入的行
    while(record >> word)
      {
        ...
      }
  }
```

- 当需要逐步构造输出，希望最后一起打印时可以使用 `ostringstream` 类。
