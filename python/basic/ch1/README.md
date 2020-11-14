# Python

## 下载
`Python`的官方网站是[https://www.python.org](https://www.python.org)
可以在这个网站下载Python安装包，源码包和文档。

## 安装
`Windows`和`MacOS`安装方式是可视化界面。
`Unix/Linux`是使用源码方式。 
-`MacOS`也算是类`Unix`系统，可以使用源码包安装，但需要一些依赖包。


源码安装方法:
- 下载源码包
- 解压、解包
```sh
wget https://www.python.org/ftp/python/3.9.0/Python-3.9.0.tgz
tar -xvf Python-3.9.0.tgz -C /usr/local
```
- 进入安装目录，使用`./configure + 参数方式来配置安装文件(可以不加任何参数，默认方式安装)`
```sh
./configure --prefix=/usr/local/python3
```
- `make`进行编译
- `make install` 来进行安装
```sh
make && make install
```
- 修改旧版本
```sh
mv /usr/bin/python /usr/bin/python_bak
```
- 创建新的软连接
```sh
ln -s /usr/local/python3/bin/python3 /usr/bin/python
```

## 环境变量设置
| 变量名 | 描述  | 
| :---: | :---:| 
| PYTHONPATH     |  PYTHONPATH是Python搜索路径，默认我们import的 模块都会从PYTHONPATH里面寻找。 |  
| PYTHONSTARTUP  |  Python启动后，先寻找PYTHONSTARTUP环境变量， 然后执行此文件中变量指定的执行代码 |
| PYTHONCASEOK   |  加入PYTHONCASEOK的环境变量, 就会使python导入 模块的时候不区分大小写。        |
| PYTHONCASEOK   |  另一种模块搜索路径。它通常内嵌于的 PYTHONSTARTUP或PYTHONPATH目录中，使得两个 模块库更容易切换。  |

## Python解释器简介
解释器:解释器是一种让其他程序运行起来的程序。实际上，解释器是代码与计算机硬件之间的软件逻辑层。`Shell`就是我们最常见的解释器。 解释器在执行时，每次读入一条语句，并且根据这条语句执行特定的操作;然后再 读入下一条语句，依次类推。

`Python`可以认为是一款编程语言，我们安装的是一个名为解释器的软件包。 当`Python`包安装在机器上后，它包含了一些最小化的组建:一个解释器和支持的库。


## 程序执行
`script0.py`文件,内容如下:
> print(‘hello world!')   
> print(2 ** 100)    

之后执行:
> $python script0.py

其结果为:
> hello world!  
> 1267650600228229401496703205376

对于`Python`，跟`shell`比起来其过程就稍微多几步。  

**字节码编译**: 

`Python`会把源码编译成所谓字节码的形式。编译是一个简单翻译的步骤，可以提高运行速度。如果`Python`进程在机器上拥有写的权限，那么它会把程序的字节码保存为一个以`.pyc`为扩展名的文件。`.pyc`就是编译过的`.py`源代码

**Python虚拟机(PVM)**:

字节码会通过`PVM`来执行。`PVM`是迭代运行字节码指令的一个大循环，一个接一个地完成操作。`PVM`是`Python`的运行引擎，实际运行脚本的组建。

## 交互模式与编写代码

最简单的运行`Python`程序的方法就是交互模式。 在正确配置参数后`“python”`命令就能进入交互模式。 此时提示符会变成`“>>>”` 交互模式通常用于实验和测试。 交互模式下比起文本模式，会有如下特点:
- 文本前面不能有空格，否则报错。
- 复合语句中第二行开始提示符会变成`“...”`。 
- 用一个空行表示符合语句结束。

## 可执行脚本
可执行脚本就是跟`shell`脚本执行方式类似。 在`UNIX`(或类`UNIX`系统中)以`“#!”`开头，并指定程序，并赋予执行权限。
或者不需要`“#!”`开头，只需要如下操作:
> $python script0.py    

这样也能执行`script0.py`里的内容。   
技巧:由于`Python`安装的位置可能都不一样，所以可以在第一行写成如下:
> #!/usr/bin/env python  

这样，系统会自动去找相关`python`。
 
## 基础语法
**标示符**:标识符有字母、数字、下划线组成，但不能以数字开头。 
**行和缩紧**:由于`Python`不使用`{}`来表示符合语句的开始和结束，所以缩紧很重要。  
缩紧例子:  
```python
if True:
    print('first true') 
    if True:
        print('second true')
else: 
    print('first else')
```
上面的例子里，在`C`语言等高级语言里当没有使用`{}`的时候会按最近的匹配方式来 匹配`if`和`else`的。但在`Python`里是以缩紧来匹配。所以上面例子里的`else`匹配的是第一个`if`。

**多行语句**:使用反斜杠(`\`)可以把一行语句写成多行。   
**引号**:在`Python`里引号可以使用单引号(`'`)双引号(`"`)。用法一样。 三引号(` " " "`)可以使用段落。   
**Python注释**:可以使用#来进行注释   