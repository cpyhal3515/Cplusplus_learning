# Chapter 12 动态内存

## 说明

> 动态内存实际上类似于一个可以自动 free 的 C 语言中的 malloc，而 new 与 delete 就类似 C 语言中的 malloc 以及 free。

## 记录笔记

### 动态内存与智能指针

#### 动态内存概述

*   静态内存：保存局部 static 对象，类 static 对象成员以及定义在任何函数外的变量。

*   栈：保存定义在函数内的非 static 对象。

*   动态内存：堆，程序运行时使用。

#### 智能指针

*   shared\_ptr 类

    *   定义方式：使用模板的定义方式，可以指向 string 类型 `shared_ptr p1` 。

    *   使用方式：和普通指针的使用方式类似。

```C++
// 如果 p1 不空，但指向一个空 string，则将一个新值赋予 string
if(p1 != nullptr && p1->empty())
  *p1 = "hi";
```

*   分配方式 make\_shared 函数：此函数在动态内存中分配一个对象并初始化它，返回指向此对象的 shared\_ptr，`shared_ptr p = make_shared(10, '9')`

*   拷贝和赋值：当进行拷贝和赋值时，每个 shared\_ptr 都会记录有多少个其它的 shared\_ptr 指向相同的对象，这称为**引用计数**。当用一个 shared\_ptr 初始化另一个 shared\_ptr 或者将它作为参数传递给一个函数或者作为函数的返回值时，计数器会递增；当给 shared\_ptr 赋予一个新值或者 shared\_ptr 被销毁，计数器会递减，当计数器为 0 时，shared\_ptr 自动销毁所管理的对象，并释放相关内存。

*   unique\_ptr 类

    *   与 shared\_ptr 不同，某个时刻智能有一个 unique\_ptr 指向一个给定对象，当 unique\_ptr 被销毁时，它所指向的对象也被销毁。

    *   定义方式：需要将其绑定到一个 new 返回的指针上，由于其特性，因此不能进行拷贝或赋值，但是可以进行所有权转移。

```C++
unique_ptr<int> p(new int(42));

// release 将 p 置为空，将所有权从 p 转移给 p1
unique_ptr<int> p1(p.release());
unique_ptr<int> p2(new int(100));
// 将所有权从 p1 转移给 p2
p1.reset(p2.release());

```

*   weak\_ptr 类

    *   是一种不控制所指对象生存期的智能指针，指向由 shared\_ptr 管理的对象，但是 shared\_ptr 如果被销毁，weak\_ptr 也会随之销毁（弱）。

    *   可以通过 weak\_ptr 检查指针是否还存在：

```C++
auto p = make_shared<int>(42);
weak_ptr<int> wp(p);  // wp 弱共享 p，p 的引用计数未改变
if(shared_ptr<int> np = wp.lock())
{
  // 如果 np 不为空则成立
  // 在 if 中 np 与 p 共享对象
}
```

#### 直接管理

*   new 动态分配内存

    *   new 会返回一个指向自由空间分配内存的指针，`int *pi = new int` 。

    *   可以使用括号进行初始化 `int *pi= new int(1024)`，也可以使用列表进行初始化 `vector<int> *pv = new vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}` 。

    *   可以实现动态分配的 const 对象，注意动态分配的 const 对象必须进行初始化，`const int *pci = new const int(1024)` 。

    *   内存耗尽：如果 new 不出新的空间就会抛出类型为 bad\_alloc 的异常。

*   delete 释放动态内存

    *   delete 表达式接受一个指针，指针必须指向动态分配的内存或者一个空指针，`delete p` 。

\*\* 由内置指针（而不是智能指针）管理的动态内存在被显式释放前一直都会存在\*\*

#### shared\_ptr 与 new 结合使用

*   可以使用 new 返回的指针来初始化智能指针：

```C++
shared_ptr<int> p(new int(42));

shared_ptr<int> clone(int p)
{
  // 显式地用 int* 创建 shared_ptr<int>
  return shared_ptr<int>(new int(p));
}

// 可以使用 reset 将新的指针赋予一个 shared_ptr
p.reset(new int(1024));
```

*   不能混用普通指针和智能指针：使用内置指针来访问智能指针所负责的对象很危险，因为无法得知对象什么时候会被销毁。

```C++
// 在函数被调用时 ptr 被创建并初始化
void process(sharedd_ptr<int> ptr)
{
  // 使用 ptr
} // ptr 离开作用域，被销毁

int *x(new int(1024));

// 合法的，但是由于前面 x 的定义过程中没有进行引用计数，因此之后会被释放
process(shared_ptr<int>(x));

// 未定义，x 已经被释放
int j = *x;
```

*   get 函数：当我们需要向不能使用智能指针的代码传递一个内置指针时可以使用 get 函数，需要注意使用 get 返回的指针的代码不能 delete 此指针，并且不要用 get 初始化另一个智能指针（get 得到的相当于一个普通指针，不能混用普通指针与智能指针）。

```C++
shared_ptr<int> p(new int(42)); // 引用计数为 1
int *q = p.get();
```

#### 智能指针和异常

*   使用智能指针可以保证即使程序被异常终止，也能确保内存被释放。而直接管理的内存如果在 new 以及 delete 之间发生异常且异常没有在函数中被捕获，则内存永远不会被释放。

```C++
void f1()
{
  shared_ptr<int> sp(new int(42));
  // 抛出一个异常
} // 在函数结束时 shared_ptr 自动释放内存

void f2()
{
  int *ip = new int(42);
  // 抛出一个异常
  delete ip; // 在退出之前释放内存
}
```

*   使用自己的释放操作：可以定义一个删除器，shared\_ptr 在释放的过程中自动调用删除器完成资源的释放。

### 动态数组

#### allocator 类

*   为定义一个 allocator 对象，必须指明其可以分配的对象类型。

```C++
allocator<string> alloc; // 可以分配 string 的 allocator 对象
auto const p = alloc.allocate(n); // 分配 n 个未初始化的 string
```

*   使用 allocator 分配的内存是未构造的，要按照需要在此内存中构造对象。

```C++
auto q = p;// q 指向最后构造的元素之后的位置
alloc.construct(q++, 10, 'c'); // *q 为 cccccccccc
alloc.construct(q++, "hi"); // *q 为 hi
```

*   使用完对象之后需要对每一个构造的元素调用 destory 来销毁。

```C++
while(q != p)
  alloc.destory(--q);
```

*   元素被销毁后可以重新使用这部分内存保存其它的 string，也可以将其归还给系统。

```C++
alloc.dellocate(p, n);
```

*   使用算法拷贝填充未初始化的类：可以在未初始化的内存中创建对象。

```C++
// 分配比 vi 中元素所占空间大一倍的动态内存
auto p = alloc.allocate(vi.size() * 2);
// 通过拷贝 vi 中的元素来构造从 p 开始的元素，返回（递增后的）目的位置迭代器
auto q = uninitialized_copy(vi.begin(), vi.end(), p);
// 将剩余的元素初始化为 42
uninitialized_fill_n(q, vi.size(), 42);
```

### 文本查询程序

*   参见 TextQuery\_class.h 以及 12\_3 text\_query\_program.cpp。

