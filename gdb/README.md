# GDB


## 目录
* [GDB是什么？](#GDB是什么？)
* [GDB的应用场景](#GDB的应用场景)  
* [调用GDB调试器的几种方式](#调用GDB调试器的几种方式)  
    - [直接使用 gdb 指令启动 GDB 调试器](#直接使用-gdb-指令启动-GDB-调试器)
    - [调试尚未执行的程序](#调试尚未执行的程序)
    - [调试正在执行的程序](#调试正在执行的程序)
    - [调试执行异常崩溃的程序](#调试执行异常崩溃的程序)
* [GDB调试器启动可用参数](#GDB调试器启动可用参数)  
* [GDB常用命令](#GDB常用命令)

![gdb](image/gdb.png) 

### GDB是什么？
`GDB`全称`“GNU symbolic debugger”`,它诞生于`GNU`计划（同时诞生的还有`GCC`、`Emacs`等,是`Linux`下常用的程序调试器.

### GDB的应用场景
- 程序启动时,可以按照我们自定义的要求运行程序,例如设置参数和环境变量
- 可使被调试程序在指定代码处暂停运行,并查看当前程序的运行状态（例如当前变量的值，函数的执行结果等）,即支持断点调试   
- 程序执行过程中，可以改变某个变量的值,还可以改变代码的执行顺序,从而尝试修改程序中出现的逻辑错误。  

### 调用GDB调试器的几种方式

#### 直接使用 gdb 指令启动 GDB 调试器
```shell
root@MacBook-Pro ~ %  gdb
```
由于此方式启动的`GDB`调试器事先未指定要调试的具体程序,因此需启动后借助`file`或者`exec-file`命令指定   
```
(gdb) file /tmp/demo/main.exe
```

#### 调试尚未执行的程序
对于具备调试信息（使用`-g`选项编译而成）的可执行文件,调用`GDB`调试器的指令格式为：
```shell
gdb program
```
其中`program`为可执行文件的文件名,例如：
```shell
gcc example.c -o test -g
gdb test 
```

#### 调试正在执行的程序
当想调试一个当前已经启动的程序时,但又不想重启该程序,每个进程都配有唯一的进程号（`PID`),需要先找到该程序运行所对应的进程号.
```shell
pidof 文件名
```
例如:
```
pidof test
```
找到`PID`号之后,可以调用`GDB`对该程序进行调试,调用指令有以下 3 种形式，选择其中一条即可:
```
(1)  gdb attach PID
(2)  gdb 文件名 PID
(3)  gdb -p PID
```

#### 调试执行异常崩溃的程序
在程序运行过程中常常会因为各种异常或者`Bug`而崩溃,比如内存访问越界（例如数组下标越界、输出字符串时该字符串没有 `\0`结束符等）、非法使用空指针等,此时就需要调试程序。    

在`Linux`操作系统中,当程序执行发生异常崩溃时,系统可以将发生崩溃时的内存数据、调用堆栈情况等信息自动记录下载,并存储到一个文件中,该文件通常称为`core`文件,`Linux`系统所具备的这种功能又称为核心转储（`core dump`）.

默认情况下,`Linux`系统是不开启`core dump`这一功能的,可以借助执行`ulimit -c`指令来查看当前系统是否开启此功能：

```shell
root@MacBook-Pro ~ % ulimit -a
-t: cpu time (seconds)              unlimited
-f: file size (blocks)              unlimited
-d: data seg size (kbytes)          unlimited
-s: stack size (kbytes)             8192
-c: core file size (blocks)         0
-v: address space (kbytes)          unlimited
-l: locked-in-memory size (kbytes)  unlimited
-u: processes                       5568
-n: file descriptors                2560
```

其中,如果`core file size`（`core` 文件大小）对应的值为 `0`，表示当前系统未开启`core dump`功能。这种情况下,可以通过执行如下指令改变`core`文件的大小：
```shell
root@MacBook-Pro ~ % ulimit -c unlimited
root@MacBook-Pro ~ % ulimit -a
-t: cpu time (seconds)              unlimited
-f: file size (blocks)              unlimited
-d: data seg size (kbytes)          unlimited
-s: stack size (kbytes)             8192
-c: core file size (blocks)         unlimited
-v: address space (kbytes)          unlimited
-l: locked-in-memory size (kbytes)  unlimited
-u: processes                       5568
-n: file descriptors                2560
```
> 其中`unlimited` 表示不限制 `core`文件的大小。   
  
当程序执行发生异常崩溃时,系统就可以自动生成相应的`core`文件。

对于`core`文件的调试,其调用`GDB`调试器的指令为：
```shell
gdb program core
```
例如: 当`test`在运行的时候发生错误,生成了core文件
```
gdb test core
```

#### GDB调试器启动可用参数
调试进程`ID`为`number`的程序:
```
gdb -pid number
gdb -p number
```

从指定`file`文件中读取符号表:
```
gdb -symbols file
gdb -s file
```

取消启动`GDB`调试器时打印的介绍信息和版权信息:
```
gdb -q
gdb -quiet
gdb -silent
```

以`directory`作为启动`GDB`调试器的工作目录,而非当前所在目录:
```
gdb -cd directory
```

向可执行文件传递执行所需要的参数:
```
gdb --args 参数1 参数2...
```

## GDB常用命令
- `run`(r) : 运行一个程序
- `start`: 执行程序，停在`main`函数处
- `continue(c)`: 让暂停的程序继续执行,`continue`默认遇到断点时候会暂停执行,可以使用`continue n`表示继续执行一定次数
- `next`(n): 运行到下一行
- `step`(s): 进入到调用函数内部
- `until`(u): 运行到指定行停下来
- `finish`(fi) : 结束当前调用函数,到上一层函数调用处
- `return`: 结束当前调用函数并返回指定值到上一层函数调用处
    - `finish`命令会执行函数到正常退出函数,`return`会立即结束当前函数并返回
- `jump`(j) : 执行流跳转到指定行或地址
- `print`(p) : 打印变量或寄存器值,也可以修改变量或寄存器值,默认显示有最大长度,设置`set print element 0`可设置将打印结果显示完整
- `backtrace`(bt): 当前线程调用堆栈
    - `bt n` : 显示栈顶的`n`个帧信息
    - `bt -n`: 显示栈底的`n`个帧信息
    - `bt full`: 显示栈中所有帧的所有信息:函数参数、本地变量等
- `frame`(f) : 切换到调用线程的制定堆栈
- `thread id`: 切换到指定线程
- `break`(b) : 添加断点
- `tbradk`: 添加临时断点(`temporary`)
- `rbreak [regex]` : 在满足正则表达式的函数处添加断点
    - 条件断点1 : break [linenumber] if [condition]
    - 条件断点2 : break [linenumber] 再 [condition] [linenumber] [condition]
- `delete`(del): 删除断点
- `enable`: 启用某个断点
- `disable`: 禁用某个断点
- `enable once [num]` : 断点只启用一次
- 捕获: `catch`和`tcatch`表示捕获`xxx`停止程序运行
- `catch syscall close`: 表示`close`系统调用后停止程序运行
- `display`: 每次程序中断下来都会自动输出变量
    - `delete display`
    - `info display`
    - `delete display id`
- `watch` : 监视某一变量或内存地址值是否发生变化,当变化时`gdb`就会停下
    - `watch [expr/field]` : 发生变化时暂停执行
    - `awatch [expr/field]`: 被访问或者发生变化时暂停执行
    - `rwatch [expr/field]`: 被访问时暂停执行
    - `watch expr thread [threadid]` : 监视某个线程的变量表达式
- `list`(l): 显示源码
    - `list + `: 向后看源码
    - `list - `: 向前看源码
    - 默认只显示10行代码,可以查看行数`show `
    - `listsize`: 可以设置行数 `set listsize [num]`
    - `list [first] [last]`
    - `list [function]`
    - `list [filename:function]`
- `info`: 查看断点线程等信息
- `ptype`: 查看变量类型
    - `whatis filed`: 打印处`field`的结构定义
    - `ptype field`: 更详细的打印`field`的类型
- `set variable [field]=[expression]`: 改变变量的值
- `set $r=0=[value]`: 改变寄存器的值
- `disassemble`(dis): 查看汇编代码
- `show disassemble-flavor`: 显示反汇编指令格式
- `set args`: 设置程序启动命令行参数
- `show args`: 查看设置的命令行参数
- `info break`: 查看断点信息
- `info thread`: 查看线程信息
- `info sharedlibrary`: 显示加载的动态链接库信息
    - `LWP: Light Weight Process`：轻量级进程
- `signal SIGSEGV`: 可以使用`signal SIGSEGV`手动给程序发送信号
    - `handle SIGSEGV`: 使用`handle`表示`gdb`调试时忽略某个信号
- `show scheduler-locking` : 显示当前线程`scheduler-locking`状态
- `set scheduler-locking on`: 调试时将程序执行流锁定在当前线程,禁止上下文切换
- `set scheduler-locking off`: 不锁定任何线程,所有线程都执行
- `set scheduler-locking step`: 阻止其它线程在当前线程单步调试时抢占当前线程,当`next`、`continue`、`until`、`finish`等其它线程才会执行
- `checkpoint` 搭配`restart [id]`: 相当于给在当前进程检查点加一个快照,适合调试难以复线的`bug`，预感将要发送`bug`前,添加一个`checkpoint`
- 多线程调试
    - `thread id` : 多线程时,默认是主线程,这里可以切换当前调试的线程为指定的`id`的线程号
    - `thread apply all [cmd]`: 所有线程执行命令
    - `thread apply 1 2 3 [cmd]`: 1 2 3 线程执行命令
    - `thread apply 1 2 3 bt`: 查看1 2 3 线程堆栈信息

**[⬆ 返回顶部](#目录)**