# Chapter 16 模板与泛型编程

## 说明

> 模板就是将实际的参数类型与数据结构进行解耦，这里只记录的最基础的部分，剩下比较细节的部分暂时也没太看。

## 记录笔记

### 定义模板

#### 1、函数模板

*   一个函数模板就是一个公式，可用来生成针对特定类型的函数版本。

```C++
template<typename T>
int compare(const T &v1, const T &v2)
{
  if(v1 < v2) return -1;
  if(v2 < v1) return 1;
  return 0;
}
```

模板定义以关键字 `template` 开始，后跟一个**模板参数列表**，列表中是以逗号分割的一个或多个**模板参数**。当使用模板时，我们（隐式或显式地）指定**模板实参**，将其绑定到模板参数上。

在 `compare` 中，我们用名字 T 来表示一个类型，而 T 的实际类型则在编译时根据 compare 的使用情况来确定。

*   **实例化函数模板**：当我们调用一个函数模板时，编译器用函数实参来为我们推断模板实参，专业点来说就是编译器用推断出的模板参数来为我们**实例化**一个特定版本的函数。

```C++
cout << compare(1, 0) << endl; // T 为 int
```

*   **模板类型参数**：在上面的例子中，模板类型参数是 T，一般来说，我们可以将类型参数看作类型说明符，就像内置类型或类类型说明符一样使用。

```C++
template<typename T>T foo(T* p)
{
  T tmp = *p; // tmp 的类型与 p 指针指向的类型相同
  // ...
  return tmp;
}
```

*   **非类型模板参数**：表示一个值而非类型，注意这些值必须是常量表达式，从而允许编译器在编译时实例化模板。

```C++
template<unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M])
{
   return strcmp(p1, p2); 
}
```

*   **模板编译**：当编译器遇到一个模板定义时，它并不生成代码。只有当我们实例化出模板的一个特定版本时，编译器才会生成代码。当调用一个函数时，编译器只需要掌握函数的声明，因此可以将函数声明放在头文件，函数定义放在源文件中。模板不同，为了生成一个实例化版本，编译器需要掌握函数模板或类模板成员函数的定义，因此模板的头文件既需要包括声明，也包括定义。

#### 2、类模板

*   与函数模板的不同之处在于，编译器不能为类模板推断模板参数类型。因此，为了使用类模板，我们必须在模板名后的尖括号中提供额外信息。

*   **类模板的定义**：类似函数模板，类模板以关键字 `template` 开始，后跟模板参数列表。

```C++
template <typename T> class Blob
{
  ...
  T& back();
}
```

*   **实例化类模板**：当使用一个类模板时，必须提供显示模板实参列表，它们被绑定到模板参数。例如为了用我们的 Blob 模板定义一个类型，必须提供元素类型 `Blob<int> ia;` ，`Blob<string> names;` 。

*   **类模板的成员函数**：类模板的成员函数既可以定义在类内，也可以定义在类外，定义在类模板之外的成员函数必须以关键字 `template` 开始，后接模板参数列表。

```C++
template<typename T>
T& Blob<T>::back()
{
  return data->back();
}
```

*   **类模板和友元**：最常见的类模板与另一个模板间友好关系的形式是建立对应实例及其友元的友好关系。为了引用模板的一个特定实例，我们必须首先声明模板自身。

```C++
// Blob 的友元定义中需要用到
template <typename> class BlobPtr;
// operator== 的定义中需要用到
template <typename> class Blob;

template <typename T> bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T>
class Blob 
{
    // Blob 以及 BlobPtr 对应的实例化结果应该是相同的类型
    friend class BlobPtr<T>;

    friend bool operator==<T>
        (const Blob<T>&, const Blob<T>&);
    ...
}
```

#### 3、模板参数

*   模板参数的名字没有什么内在含义，一般情况下，我们将类型参数命名为 T，但是实际上我们可以使用任何名字。

*   **模板参数与作用域**：模板参数的作用域与普通的作用域的规则相同。

*   **使用类的类型成员**：C++ 假定通过 `::` 运算符访问的是名字而不是类型（静态变量中会用到），如果我们希望使用一个模板类型参数的类型成员，就必须显式告诉编译器该名字是一个类型，可以通过 `typename` 来实现这一点：

```C++
template <typename T>
typename T::value_type top(const T& c)
{
  if(!c.empty())
    return c.back();
  else
    return typename T::value_type();
}
```

### 模板实参推断

#### 1、类型转换与模板类型参数

*   **模板实参推断**：编译器利用调用中的函数实参来确定其模板参数，从函数实参来确定模板实参的过程。

*   **类型转换**：编译器通常不是对实参进行类型转换，而是生成一个新的模板实参。例如 `fcn(T, T)` 就不能实例化成 `fcn(float, double)` ，如果希望实例化两个不同类型，需要将函数模板定义为两个类型参数

```C++
template <typename A, typename B>
int fcn(const A& v1, const B& v2)
{
  ...
}
```

#### 2、函数模板显式实参

*   ** 指定显式模板实参**：在下面的例子中，可以定义表示返回类型的第三个模板参数，从而允许用户控制返回类型。

```C++
// 编译器无法推断 T1，它未出现在函数参数列表中
template <typename T1, typename T2, typename T3>
T1 sum(T2, T3);
```

在本例中，没有任何函数实参类型可用来推断 T1 的类型，每次调用 sum 时的调用者都必须为 T1 提供一个显示模板实参。

```C++
// T1 是显式指定的，T2和T3是从函数实参类型推断而来的
auto val3 = sum<long long>(i, lng);  // long long sum(int, long)
```

#### 3、尾置返回类型

*   虽然可以让用户使用显式模板实参来定义返回值类型，但有时候这样很麻烦，而且没有必要，使用尾置返回类型自动推断则可以节省用户很多精力。

```C++
// 尾置返回允许我们在参数列表之后声明返回类型
template <typename It>
auto fcn(It beg, It end) -> decltyp(*beg)
{
  //处理
  return *beg;// 返回其中一个元素的引用
}
```

#### 4、理解 std::move

*   可以使用 `move` 获得一个绑定到左值上的右值引用，标准库的定义如下：

```C++
//在返回类型和类型转换中也要用到 typename
// remove_reference 脱去引用，剩下元素类型本身
// static_cast 实现强制类型转换
template <typename T>
typename remove_reference<T>::type&& move(T&& t)
{
  return static_cast<typename remove_reference<T>::type&&>(t);
}
```

*   一个小知识点：引用折叠，`X& &、X& &&、X&& &` 都折叠成类型 `X&` ，类型 `X&& &&` 折叠成 `X&&` 。

*   move 的函数参数 `T&&` 是一个指向模板类型参数的右值引用，通过引用折叠，这个参数可以与任何类型的实参匹配。

```C++
string s1("hi!"), s2;
s2 = std::move(string("bye")); // 正确：从一个右值移动数据
s2 = std::move(s1); // 正确：但在赋值后，s1 的值不确定
```

*   **第一个赋值的 move 流程**：传给 move 的实参是 string 构造函数的右值结果。

    *   推断出 T 的类型为 string，再结合 remove\_reference 得到其对应的 type 也是 string。

    *   move 的返回类型是 string&&

    *   再结合 t 的类型 &&，通过折叠最终返回 string&&

    *   这个函数最终的例化结果为：`string&& move(string &&t)`

*   **第二个赋值的 move 流程**：传给 move 的实参一个左值。

    *   推断出 T 的类型为 string&，再结合 remove\_reference 得到其对应的 type 是 string。

    *   move 的返回类型是 string&&

    *   再结合 t 的类型 &，通过折叠最终返回 string&

    *   这个函数最终的例化结果为：`string&& move(string &t)`

























