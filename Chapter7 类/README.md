# Chapter 7 函数

## 说明

> 由于之前学习过 C 语言和一部分 C++ 的内容，因此这里主要把一些之前不太熟悉的部分记录下来，这里感觉叫 C2C++ 比较好

## 记录笔记

### 类的基本概念

*   类的基本思想：类主要完成数据抽象与封装功能。

    *   数据抽象：接口 + 数据成员。

    *   封装：隐藏实现细节，用户只能使用接口而无法访问实现部分。确保类内部的数据成员的安全，并且被封装的类的具体实现细节可以随时改变，保证接口不变就无需调整用户级别的代码。

*   抽象数据类型

    ```C++
    // 定义 Sales_data 类
    class Sales_data
    {
    public:
      // 类的公有函数操作
      std::string isbn() const { return bookNo; };
      Sales_data& combine(const Sales_data&);
    private:
      // 类的私有函数操作
      double avg_price() const
      {
        return (units_sold > 0) ? revenue / units_sold : 0 ;
      }
      // 类的私有数据
      std::string bookNo;
      unsigned units_sold = 0;
      double revenue = 0.0;
    };
    ```

    上面的代码完成了一个简单的类，并实现了数据抽象以及封装，一方面定义了私有的数据和内部函数，另一方面定义了类与外部交互的公有函数作为接口。

*   `class` 与 `struct` 的区别：`class` 与 `struct` 只有默认访问权限不一样，剩下都完全相同，可以互相替换，`struct` 的默认访问权限是 public 的，而 `class` 的默认访问权限是 private 的。

*   `private` 与 `public`

    *   `private`：只能被类的成员函数访问。

    *   `public`：成员可以在整个程序内被访问，主要用来定义接口。

### 类的特性

#### 类的成员

*   定义类型成员：必须先定义后使用，因此类型成员要定义**在类开始的地方**。

    ```C++
    class Screen
    {	
    public:
      // 声明类型别名
      using pos = std::string::size_type;
    private:
    };
    ```

*   定义成员函数的内联特性：定义在类内部的成员是自动 `inline`，对于定义在类外部的成员，最好只在类外部定义的地方说明 `inline` 特性。

    ```C++
    class Screen
    {	
    public:
      using pos = std::string::size_type;
      // 隐式内联
      char get() const
      {
        return contents[cursor];
      }

      Screen& move(pos, pos);
    private:
      pos cursor = 0;
    };
    // 在类外部定义为显式内联
    inline
    Screen& Screen::move(pos r, pos c)
    {
      ...
    }
    ```

*   成员函数的重载特性：与普通函数的重载特性是一样的，例如在下面的代码中就重载了 `get` 成员函数。

    ```C++
    Screen myscreen;
    char ch = myscreen.get();
    ch = myscreen.get(0, 0);
    ```

#### 返回 \*this 的成员函数

*   `this` 总指向“这个”对象。在成员函数内部可以直接调用该函数的对象的成员，因为 `this` 所指的正是这个对象，任何对类成员的访问都被看做 `this` 的隐式引用，在对象外部可以定义返回 `this` 对象的函数。

*   通过返回 `this` 可以使用连续调用：对于下面的类的定义可以使用 `myScreen.move(4, 0).set('#')` 进行连续调用。

    ```C++
    class Screen
    {	
    public:
      using pos = std::string::size_type;
      Screen& set(char);
      Screen& move(pos, pos);
    private:
    };
    // 定义普通的类返回 
    Screen& Screen::set(char ch);
    {
      return *this;
    }
    // 定义普通的类返回
    Screen& Screen::move(pos r, pos c)
    {
      ...
      return *this;
    }
    ```

需要注意的是上面连续调用的类中的返回值应当是普通的引用类型，对于常量引用类型会产生报错。一般处理常量引用类型的方法如下，函数重载会自动决定具体要重载到哪种类型的 `display`：

```C++
class Screen
{
public:
  // 根据对象是否是 const 重载了 display 函数
  Screen &display(std::ostream &os)
  {
    ...
    return *this;
  }
  const Screen &display(std::ostream &os) const
  {
    ...
    return *this;
  }
private:
  // 该函数负责实现 display 的功能
  void do_display(std::ostream &os) const
  {
    ...
  }
}
```

#### 类的声明与定义

*   类的定义：将一个类的具体内容完整的定义出来。

    ```C++
    class Screen
    {	
    public:
      ...
    private:
      ...
    };
    ```

*   类的声明：与类的定义可以分离开。但是只有完成类的定义，编译器才能知道存储该数据成员所需的空间，因此只有当类全部完成后类才算被定义，所以一个类的成员类型不能是该类自己，但是**可以是指向它自身类型的引用或指针**：

    ```C++
    class Link_screen
    {
      Screen window;
      Link_screen *next;
      Link_screen *prev;
    };
    ```

#### 友元

*   类之间的友元关系：一个类指定了友元类后，友元类的成员函数可以访问此类中的所有成员。

    ```C++
    class Screen
    {
      // Window_mgr 的成员可以直接访问 Screen 类的私有部分
      friend class Window_mgr;
      ...
    }

    ```

*   成员函数作为友元：只为某个函数提供访问权限，当把一个成员函数声明成友元时，我们必须明确指出该成员函数属于哪个类。

    ```C++
    class Screen
    {
      // Window_mgr::clear 必须在 Screen 类之前被声明
      friend void Window_mgr::clear(ScreenIndex);
      ...
    }
    ```

*   友元关系不可以被传导，即如果 A 是 B 的友元，B 是 C 的友元，但是 A 不一定是 C 的友元。

*   函数重载与友元：重载函数在友元这个概念下是不同的函数，如果一个类想把一组重载函数声明成它的友元，它需要对这组函数中的每一个分别声明。

*   友元声明与作用域：友元声明仅是影响访问权限，它本身并非普通意义上的声明。因此在调用该友元函数前必须保证它是被声明过的。

    ```C++
    class X
    {
      friend void f()
      {
        // 友元函数可以定义在类的内部
        ...
      }
      // 错误：f 还没有被声明
      X() { f(); }
      void g();
      void h();
    };

    void X::g() {return f();} // 错误：f 还没有被声明
    void f();
    void X::h() {return f();} // 正确：f 已经被声明过了
    ```

### 类的作用域

*   一旦遇到类名，定义的剩余部分就在类的作用域之内了（包括参数列表和函数体），因此类中的其它成员均可以直接使用。

    ```C++
    // 因为有 Window_mgr 因此
    // 不需要再专门说明 ScreenIndex 是 Window_mgr 类定义的
    void Window_mgr::clear(ScreenIndex i)
    {

    }
    ```

*   要想理解类的作用域，首先要明白类的定义的流程。类的定义分两步：

    *   首先，编译成员的声明。

    *   直到类全部可见后才编译函数体。

*   用于类成员声明的名字查找

    ```C++
    typedef double Money;
    string bal;
    class Account
    {
    public:
      Money balance() {return bal;}
    private:
      Money bal;
    }
    ```

在这个例子中，编译器会找到 Money 的 typedef 语句，该类型被用作 balance 函数的返回类型以及数据成员 bal 的类型。另一方面，balance 函数体在整个类可见后才被处理，因此该函数 return 返回 bal 成员，而不是外层作用域的 string 对象。

### 构造函数

```C++
// 定义 Sales_data 类
class Sales_data
{
public:
	// 默认构造函数
  Sales_data() = default;
  // 花括号定义了函数体
  // 冒号与花括号之间的部分是构造函数初始值列表
  Sales_data(const std::string &s) : bookNo(s) {}
  Sales_data(const std::string &s, unsigned n, double p) :
    bookNo(s), units_sold(n), revenue(p*n) {}
  // 在类的外部定义构造函数
  Sales_data(std::istream &);
	
	
private:
  ...

};
// 在类的外部定义构造函数
Sales_data::Sales_data(std::istream &is)
{
  // read 函数从 is 中读取一条交易信息然后存入 this 对象中
  read(is, *this);
}
```

#### 构造函数的初始化列表

*   成员初始化的顺序：成员初始化顺序与它们在类定义中的出现顺序一致。

    ```C++
    class X
    {
      int i;
      int j;
    public:
      // 未定义的：i 在 j 之前被初始化 
      X(int val) : j(val), i(j) {}
    };
    ```

*   默认实参：例如可以将一开始的代码变为 `Sales_data(std::string s = ""): bookNo(s) {} `，该函数的行为与只接受一个 string 实参的构造函数差不多。

#### 委托构造函数

*   委托构造函数使用它所属类的其它构造函数执行它自己的初始化过程。当一个构造函数委托给另一个构造函数时，受委托的构造函数的初始值列表和函数体被依次执行。

    ```C++
    // 定义 Sales_data 类
    class Sales_data
    {
    public:
      // 构造函数：完成类的初始化操作
      Sales_data(const std::string& s, unsigned n, double p) :
        bookNo(s), units_sold(n), revenue(p* n) {};
      // 委托构造函数：将实际的构造任务交给构造函数完成
      Sales_data() : Sales_data(" ", 0, 0) {};
      Sales_data(const std::string& s) : Sales_data(s, 0, 0) {};
      Sales_data(std::istream& is) :Sales_data() { read(is *this); };
    private:
      ...

    };
    ```

#### 隐式的类类型转换

*   如果构造函数只接受一个实参，则它可以由普通实参对应的数据类型转换成类的类型。

    ```C++
    string null_book = "9-999-99999-9";
    // 构造一个临时的 Sales_data 对象
    // 该对象的 units_sold 和 revenue 等于 0， bookNo 等于 null_book
    item.combine(null_book);
    ```

*   注意，这个转换只允许一步，例如下面这个就是不对的：

    ```C++
    // 下面这个代码需要两步转换：
    // (1) 把 "9-999-99999-9" 转换成 string
    // (2) 把 string 转换成 Sales_data
    item.combine("9-999-99999-9");
    ```

*   可以通过 `explicit` 抑制构造函数定义的隐式转换。

### 类的静态成员

*   我们可以使用 static 关键字来把类成员定义为静态的。当我们声明类的成员为静态时，这意味着无论创建多少个类的对象，静态成员都只有一个副本。这样可以保证**成员变量与类关联，而不是与类的每个对象关联**。

*   声明：需要使用 `static` 关键字。

    ```C++
    class Account
    {
    public:
      void calculate() { amount += amount * interestRate; };
      // 静态成员变量
      static double rate() { return interestRate; };
      static void rate(double);

    private:
      std::string owner;
      double amount;
      static double interestRate;
      static double initRate();

      // 类内字面值常量静态成员
      static constexpr int period = 30;
      double daily_tbl[period];
    };

    void Account::rate(double newRate)
    {
      interestRate = newRate;
    }

    double Account::initRate()
    {
      interestRate = 1.5;
    }
    ```

*   定义：因为静态数据成员不属于类的任何一个对象，所以它们**并不是在创建类的对象时被定义的**，这意味着它们不是由类的构造函数初始化的。一般情况下，需要在类的外部定义和初始化静态成员，但是也可以使用 `constexpr` 关键字在类内初始化。

*   使用：可以使用作用域运算符 `r = Account::rate();` 或者类的对象的方式 `r = ac1.rate();` 直接访问静态成员。

### 拷贝、赋值与析构

*   13 章中会详细说明。

