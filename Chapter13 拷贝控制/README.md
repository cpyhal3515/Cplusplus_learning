# Chapter 13 拷贝控制

## 说明

> 拷贝控制就是定义对象拷贝、移动、赋值或销毁时做什么。

## 记录笔记

### 拷贝控制操作

*   一个类通过定义五种特殊的成员函数来控制对象拷贝、移动、赋值和销毁时做什么：

    *   拷贝构造函数

    *   拷贝赋值运算符

    *   移动构造函数

    *   移动赋值运算符

    *   析构函数

#### 拷贝构造函数

*   构造函数的第一个参数是自身类类型的引用，且任何额外参数都有默认值，则此构造函数是拷贝构造函数，第一个参数必须是引用类型，一般声明为 `const` 。

```C++
class Foo {
public:
  // 默认构造函数
  Foo(); 
  // 拷贝构造函数
  Foo(const Foo&);
}
```

*   \*\*合成拷贝构造函数：\*\*如果没有为类定义拷贝构造函数，编译器会为我们定义一个。合成的函数会将类的参数成员（非 static 的）逐个拷贝到正在创建的对象中，如果遇到要拷贝的元素也是一个对象，则会自动调用该对象的拷贝构造函数。

*   \*\*拷贝初始化：\*\*拷贝初始化会在如下四种情况中发生，有的时候会调用移动构造函数而不是拷贝构造函数。

    *   用 \= 定义变量时：`string nines = string(100, '9');` 。

    *   将对象作为实参传递给一个非引用类型的形参

    *   从一个返回类型为非引用类型的函数返回一个对象

    *   列表初始化一个数组中元素

#### 拷贝赋值运算符

*   重载赋值运算符：本质是函数，赋值运算符就是一个名为 `operator=` 的函数，需要定义为类的成员函数，其左侧运算对象就绑定到隐式的 `this` 参数，对于赋值这个二元运算符，右侧运算对象作为显式参数传递。

```C++
class Foo {
public:
  Foo& operator=(const Foo&); // 赋值运算符
}
```

*   \*\*合成拷贝运算符：\*\*如果没有为类定义拷贝运算符，编译器会为我们定义一个。合成的拷贝运算符会将右侧运算对象的每个非 static 成员通过各成员的拷贝赋值运算符赋予左侧运算对象的对应成员。

#### 移动构造函数

*   **右值引用**：可以通过 `&&` 而不是 `&` 来获得右值引用，左值持久，右值短暂（只能绑定到一个将要销毁的对象）。

```C++
int i = 42;
int &r = i;
int &&rr = i * 42;
```

*   **标准库 move 函数**：可以使用该函数来获得绑定到左值上的右值引用，`int &&rr3 = std::move(rr1);` 。调用 move 就意味着除了对 rr1 赋值或销毁外，我们将不再使用它。

*   **移动迭代器**：移动迭代器的解引用运算符可以生成一个右值引用，可以调用 `makee_move_iterator` 函数将一个普通迭代器转换为一个移动迭代器：

```C++
void StrVec::reallocate()
{
	// 分配当前大小两倍的空间
	auto new_cap = (size() == 0) ? 1 : 2 * size();
	// 分配新内存
	auto first = alloc.allocate(new_cap);
	// 将数据从旧内存移向新内存
	auto last = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), first);

	// 释放旧内存空间
	free();
	// 更新元素
	elements = first;
	first_free = last;
	cap = elements + new_cap;
}
```

*   移动构造函数：引用参数应该是一个右值引用，并且需要确保移动后的源对象处于一个销毁无害的状态，因为有时候在移动操作完成之后，源对象会被销毁。

```C++
StrVec::StrVec(StrVec&& orig) noexcept // 移动操作不应该抛出任何异常
	// 成员初始化器接管 orig 中的资源
	: elements(orig.elements), first_free(orig.first_free), cap(orig.cap)
{
	// 令 orig 进入可以析构的状态
	orig.elements = orig.first_free = orig.cap = nullptr;

}
```

#### 移动赋值运算符

```C++
StrVec& StrVec::operator=(StrVec&& rhs) noexcept
{
	// 检测自赋值
	if (this != &rhs)
	{
		// 释放已有元素
		free();
		// 从 rhs 接管资源
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		// 将 rhs 置于可析构的状态
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	
	return *this;
}
```

#### 析构函数

*   析构函数释放对象使用的资源，并销毁对象的非 static 数据成员。首先执行函数体，然后按照初始化顺序的逆序销毁成员。销毁类类型的成员需要执行成员自己的析构函数。

```C++
class Foo {
public:
  ~Foo(); // 析构函数
}
```

**析构函数自身并不直接销毁成员，成员是在析构函数体之后隐含的析构阶段中被销毁的。**

*   **析构函数的调用：对象被销毁时。**

    *   变量离开其作用域时。

    *   对象被销毁时，其成员会被析构。

    *   容器被销毁时，其元素被销毁。

    *   动态分配的对象只有在指向它的指针应用 delete 运算符时才会被销毁。

> 需要析构函数的类也需要拷贝和赋值操作。\
> 需要拷贝操作的类也需要赋值操作，反之亦然。

#### 使用 default

*   可以通过将拷贝控制成员定义为 \=default 来显式地要求编译器生成合成的版本。

```C++
class Sales_data {
public:
  // 拷贝控制成员：使用 default
  Sales_data() = default;
  Sales_data(const Sales_data&) = default;
  Sales_data& operator=(const Sales_data &);
  ~Sales_data() = default;

};
Sales_data& Sales_data::operator=(const Sales_data&) = default;
```

#### 阻止拷贝

*   对于某些类来说，拷贝是没有意义的，需要使用 \=default 阻止。比如 iostream 类为了避免多个对象写入或读取相同的 IO 缓冲，会阻止拷贝。

```C++
struct NoCopy {
  NoCopy() = default;// 使用合成的默认构造函数
  NoCopy(const NoCopy&) = delete;// 阻止拷贝
  NoCopy &operator=(const NoCopy&) = delete;// 阻止赋值
}
```

**析构函数不能是删除的成员**，要不然就无法销毁此类型的对象了。

### 拷贝控制和资源管理

*   在定义类成员之前必须确定此类型对象的拷贝语义，一般来说可以定义拷贝操作，使类的行为看起来像一个值或者像一个指针。

#### 行为像值的类

*   每个对象都拥有一份自己的拷贝，下面以 HasPtr 作为示例，每个 HasPtr 对象都必须有自己的拷贝：

```C++
class HasPtr {
public:
  HasPtr(const std::string &s = std::string()):
    ps(new std::string(s)), i(0) {}
  // 对 ps 指向的 string，每个 HasPtr 对象都有自己的拷贝
  HasPtr(const HasPtr &p) :
    ps(new std::string(*p.ps)), i(p.i) {}
  HasPtr& operator=(const HasPtr &);
  ~HasPtr() {delete ps;}
private:
  std::string *ps;
  int i;
};
```

*   类值拷贝赋值运算符

```C++
HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
  auto newp = new string(*rhs.ps); // 拷贝底层 string
  delete ps; // 释放旧内存
  ps = newp; // 从右侧运算对象拷贝数据到本对象
  i = rhs.i;
  return *this; // 返回本对象
}
```

#### 行为像指针的类

*   需要为其定义拷贝构造函数和拷贝赋值运算符，来拷贝指针成员本身，同时，析构函数不能单方面地释放关联的 string，只有当最后一个指向 string 的 HasPtr 销毁时，它可以释放 string，需要使用**引用计数**的方式：

```C++
class HasPtr
{
public:
	// 构造函数
	HasPtr(const std::string &s = std::string()): 
		ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
	// 拷贝构造函数
	HasPtr(const HasPtr& orig) : 
		ps(new std::string(*orig.ps)), i(orig.i), use(orig.use) 
	{
		// 增加引用计数
		++*use;
	}
	// 拷贝赋值运算符
	HasPtr& operator=(const HasPtr&);
	// 析构函数
	~HasPtr() {}
private:
	std::string* ps;
	int i;
	// use 用来表示引用计数的值
	std::size_t* use;
};

// 拷贝赋值运算符
HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
	// 递增右侧对象的引用计数值
	++*rhs.use;
	// 递减本对象的引用计数值，若没有其余用户引用本对象，则释放本对象
	if (--*use == 0)
	{
		delete ps;
		delete use;
	}
	// 将数据从 rhs 拷贝到本对象
	ps = rhs.ps;
	i = rhs.i;
	use = rhs.use;
	return *this;
}

// 拷贝赋值运算符
HasPtr::~HasPtr()
{
	// 如果引用计数变为 0 
	if (--*use == 0)
	{
		// 释放 string 内存
		delete ps;
		// 释放计数器内存
		delete use;
	}
}
```

### 交换操作

*   管理资源的类通常还会定义一个名为 swap 的函数，对于与那些重排元素顺序的算法一起使用的类，定义 swap 很重要：

```C++
class HasPtr {
  friend void swap(HasPtr&, HasPtr&);
}
inline
void swap(HasPtr &lhs, HasPtr &rhs)
{
  // swap 函数中调用的是 swap 函数，而不是 std::swap 函数
  // 因为一个类成员可以有自己类型特定的 swap 函数
  using std::swap;
  swap(lhs.ps, rhs.ps); // 交换指针，而不是 string 数据
  swap(lhs.i, rhs.i);  // 交换 int 成员
}
```

*   拷贝交换技术：定义 swap 的类用 swap 来定义它们的赋值运算符，将左侧对象与右侧对象的副本进行交换：

```C++
// rhs 按值传递的，意味 HasPtr 的拷贝构造函数
// 将右侧运算对象中的 string 拷贝到 rhs
HasPtr& HasPtr::operator=(HasPtr rhs)
{
  // 交换左侧运算对象和局部变量 rhs 的内容
  swap(*this, rhs); // rhs 现在指向本对象曾经使用的内存
  return *this; // rhs 被销毁，从而 delete 了 rhs 中的指针
}
```

### vector\<string> 类以及 String 类的实现

*   vector\<string> ：参考 StrVecClass.h 以及 StrVecClass.cpp。

*   String：参考 StringClass.h 以及 StringClass.cpp。

