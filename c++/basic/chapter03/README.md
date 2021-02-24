# 第三章 字符串、向量和数组


## 目录
* [命名空间的using声明](#命名空间的using声明)
    - [namespace](#namespace)
        - [命名空间的定义](#命名空间的定义)
        - [命名空间的使用](#命名空间的使用)
    - [using声明](#using声明)
* [标准库类型string](#标准库类型string)
    - [定义和初始化string对象](#定义和初始化string对象)
    - [string对象上的操作](#string对象上的操作)
        - [读写string对象](#读写string对象)
        - [使用getline读取一整行](#使用getline读取一整行)
        - [`string`的`empty`和`size`操作](#`string`的`empty`和`size`操作)
        - [字面值和string对象相加](#字面值和string对象相加)
        - [处理每个字符，使用基于范围的for语句](#处理每个字符，使用基于范围的for语句)
        - [处理一部分字符，可以使用下标运算符和迭代器](#处理一部分字符，可以使用下标运算符和迭代器)
* [标准库类型vector](#标准库类型vector)
    - [定义和初始化vector对象](#定义和初始化vector对象)
    - [列表初始化vector对象](#列表初始化vector对象)
    - [向vector对象中添加元素](#向vector对象中添加元素)
    - [其它vector操作](#其它vector操作)
* [迭代器](#迭代器)
    - [使用迭代器](#使用迭代器)
* [数组](#数组)
    - [定义和初始化内置数组](#定义和初始化内置数组)
    - [访问数组元素](#访问数组元素)
    - [指针和数组](#指针和数组)
    - [C风格字符串](#C风格字符串)
    - [与旧代码的接口](#与旧代码的接口)
* [多维数组](#多维数组)
	- [多维数组的初始化](#多维数组的初始化)
	- [多维数组的下标引用](#多维数组的下标引用)
	- [使用范围for语句处理多维数组](#使用范围for语句处理多维数组)
    - [指针和多维数组](#指针和多维数组)
    - [类型别名简化多维数组的指针](#类型别名简化多维数组的指针)

## 命名空间的using声明

### namespace

​	指标识符的可见范围。作用是避免程序中的命名冲突，声明作用域。

#### 命名空间的定义

```c++
namespace name {...};
```

#### 命名空间的使用

- 命名空间的成员可以是变量，函数，结构体，类

- 命名空间的声明必须放在全局

- 命名空间可以重名，重名之后是做合并操作

- 命名空间可以取别名 namespace 别名= 原名

- 命名空间中的函数，定义和声明必须分离

- 命名空间可以嵌套命名空间

```c++
#include <iostream>
using namespace std;
namespace namespaceA
{
    int a = 0;
    namespace namespaceB
    {
	int a = 1;
	int b = 2;
    }
}

int main()
{
	cout << namespaceA::a << endl;			    // 输出 0
	cout << namespaceA::namespaceB::a << endl;	    // 输出 1
	return 0;
}
```

### using声明

使用 `using` 声明后，就无须再通过专门的前缀去获取所需的名字了。`using` 声明具有如下的形式：`using namespace::name`。

```c++
#include <iostream>
// using 声明，当使用名字cin时，从命名空间std中获取它
using std::cin;
// 或者使用namespace，就不用单独调用具体的声明了
// using namespace std; 编译指令
int main()
{
	int i;
	cin >> i; 			// ok：cin和std::cin含义相同
	cout << i; 			// error：没有对应的using声明，必须使用完整的名字
	std::cout << i; 		// ok：显式地从std中使用cout
	system("pause");
	return 0 ;
}
```

- `using`的声明作用域和局部作用域不能同时出现，会产生歧义

- `using` 的编译指令和局部作用域可以同时出现，同时出现时使用的局部的作用域。

- 程序中使用的每个名字都需要用独立的 `using` 声明引入，或者需要引入 `namespace`。


- 头文件中通常不应该包含 `using` 声明。这是因为头文件的内容会拷贝到所有引用它的文件中去，如果头文件里有某个 `using` 声明，那么每个使用了该头文件的文件就都会有这个声明。对于某些程序来说， 由于不经意间包含了一些名字， 反而可能产生始料未及的名字冲突。

## 标准库类型string

标准库类型 `string` 表示可变长的字符序列，定义在头文件 `string` 中。

```c++
#include <string>
using std::string;
```

### 定义和初始化string对象

初始化`string`的方式

| string s1           | 默认初始化，s1是一个空串                              |
| ------------------- | ----------------------------------------------------- |
| string s2           | s2是s1的副本                                          |
| string s2 = s1      | 等价于s2(s1)，s2是s1的副本                            |
| string s3("value")  | s3是字面值"value"的副本，除了字面值最后的那个空字符外 |
| string s3 = "value" | 等价于s3("value")，s3是字面值"value"的副本            |
| string s4 (n,'c');  | 把s4初始化为由连续n个字符c组成的串                    |

**直接初始化**（`copy initialization`）：**不使用等号初始化一个变量**

**拷贝初始化（`direct initialization`）**：**使用等号初始化一个变量**，编译器把等号右侧的初始值拷贝到新创建的对象中去。

```c++
string s5 = "hiya";  // 拷贝初始化
string s6("hiya") ;  // 直接初始化
string s7(10, 'c');  // 直接初始化，s7的内容是cccccccccc
```

### string对象上的操作

`string`的操作：

| os<<s           | 将s写到输出流os当中，返回os                                  |
| --------------- | ------------------------------------------------------------ |
| is>>s           | 从is中读取字符串赋给s，字符串以空白分隔，返回is              |
| geline(is, s)   | 从is中读取一行赋给s，返回is                                  |
| s.empty()       | s为空返回true，否则返回false                                 |
| s.size()        | 返回s中字符的个数                                            |
| s[n]            | 返回s中第n个字符的引用，位置n从0计起                         |
| s1 + s2         | 返回s1和s2连接后的结果                                       |
| s1 = s2         | 用s2的副本代替s1中原来的字符                                 |
| s1 == s2        | 如果s1和s2中所含的字符完全一样，则它们相等，string对象的相等性判断对字母的大小写敏感 |
| s1 != s2        | 等性判断对字母的大小写敏感                                   |
| < , <= , > , >= | 利用字符在字典中的顺序进行比较，且对字母的大小写敏感         |

#### 读写string对象

在执行读取操作时，`string` 对象会自动忽略开头的空白（空格符、换行符、制表符等）并从第一个真正的字符开始读取，直到遇见下一处空白为止。

```c++
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string s;
	cin >> s;
	cout << s << endl;
	system("pause");
	return 0;
}
```

#### 使用getline读取一整行

当希望能在输出的字符串中保留输入的空白字符时，可以使用 `getline` 函数，`getline `函数可以读取一整行字符。该函数只要遇到换行符就结束读取并返回结果（换行符也被读进来了），然后把所读内容存入到 `string` 对象中（不保存换行符）。如果输入的开始就是一个换行符，则得到空` string`。

```c++
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string line;
   	// 每次读入一整行，直至到达文件末尾
	while(getline(cin,line))
		 cout << line << endl;
	return 0;
}
```

触发 `getline` 函数返回的那个换行符实际上被丢弃掉了，得到的 `string` 对象中并不包含该换行符,和往常一样，使用`endl`结束当前行并刷新显示缓冲区。

#### `string`的`empty`和`size`操作

`empty` 函数根据 `string` 对象是有为空返问一个对应的布尔值。

```c++
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string line;
  	// 每次读入一整行，遇到空行直接跳过
	while(getline(cin,line))
	    if(line.empty()) {
	    	continue
	    }
	    cout << line << endl;
	return 0;
}
```

`size` 函数返回 `string` 对象的长度（即 `string` 对象中字符的个数），返回值其实是 `string::size_type` 类型，这是一种无符号类型。要使用 `size_type`，必须先指定它是由哪种类型定义的。

```c++
auto len = line.size();			// len的类型是string::size_type
```

**Tip**: 如果一个表达式中已经有了 `size` 函数就不要再使用 `int` 了，这样可以避免混用 `int` 和 `unsigned int` 可能带来的问题。

#### 字面值和string对象相加

当把 `string` 对象和字符字面值及字符串字面值混合在一条语句中使用时，**必须确保每个加法运算符两侧的运算对象中至少有一个是 `string`**。

```c++
string s;
string s1 = s + ",";			// ok: 把一个string对象和一个字面值相加
string s2 = "hello" + " ,"; 		// error:两个运算对象都不是string
string s3 = s + "," + "hello"; 		// ok: 每个加法运算符都有一个运算对象是string
string s4 = "hello" + "," + s; 		// error:不能把字面值直接相加
```

为了与C兼容，C++语言中的字符串字面值并不是标准库 `string` 的对象。 切记，字符串字面值与 `string` 是不同的类型。

### 03）处理string对象中的字符

头文件 *cctype* 中的字符操作函数：

| isalnum(c)  | 当c是字母或数字时为真                                        |
| ----------- | ------------------------------------------------------------ |
| isalpha(c)  | 当c是字母时为真                                              |
| iscntrl(c)  | 当c是控制字符时为真                                          |
| isdigit(c)  | 当c是数字时为真                                              |
| isgraph(c)  | 当c不是空格但可打印时为真                                    |
| islower(c)  | 当c是小写字母时为真                                          |
| isprint(c)  | 当c是可打印字符时为真(即c是空格或c具有可视形式)              |
| ispunct(c)  | 当c是标点符号时为真(即c不是控制字符、数字、字母、可打印空白中的一种) |
| isspace(c)  | 当c是空白时为真(即c是空格、横向制表符、纵向制表符、回车符、换行符、进纸符中的一种) |
| isupper(c)  | 当c是大写字母时为真                                          |
| isxdigit(c) | 当c是十六进制数字时为真                                      |
| tolower(c)  | 如果c是大写字母，输出对应的小写字母；否则原样输出c           |
| toupper(c)  | 如果c是小写字母，输出对应的大写字母；否则原样输出c           |

建议使用C++版本的C标准库头文件。C语言中名称为 *name.h* 的头文件，在C++中则被命名为 *cname*。

#### 处理每个字符，使用基于范围的for语句

C++11提供了范围 `for`（range for）语句，可以遍历给定序列中的每个元素并执行某种操作。

```c++
for (declaration : expression)
     statement
```

其中，*expression* 部分是一个对象，用于表示一个序列。*declaration* 部分负责定义一个变量，该变量被用于访问序列中的基础元素。每次迭代，*declaration* 部分的变量都会被初始化为 *expression* 部分的下一个元素值。

```c++
string str("some string");
//每行输出str中的一个字符
for(auto c : str)						// 对于str中的每个字符
		cout << c << endl;				// 输出当前字符，后面紧跟一个换行符
```

如果想在范围 `for` 语句中改变 `string` 对象中字符的值，必须把循环变量定义成引用类型。

```c++
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string s("Hello, World!!!");
	// 转换成大写形式
	for (auto &c : s)  				// 对于s中的每个字符(注意c是引用)
	    c = toupper(c);				// c是一个引用，因此赋位语句将改变s中字符的值
	cout << s << endl;
	system("pause");
	return 0;
}
```

 #### 处理一部分字符，可以使用下标运算符和迭代器

标运算符接收的输入参数是 `string::size_type` 类型的值，表示要访问字符的位置，返回值是该位置上字符的引用。

```c++
stirng s("some string");
if (!s.empty())
    s[0] = toupper(s[0]);
```

- string对象的下标必须大于等于`0`而小于`s.size()`,使用超出范围的下标将引发不可预知的后果。
- C++标准并不要求标准库检测下标是否合法。编程时可以把下标的类型定义为相应的 `size_type`，这是一种无符号数，可以确保下标不会小于0，此时代码只需要保证下标小于 `size` 的值就可以了。另一种确保下标合法的有效手段就是使用范围 `for` 语句。



## 标准库类型vector

标准库类型 `vector` 表示对象的集合，也叫做 **容器（container）**，定义在头文件 *vector* 中。`vector` 中所有对象的类型都相同，每个对象都有一个索引与之对应并用于访问该对象。

实质：动态数组

`vector` 是一个 **类模板（`class template`）**，模板本身不是类或函数，相反可以将模板看作为编译器生成类或函数编写的一份说明。编译器根据模板创建类或函数的过程，称为 **实例化（instantiation）**，当使用模板时，需要指出编译器应把类或函数实例化成何种类型。

```c++
vector<int> ivec;				// ivec保存int类型的对象
vector<Sales_item> Sales_vec;			// 保存Sales_item类型的对象
vector<vector<string>> file;			// 该向量的元素是vector对象
```

`vector` 是模板而非类型，由 `vector` 生成的类型必须包含 `vector` 中元素的类型，如 `vector`。

因为引用不是对象，所以不存在包含引用的 `vector`。

在早期的C++标准中，如果 vector 的元素还是 vector（或者其他模板类型），定义时必须在外层 vector 对象的右尖括号和其元素类型之间添加一个空格，如 `vector<vector<int> >`。但是在C++11标准中，可以直接写成 `vector<vector<int>>`，不需要添加空格。

### 定义和初始化vector对象

初始化 `vector` 对象的方法：

| `vector<T>v1`                     | v1是一个空vector，它潜在的元素是T类型的，执行默认初始化 |
| --------------------------------- | ------------------------------------------------------- |
| `vector<T> v2(v1)`                | v2中包含有v1所有元素的副本                              |
| `vector<T> v2 = v1`               | 等价于v2(v1)，v2中包含有v1所有元素的副本                |
| `vector<T> v3(n,val)`             | v3包含了n个重复的元素，每个元素的值都是val              |
| `vector<T> v4(n)`                 | v4包含了n个重复地执行了值初始化的对象                   |
| `vector<T> v5 { a , b , c ,...}`  | v5包含了初始值个数的元素，每个元素被赋予相应的初始值    |
| `vector<T> v5 = { a , b, c ,...}` | 等价于v5{ a , b , c, ...}                               |

   

初始化 `vector` 对象时：

- 可以默认初始化`vector`对象，从而创建一个指定类型的空`vector`
- 允许一个`vector`对象的元素拷贝给另一个vector元素
- 两个vector对象的类型必须相同
- 不能使用字符串构建vector对象

```c++
vector<int> ivec; 					// 初始化状态为空
// 在此处给ivec添加一些值
vector<int> ivec2(ivec);				// 把ivec的元素拷贝给ivec2
vector<int> ivec3 = ivec;				// 把ivec的元素拷贝给ivec3
vector<string> svec(ivec2);  				// error：svec的元素是string对象，不是int
```

### 列表初始化vector对象

- 如果使用圆括号，可以说提供的值是用来构造（construct） `vector` 对象；
- 如果使用的是花括号，则是在列表初始化（list initialize） `vector` 对象。花括号里的值必须与元素类型相同

```c++
vector<string> articles = {"a","an","the"};
vector<string> v1{"a","an","the"};			// 列表初始化
vector<string> v2("a","an","the");			// error
vector<int> ivec(10);			 		// 10个元素，每个初始化为0
vector<string> svec(10);		 		// 10个元素，每个都是空string对象
vector<int> vi = 10;			 		// error:必须使用直接初始化的形式指定向量大小
vector<string> v1{"hi"};		 		// 列表初始化：v1有一个元素
vector<string> v2("hi");	   	 		// error：不能使用字符串字面值构建vector对象
vector<string> v3{10};			 		// v3有10个默认初始化的元素
vector<string> v4{10,"hi"};				// v4有10个值为“hi"的元素
```

### 向vector对象中添加元素

`push_back` 函数可以把一个值添加到 `vector` 的尾端。

```c++
vector<int> v;				// 空vector对象
for (int i = 0 ; i != 100 ; ++i)
	v.push_back(i);			// 依次把整数值放到v尾端
// 循环结束后v有100个元素，值从0到99
```

### 其它vector操作

`vector` 支持的操作：

| v.empty()             | 如果v不含有任何元素，返回真，否则返回假                |
| --------------------- | ------------------------------------------------------ |
| v.size()              | 返回v中元素的个数                                      |
| v.push_back()         | 向v的尾端添加一个值为t的元素                           |
| v[n]                  | 返回v中第n个位置上元素的引用                           |
| v1 = v2               | 用v2中元素的拷贝替换v1中的元素                         |
| v1 = { a , b ,c ,...} | 用列表中元素的拷贝替换v1中的元素                       |
| v1 == v2              | v1和v2相等当且它们的元素数量相同且对应位置的元素值相同 |
| v1 != v2              |                                                        |
| < , <= , > ,>=        | 顾名思义，以字典顺序进行比较                           |

​	`vector` 和 `string` 对象的下标运算符只能用来访问已经存在的元素，而不能用来添加元素

```c++
vector<int> ivec;   	// 空vector对象
for (decltype(ivec.size()) ix = 0; ix != 10; ++ix)
{
    ivec[ix] = ix;     		 // 严重错误：ivec不包含任何元素，不能使用下标运算符添加元素
    ivec.push_back(ix);		 // 正确：添加一个新元素，该元素的值是ix
}
```

## 迭代器

迭代器的作用和下标运算类似，但是更加通用。所有标准库容器都可以使用迭代器，但是其中只有少数几种同时支持下标运算符。迭代器的作用也和指针类型类似，也提供了对对象的间接访问。

实质就是指针，是算法和容器之间的桥梁，普通的指针也是迭代器

### 使用迭代器

定义了迭代器的类型都拥有 `begin` 和 `end` 两个成员函数。`begin` 函数返回指向第一个元素的迭代器，`end` 函数返回指向容器 **尾元素的下一位置（one past the end）** 的迭代器。

```c++
// 由编译器决定b和e的类型;
// b表示v的第一个元素， e表示v尾元素的下一位置
auto b = ivec.begin(), e = ivec.end();    // b和e的类型相同
```

`end` 函数通常被称作 **尾后迭代器（`off-the-end iterator`）** 或者简称为 **尾迭代器（`end iterator`）**。

如果容器为空，则 `begin` 和 `end` 返回的是同一个迭代器，都是尾后迭代器。

标准容器迭代器的运算符：

| *iter          | 返回迭代器iter所指元素的引用                                 |
| -------------- | ------------------------------------------------------------ |
| iter->men      | 解引用iter并获取该元素的名为mem的成员，等价于(*iter).mem     |
| ++iter         | 令iter指示容器中的下一个元素                                 |
| --iter         | 令iter指示容器中的上一个元素                                 |
| iter1 == iter2 | 判断两个迭代器是否相等(不相等)，如果两个迭代器指示的是同一个元素 |
| iter1 != iter2 | 或者它们是同一个容器的尾后迭代器，则相等，反之，不相等       |

因为 `end` 返回的迭代器并不实际指向某个元素，所以不能对其进行递增或者解引用的操作。

在 `for` 或者其他循环语句的判断条件中，最好使用 `!=` 而不是 `<`。所有标准库容器的迭代器都定义了 `==` 和 `!=`，但是只有其中少数同时定义了 `<` 运算符。

```c++
// 依次处理s的字符直至我们处理完全部字符或者遇到空白
for(auto it = s.begin(); it != s.end() && !isspace(*it); ++it)
	*it = toupper(*it);		// 将当前字符改成大写形式
```

如果 `vector` 或 `string` 对象是常量，则只能使用 `const_iterator` 迭代器，该迭代器只能读元素，不能修改元素。

```c++
vector<int>::iterator it;					  // it 能读写vector<in>的元素
string::iterator it2;						  // it2 能读写string对象中的字符
vector<int>::const_iterator it3;              			  // it3 只能读元素，不能写元素
string::iterator it4;						  // it4只能读字符，不能写字符
```

C++11新增了 `cbegin` 和 `cend` 函数，不论 `vector` 或 `string` 对象是否为常量，都返回 `const_iterator` 迭代器。

`begin` 和 `end` 返回的迭代器具体类型由对象是否是常量决定，如果对象是常量，则返回 `const_iterator`；如果对象不是常量，则返回 `iterator`。

```c++
vector<int> v;
const vector<int> cv;
auto it1 = v.begin();  		 // it1的类型是vector<int>::iterator
auto it2 = cv.begin();  	 // it2的类型是vector<int>::const_iterator
```

- 不能在范围for循环中向vector对象添加元素。
- 任何可能改变容器对象容量的操作，都会使该对象的迭代器失效。

### 02）迭代器运算

`vector` 和 `string` 迭代器支持的操作：



使用迭代器完成了二分搜索：

```c++
// text必须是有序的
// beg和end表示我们搜索的范围
// beg指向搜索范围内的第一个元素、end指向居元素的下一位置、mid指向中间的那个元素
auto beg = text.begin(), end = text.end();
auto mid = text.begin() + (end - beg)/2; 	// 初始状态下的中间点
// 当还有元素尚未检查并且还没有找到sought时执行循环
whi1e (mid != end && *mid != sought)
{
	if (sought < *mid) 				// 我们要找的元素在前半部分吗?
		end = mid; 				// 如果是，调整搜索范围使得忽略掉后半部分
	e1se 						// 我们要找的元素在后半部分
		beg = mid + 1; 				// 在mid之后寻找
	mid = beg + (end - beg)/2; 			// 新的中间点
}
```



## 数组

数组类似 `vector`，也是存放类型相同的对象的容器，但数组的大小确定不变，不能随意向数组中添加元素。

如果不清楚元素的确切个数，应该使用 `vector`。

### 定义和初始化内置数组

数组是一种复合类型，声明形式为 `a[d]`，其中 *a* 是数组名称，*d* 是数组维度。维度说明了数组中元素的个数，因此必须大于0 。数组中元素的个数也属于数组类型的一部分， 编译的时候维度应该是己知的，即维度必须是一个常量表达式。

```c++
unsigned cnt = 42; 					// 不是常量表达式
constexpr unsigned sz = 42; 				// 常量表达式
int arr[10]; 						// 含有10个整数的数组
int *parr[sz]; 						// 含有42个整型指针的数组
string bad[cnt]; 					// error：cnt不是常量表达式
string strs[get_size()]; 				// 当get_size是constexpr时正确，否则错误
```

默认情况下，数组的元素被默认初始化。

定义数组的时候必须指定数组的类型，不允许用 `auto` 关键字由初始值列表推断类型。

如果定义数组时提供了元素的初始化列表，则允许省略数组维度，编译器会根据初始值的数量计算维度。但如果显式指明了维度，那么初始值的数量不能超过指定的大小。如果维度比初始值的数量大，则用提供的值初始化数组中靠前的元素，剩下的元素被默认初始化。

```c++
const unsigned sz = 3;
int ia1[sz] = {0,1,2};  				// 含有3个元素的数组，元素值分别是0，1，2
int a2[] = {0, 1, 2};   				// 维度是1的数组
int a3[5] = {0, 1, 2};  				// 等价于a3[] = {0, 1, 2, 0, 0}
string a4[3] = {"hi", "bye"};   			// 等价于a4[] = {"hi", "bye", ""}
int a5[2] = {0,1,2};    				// error：初始值过多
```

可以用字符串字面值初始化字符数组，但字符串字面值结尾处的空字符也会一起被拷贝到字符数组中。

```c++
char a1[] = {'C', '+', '+'};        		 // 列表初始化，没有空字符
char a2[] = {'C', '+', '+', '\0'}; 		 // 列表初始化，含有显式的空字符
char a3[] = "C++";      			 // 自动添加表示字符串结束的空字符
const char a4[6] = "Daniel";    	 	 // error：没有空间可存放空字符！
```

不能将数组的内容拷贝给其他数组作为其初始值，也不能用数组为其他数组赋值：

```c++
int a[] = {O , 1 , 2};				// 含有3个整数的数组
int a2[] = a;					// error：不允许使用一个数组初始化另一个数组
a2 = a;						// error：不能把一个数组直接赋值给另一个数组
```

从数组的名字开始由内向外阅读有助于理解复杂数组声明的含义。

```c++
int *ptrs[10];              			// ptrs是含有10个整型指针的数组
int &refs[10] = /* ? */;   		        // error：不存在引用的数组
int (*Parray)[10] = &arr;   			// Parray指向一个含有10个整数的数组
int (&arrRef)[10] = arr;    			// arrRef引用一个含有10个整数的数组
```

### 访问数组元素

数组下标通常被定义成 size_t 类型，这是一种机器相关的无符号类型，可以表示内存中任意对象的大小。size_t 定义在头文件 cstddef 中。

数组除了大小固定这一特点外，其他用法与 vector 基本类似。

大多数常见的安全问题都源于缓冲区溢出错误。当数组或其他类似数据结构的下标越界并试图访问非法内存区域时，就会产生此类错误。

### 指针和数组

使用数组的时候编译器一般会把它转换为数组。

在大多数表达式中，使用数组类型的对象其实是在使用一个指向该数组首元素的指针。

对数组使用下标运算符得到的是该数组指定位置的元素。

```c++
string nums[] = {"one", "two", "three"};    			// 数组的元素是string对象
string *p = &nums[0];   					// p指向nums的第一个元素
string *p2 = nums;      					// 等价于p2 = &nums[0]
```

当使用数组作为一个 `auto` 变量的初始值时，推断得到的类型是指针而非数组。但 `decltype` 关键字不会发生这种转换，直接返回数组类型。

```c++
int ia[] = {0,1,2,3,4,5,6,7,8,9};    			// ia是一个含有10个整数的数纽
auto ia2(ia);   					// ia2是一个整型指针，指向ia的第一个元素
ia2 = 42;                      				// error：ia2是一个指针，不能用int值给指针赋值
auto ia2(&ia[0]);   					// 显然ia2的类型是int*
// ia3是一个含有10个整数的数组
decltype(ia) ia3 = {0,1,2,3,4,5,6,7,8,9};
ia3 = p;    						// error：不能用整型指针给数组赋值
ia3[4] = i;     					// ok：把i的值赋给ia3的一个元素
```

### C风格字符串

c++支持C风格字符串，但在c++程序中最好不要使用它们，这是因为C风格字符串不仅使用起来不方便，而且极易引发程序漏洞，是诸多安全问题的根本原因。

C标准库String函数：所列的函数不负责验证其字符串参数。

| strlen(p)     | 返回p的长度，空字符不计算在内                                |
| ------------- | ------------------------------------------------------------ |
| strcmp(p1,p2) | 比较p1和p2的想等性。如果p1==p2返回0；如果p1>p2，返回一个正值，反之，返回负值 |
| strcat(p1,p2) | 将p2附加到p1之后，返回p1                                     |
| strcpy(p1,p2) | 将p2拷贝给p1,返回p1                                          |

### 与旧代码的接口

- 允许使用以空字符结束的字符数组来初始化string对象或为string对象赋值。

```c++
string s("hello world");		//s的内容是hello world
```

- 在stirng对象的加分运算中允许使用以空字符结束的字符作为其中一个运算对象（不能两个运算对象都是)；在string对象的复合赋值运算中允许使用以空字符结束的字符数组作为右侧的运算对象。

- 不能以string对象直接初始化指向字符的指针

```c++
char *s = s;				// error : 不能用string对象初始化char*
const char *str = s.c_str();		// ok
```

- 如果执行完`c_str（）`函数后程序想一直都能返回其返回的数组，最好将该数组拷贝一份。

- 可以使用数组来初始化vector对象,需指明要拷贝区域的首元素地址和尾后地址

```c++
int int_arr[] = {0,1,2,3,4,5};
// ivec有6个元素，分别是int_arr中对应元素的副本
vector<int> ivec(begin(int_arr),end(int_arr));

// 拷贝三个元素:int_arr[1],int_arr[2],int_arr[3]
vector<int> subVec(int_arr + 1, int_arr + 4);
```

## 多维数组

C++中的多维数组其实就是**数组的数组**。当一个数组的元素仍然是数组时，通常需要用两个维度定义它：一个维度表示数组本身的大小，另一个维度表示其元素（也是数组）的大小。通常把二维数组的第一个维度称作行，第二个维度称作列。

### 多维数组的初始化

多维数组初始化的几种方式：

```c++
int ia[3][4] = 
{   // 三个元素，每个元素都是大小为3的数组
    {0, 1, 2, 3},   // 第1行的初始值
    {4, 5, 6, 7},   // 第2行的初始值
    {8, 9, 10, 11}  // 第3行的初始值
};

// 没有标识每行的花括号，与之前的初始化语句是等价的
int ib[3][4] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

// 显式地初始化每行的首元素
int ic[3][4] = {{ 0 }, { 4 }, { 8 }};

// 显式地初始化第1行，其他元素执行值初始化
int id[3][4] = {0, 3, 6, 9};
```

### 多维数组的下标引用

可以使用下标访问多维数组的元素，数组的每个维度对应一个下标运算符。

- 如果表达式中下标运算符的数量和数组维度一样多，则表达式的结果是给定类型的元素。
- 如果下标运算符数量比数组维度小，则表达式的结果是给定索引处的一个内层数组。

```c++
// 用arr的首元素为ia最后一行的最后一个元素赋值
ia[2][3] = arr[0][0][0];
int (&row)[4] = ia[1];  // 把row绑定到ia的第二个4元素数组上
```

多维数组寻址公式：

```c++
// 二维数组寻址
Type array[N][M];
array[N][M]：*（array + n x sizeof(Type[M] + m x sizeof(Type))
  
// 三维数组寻址
Type array[N][M][L];
array[N][M][L]：*（array + n x sizeof(Type[M][L] + m x sizeof(Type[L])+ l x sizeof(Type))
```

```c++
constexpr size_t rowCnt = 3,colCnt = 4;
int ia[rowCnt][colCnt] ;			// 12个未初始化的元素
// 对于每一行
for(size_t i = 0;i != rowCnt; i++) {
    // 对于行内的每一列
    for(size_t j = 0; j != colCnt; j ++) {
        // 将元素的位置索引作为它的值
        ia[i][j] = i * colCnt + j;
    }
}
```

### 使用范围for语句处理多维数组

```c++
size_t cnt = 0;
for(auto & row : ia)			// 对于外层数组的每一个元素
  for(auto &col :row)	{		// 对于内层数组的每一个元素
      col  = cnt;			// 将下一个值赋给该元
      ++cnt;				// 将cnt 加 1
}
```

使用范围 `for` 语句处理多维数组时，为了避免数组被自动转换成指针，语句中的外层循环控制变量必须声明成引用类型。

```c++
for (const auto &row : ia)  	// 对于外层数组的每一个元素
    for (auto col : row)    	// 对于内层数组的每一个元素
        cout << col << endl;
```

如果 *row* 不是引用类型，编译器初始化 *row* 时会自动将数组形式的元素转换成指向该数组内首元素的指针，这样得到的 *row* 就是 `int*` 类型，而之后的内层循环则试图在一个 `int*` 内遍历，程序将无法通过编译。

```c++
for (auto row : ia)
    for (auto col : row)
```

使用范围 `for` 语句处理多维数组时，除了最内层的循环，其他所有外层循环的控制变量都应该定义成引用类型。

### 指针和多维数组

当使用多维数组的名字时，也会自动将其转换为指向数组首元素的指针。

因为多维数组实际上是数组的数组，所以由多维数组名称转换得到的指针指向第一个内层数组。

```c++
int ia[3][4];       	// 大小为3的数组，每个元素是含有4个整数的数纽
int (*p)[4] = ia;   	// p指向含有4个整数的数组
p = &ia[2];         	// p指向ia的尾元素
```

声明指向数组类型的指针时，必须带有圆括号。

```c++
int *ip[4];     	// 整型指针的数组
int (*ip)[4];   	// 指向含有4个整数的数组
```

C++11新标准，使用 `auto` 和 `decltype` 能省略复杂的指针定义。

```c++
// 输出ia中每个元素的值，每个内层数组各占一行
// p指向含有4个整数的数组
for (auto p = ia; p != ia + 3; ++p) 
{
    // q指向4个整数数组的首元素，也就是说，q指向一个整数
    for (auto q = *p; q != *p + 4; ++q)
        cout << *q << ' ';
    cout << endl;
}
```

使用标准库函数 `begin` 和 `end` 也能实现同样的功能，而且看起来更简洁一些。

```c++
// p指向ia的第一个数组
for (auto p = begin(ia); p != end(ia); ++p) 
{
	// q指向内层数组的首元素
	for (auto q = begin(*p); q != end(*p); ++q)
		cout << *q << ' '; 	// 输出q所指的整数值
	cout << endl;
}
```

### 类型别名简化多维数组的指针

```c++
using int_array = int[4];		
typedef int int_array[4];
//输出ia中每个元素的值，每个内层数组各占一行
for(int_array* p = ia; p != ia + 3; ++p) {
  for (int *q = *p; q != *p + 4; ++q)
    	cout << *q << ' ';
  cout << endl;
}
```

**[⬆ 返回顶部](#目录)**

