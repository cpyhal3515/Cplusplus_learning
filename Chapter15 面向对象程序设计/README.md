# Chapter 15 面向对象程序设计

## 说明

> 核心在于**数据抽象**、**继承和动态绑定**。

## 记录笔记

### 基本概念

#### 1、继承

*   通过继承联系在一起的类构成一种层次关系：

    *   **基类**：通常在层次关系的根部的类。

    *   \*\*派生类：\*\*直接或间接地从基类继承而来的其它类。

*   **虚函数**：对于某些函数，基类希望它的派生类各自定义适合自身的版本，此时基类就将这些函数声明成虚函数。

```C++
class Quote
{
  public:
    std::string isbn() const;
    virtual double net_price(std::size_t n) const;
}
```

*   **派生类列表**：派生类需要通过该列表明确指出它是从哪个基类继承而来的。首先一个冒号，后面紧跟以逗号分隔的基类列表。

```C++
// Bulk_quote 继承了 Quote
class Bulk_quote : public Quote
{
  public:
    double net_price(std::size_t) const override;
}
```

#### 2、动态绑定

*   通过动态绑定，我们可以使用同一段代码分别处理 Quote 和 Bulk\_quote 对象：

```C++
double print_total(ostream &os, const Quote &item, size_t n)
{
  // 根据传入 item 形参的对象类型调用 Quote::net_price 或者 Bulk_quote::net_price
  double ret = item.net_price(n);
  return ret;
}

print_total(cout, basic, 20);
print_total(cout, bulk, 20);
```

#### 3、静态类型与动态类型

*   静态类型：在编译时已知的。

*   动态类型：运行时才可知。

#### 4、C++ 的多态性

*   面向对象的**核心思想**是多态性。

*   具有继承关系的多个类型称为多态类型，因为我们能使用这些类型的“多种形式”而无须在意它们的差异。

*   **引用或指针的静态类型与动态类型不同**这一事实是 C++ 支持多态性的根本所在。

### 定义基类和派生类

#### 定义基类

*   关键字`virtual`：对于基类希望派生类进行覆盖的函数，基类通常将其定义为虚函数。当我们使用指针或引用调用函数时，该调用将被动态绑定。根据引用或指向的对象选择实际执行的函数版本。

```C++
class Quote
{
public:
	Quote() = default;
	{
		std::cout << "Quote Default Constructor" << std::endl;
	}
	Quote(const std::string& book, double sales_price) :
		bookNo(book), price(sales_price) { }
	std::string isbn() const { return bookNo; }

	// 返回给定数量的书籍的销售总额
	// 派生类负责改写并使用不同的折扣计算算法
	virtual double net_price(std::size_t n) const
	{
		return n * price;
	}
	// 对析构函数进行动态绑定
	virtual ~Quote()
	{
		std::cout << "Quote Destructor" << std::endl;
	}
	
private:
	std::string bookNo; // 书籍的 ISBN 编号
protected:
	double price = 0.0; // 表示普通状态下不打折的价格
};
```

#### 定义派生类

```C++
// 定义 Bulk_quote 类. Bulk_quote 类继承自 Quote
class Bulk_quote : public Quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string&, double, std::size_t, double);

	// 覆盖基类的函数版本
    double net_price(std::size_t) const override;
private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};
```

### 虚函数

*   当我们使用基类的引用或指针调用一个虚成员函数时会执行动态绑定，因为我们直到运行时才能知道到底使用了哪个版本的虚函数，因此**所有虚函数都要有定义**。

*   `override` ：我们可以使用该关键字来说明派生类中的虚函数，这样可以使程序员的意图更加清晰，同时让编译器帮我们发现一些错误。

```C++
Class B
{
  virtual void f1(int) const;
  void f2();
};

Class D
{
  void f1(int) const override; // 正确：f1 与基类中的 f1 匹配
  void f2() override; // 错误：B 中没有定义 f2 为虚函数
}
```

*   `final` ：被定义的函数，无法在之后尝试任何形式的覆盖操作。

```C++
Class D2 : B
{
  virtual void f1(int) const final;
};

Class D3 : D2
{
  void f1(int) const ; // 错误：D2 已经将 f1 设置为 final
}
```

### 抽象基类

*   **纯虚函数**：和普通的虚函数不一样，一个纯虚函数无需定义。

*   **抽象基类**：\*\*含有（或未经覆盖直接继承）\*\*纯虚函数的类。

\*\*我们不能直接创建一个抽象基类的对象：\*\*例如 `Disc_quote discounted;`就是错误的。

```C++
// 定义 Disc_quote 类. Disc_quote 类继承自 Quote
// 用于保存折扣值和购买量的类，派生类适用这些数据可以实现不同的价格策略
class Disc_quote : public Quote
{
public:
	Disc_quote() = default;
	Disc_quote(const std::string& book, double price, std::size_t qty, double disc) :
		Quote(book, price), quantity(qty), discount(disc) {}
	double net_price(std::size_t) const = 0;
protected:
	std::size_t quantity = 0;	// 折扣适用的购买量
	double discount = 0.0;		// 表示折扣的小数值
};

// 可以使用 Disc_quote 类改写 Bulk_quote 类
// 定义 Bulk_quote 类. Bulk_quote 类继承自 Disc_quote
class Bulk_quote : public Disc_quote
{
public:
	Bulk_quote() = default;
    Bulk_quote(const std::string& book, duble price, std::size_t qty, double disc):
      Disc_quote(book, price, qty, disc) {}
	// 覆盖基类的函数版本以实现基于大量购买的折扣政策
	double net_price(std::size_t) const override;
};
```

### 访问控制与继承

*   受保护的成员：一个类可以使用 `protected` 关键字来声明那些它希望与派生类分享但不想被其它公共访问使用的成员。派生类的成员或者友元只能通过派生类对象来访问基类的受保护的成员，派生类对于一个基类对象中的受保护成员没有任何访问特权。

```C++
class Base
{
  protected:
    int prot_mem; 
};

class Sneaky : public Base 
{
  friend void clobber(Sneaky&); // 能访问 Sneaky::prot_mem
  friend void clobber(Base&);   // 不能访问 Base::prot_mem
}

// 正确：能访问 Sneaky 对象的 protected 成员
void clobber(Sneaky &s)
{
  s.prot_mem = 0;
}
// 错误：不能访问 Base 对象的 protected 成员
void clobber(Base &b)
{
  b.prot_mem = 0;
}
```

*   公有、私有以及受保护的继承：某个类对于继承而来的成员的访问权限受到两个因素影响，一是在基类中该成员的访问说明符；二是在派生类的派生列表中的访问说明符。派生访问说明符的目的是控制派生类用户（包括派生类的派生类在内）对于基类成员的访问权限：

```C++
class Base
{
    public:
        void pub_mem();
    protected:
        int prot_mem;
    private:
        char priv_mem;
};
struct Pub_Derv : public Base{
    // 正确：派生类能访问 protected 成员
    int f() {return prot_mem;}
};
struct Priv_Derv : private Base{
    // 正确：private 不影响派生类的访问权限
    int f1() {return prot_mem;}
};

Priv_Derv d2;
d2.pub_mem(); // 错误：pub_mem 在派生类中是 private 的
```

### 继承类中的类作用域

> 当存在继承关系时，派生类的作用域嵌套在其基类的作用域之内。如果一个名字在派生类的作用域内无法正确解析，则编译器将继续在外层的基类作用域中寻找该名字的定义。（实际上就是通过嵌套进行递归的查找）。

*   查找首先按照名字，当名字找到之后还需要根据实参进行匹配。

*   覆盖重载函数：

    *   派生类如果希望所有的重载版本对于它来说都是可见的，那么它就需要覆盖所有的版本，或者一个也不覆盖。

    *   `using` 关键字：using 声明语句指定一个名字而不指定形参列表，因此一条基类成员函数的 using 声明语句就可以把该函数的所有重载实例添加到派生类作用域中。

### 构造函数与拷贝控制

*   虚析构函数：基类通常应该定义一个虚析构函数，这样就能确保当我们 `delete` 基类指针时可以运行正确的析构函数版本。如果基类的析构函数不是虚函数，则 delete 一个指向派生类对象的基类指针将产生未定义的行为。

```C++
class Quote
{
  public:
    // 如果我们删除的是一个指向派生类对象的基类指针，则需要虚析构函数
    virtual ~Quote() = default;
}

Quote *itemP = new Quote;
delete itemP; // 调用 Quote 的析构函数
itemP = new Bulk_quote;
delete itemP; // 调用 Bulk_quote 的析构函数
```

*   合成拷贝控制与继承：

    *   如果当前类删除了拷贝构造函数，则继承该类的类也无法定义拷贝构造函数了。

    *   当一个基类定义一个虚析构函数后，在默认情况下，基类通常不含有合成的移动操作，因此它在派生类中也就没有合成的移动操作了，所以当我们确实需要移动操作时，需要在基类中先定义。

*   派生类的拷贝控制成员：

    *   定义派生类的拷贝或移动构造函数：通常使用对应的基类构造函数初始化对象的基类部分。

    *   派生类赋值运算符：必须显式的为其基类部分赋值。

    *   派生类的析构函数：派生类析构函数只负责销毁由派生类自己分配的资源。

```C++
Class Base {};
class D: public Base
{
  public:
    D(const D& d): Base(d) // 拷贝基类成员
        /* D的成员的初始值 */ {}
    D(D&& d): Base(std::move(d)) // 移动基类成员
         /* D的成员的初始值 */ {}
}


// B::operator=(const Base&) 不会被自动调用
D &D::operator=(const D &rhs)
{
  Base::operator=(rhs); // 为基类部分赋值
  // 按照过去的方式处理派生类自己1的情况
  return *this;
}

class D: public Base
{
  public:
      // Base::~Base 被自动调用执行
      ~D() {/* 该处用户定义清除派生类成员的操作*/}
}
```

*   继承的构造函数

    *   类不能继承默认、拷贝和移动构造函数。如果派生类没有直接定义这些构造函数，则编译器直接为派生类合成它们。

    *   可以使用 using 语句使得对于基类的每个构造函数，编译器在派生类中生成可以生成一个形参列表完全相同的构造函数。

    *   一个构造函数的 using 声明不会改变该构造函数的访问级别。例如，不管 using 声明出现在哪里，基类的私有构造函数在派生类中还是一个私有的构造函数。

```C++
// 定义 Bulk_quote 类. Bulk_quote 类继承自 Disc_quote
class Bulk_quote : public Disc_quote
{
public:
    // 继承 Disc_quote 的构造函数
	using Disc_quote::Disc_quote;
	// 覆盖基类的函数版本以实现基于大量购买的折扣政策
	double net_price(std::size_t) const override;

};
```

### 容器与继承

*   因为不允许在容器中保存不同类型的元素，所以我们不能把具有继承关系的多种类型的对象直接存放在容器当中，而是应该采用指针（智能指针）的方式间接存储。

```C++
vector<shared_ptr<Quote>> basket;
basket.push_back(make_shared<Quote>("0-201-54848-8", 50));
basket.push_back(make_shared<Bulk_quote>("1-201-54848-8", 50, 10, 0.85));
```

*   可以查看 Basket 类的定义。





