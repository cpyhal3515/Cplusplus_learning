# Chapter 11 关联容器

## 说明

> 关联容器核心由 map 以及 set 组成，通过键/值进行处理。

## 记录笔记

### 概述

#### 关联容器概述

- 关联容器的核心是 `map` 以及 `set` ，可以通过在前面增加 `multi` 以及 `unordered` 转换成关键字可重复出现的或者无序的关联容器。

#### 定义

- 定义 `map` 时需要既指明关键字类型又指明值类型，定义 `set` 时只需要指明关键字类型。初始化可以采用列表的方式。

```C++
set<string> exclude = {"the", "but", "and", "or", "an", "a"};
map<string, string> authors = {{"Joyce", "James"}, {"Austen", "Jane"}, {"Dickens", "Charles"}};
```

#### 关键字类型

- 对于有序容器，map、multimap、set 以及 multiset，关键字类型必须定义元素比较的方法。

- 因此为指定使用自定义的操作，必须在定义关联容器类型时定义元素比较的方法：

```C++
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
  return lhs.isbn() < rhs.isbn();
}

// bookstore 中多条记录可以有相同的 ISBN
// bookstore 中的元素以 ISBN 的顺序进行排列
multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn);
```

#### pair 类型

- 保存两个数据成员，可以通过 first 以及 second 分别访问两个成员，可以通过列表进行初始化。

```C++
pair<string, string> word_list = {"Hello", "World"};

word_list.first
word_list.second
```

### 关联容器的操作

#### 迭代器

- map 的迭代器是一个 pair 类型的。

```C++
auto map_it = word_count.begin();
map_it->first
map_it->second
```

- set 的迭代器是一个 const 类型的，只能读取不能修改。

```C++
auto set_it = iset.begin();
*set_it
```

- 无法对关联容器直接使用泛型算法（除了 find），因此一般将关联容器当做源序列或者目的位置进行调用，也可以使用 copy 先进行拷贝，再对拷贝后的序列进行泛型算法的处理。

```C++
// c 是一个 string 类型的 multiset
// v 是一个 string 类型的 vector
copy(c.begin(), c.end(), back_inserter(v));
```

#### 添加元素

- 可以使用 `insert` ，set 可以直接按照列表插入，map 需要按照 pair 的格式插入。

```C++
set<int> set2;
set2.insert({1,3,5,7,1,3,5,7});

map<string, int> word_count;
word_count.insert({word, 1});
```

- 检测 insert 的返回值：返回一个 pair 类型，其中 first 成员是一个迭代器，指向具有关键字的元素，second 成员是一个 bool 值，指出元素是插入成功还是已经在容器中了。

```C++
auto ret = word_count.insert({word, 1});
if(!ret.second)
  ++ret.first->second;
```

#### map 下标操作

- c\[k]：返回关键字为 k 的元素，如果 k 不在 c 中，添加一个关键字为 k 的元素，对其值进行初始化。

```C++
++word_count["Anna"];
```

#### map 访问元素

- `c.find(k)` ：返回迭代器指向第一个关键字为 k 的元素，没有就返回尾后迭代器。

- `c.count(k)` ：返回关键字等于 k 的元素的数量。

> 我们只想知道一个给定关键字是否在 map 中，而不想改变 map 就不要用下标运算符，而要用 find

- 对于 `multimap` 以及 `multiset` 中的多个元素，这些元素在容器中会被相邻存储，可以通过 `lower_bound` 以及 `upper_bound` 确定迭代器的上下限进行值的访问。

### 无序容器

- 无序容器不是使用比较运算符来组织元素，而是使用了一个哈希函数和关键字类型的 \=\= 运算符。
