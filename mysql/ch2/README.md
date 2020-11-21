# MySql日志系统

## 目录
* [基础架构](#基础架构)
- [重做日志模块：redo log](#重做日志模块：redo-log)
- [查询缓存](#查询缓存)
- [归档日志模块：binlog](#归档日志模块：binlog)
- [两阶段提交](#两阶段提交)

## 更新语句的执行流程
一条查询语句的执行过程一般是经过连接器、分析器、优化器、执行器等功能模块,最后到达存储引擎。
更新语句的执行流程也是同样会走一遍。
例如：一个表的创建语句如下,这个表有一个主键`ID`和一个整型字段`c`：
```mysql
mysql> create table T(ID int primary key, c int);
```
如果要将`ID=2`这一行的值加`1`,`SQL`语句就会这么写：
```
mysql> update T set c=c+1 where ID=2;
```
执行语句前要先连接数据库,这是连接器的工作。
在一个表上有更新的时候,跟这个表有关的查询缓存会失效,所以这条语句就会把表`T`上所有缓存结果都清空。

接下来,分析器会通过词法和语法解析知道这是一条更新语句。优化器决定要使用`ID`这个索引。然后执行器负责具体执行,找到这一行,然后更新。

与查询流程不一样的是,更新流程还涉及两个重要的日志模块,`redo log`（**重做日志**）和 `binlog`（归档日志）

## 重做日志模块：redo log
在`MySQL`里,如果每一次的更新操作都需要写进磁盘,然后磁盘也要找到对应的那条记录,然后再更新,整个过程`IO`成本、查找成本都很高。为了解决这样的问题,`MySql`使用了`WAL`技术,`WAL`的全称是`Write-Ahead Logging`,它的关键点就是先写日志,再写磁盘。
- 当有一条记录需要更新的时候,`InnoDB`引擎就会先把记录写到`redo log`里面,并更新内存,这个时候更新就算完成了。
- `InnoDB`引擎会在适当的时候,将这个操作记录更新到磁盘里面,而这个更新往往是在系统比较空闲的时候做
- `InnoDB`的`redo log`是固定大小的,比如可以配置为一组`4`个文件,每个文件的大小是`1GB`,那么总共就可以记录`4GB`的操作,从头开始写,写到末尾就又回到开头循环写。

![image](images/redo_log.png)
`write pos`是当前记录的位置,一边写一边后移,写到第`3`号文件末尾后就回到`0`号文件开头。`checkpoint`是当前要擦除的位置,也是往后推移并且循环的,擦除记录前要把记录更新到数据文件。

`write pos`和`checkpoint`之间的还空着的部分,可以用来记录新的操作。如果`write pos`追上`checkpoint`,表示日志满了,这时候不能再执行新的更新,得停下来先擦掉一些记录,把`checkpoint`推进一下。


有了`redo log`,`InnoDB`就可以保证即使数据库发生异常重启,之前提交的记录都不会丢失,这个能力称为`crash-safe`。

## 归档日志模块：binlog
`MySQL`整体来看,其实就有两块：一块是`Server`层,它主要做的是`MySQL`功能层面的事情；还有一块是引擎层，负责存储相关事宜。
`redo log`是`InnoDB`引擎特有的日志,而`Server `层也有自己的日志,称为`binlog`（**归档日志**）。
- 最开始`MySQL `并没有`InnoDB`引擎。`MySQL`自带的引擎是`MyISAM`
- `MyISAM`没有`crash-safe`的能力,`binlog`日志只能用于归档。
- `InnoDB`是另一个公司以插件形式引入`MySQL`的,既然只依靠`binlog`是没有`crash-safe`能力的,所以`InnoDB`使用另外一套日志系统——也就是`redo log`来实现`crash-safe`能力。

### redo log 和binlog的不同：
- `redo log`是`InnoDB`引擎特有的;`binlog`是`MySQL`的`Server`层实现的,所有引擎都可以使用。
- `redo log`是物理日志,记录的是`“在某个数据页上做了什么修改”`；`binlog`是逻辑日志,记录的是这个语句的原始逻辑,比如“给`ID=2`这一行的`c`字段加`1 `”。
- `redo log`是循环写的,空间固定会用完；`binlog`是可以追加写入的。**“追加写”**是指`binlog`文件写到一定大小后会切换到下一个,并不会覆盖以前的日志。

有了对这两个日志的概念性理解,再来看执行器和`InnoDB`引擎在执行这个简单的`update`语句时的内部流程。
- 执行器先找引擎取`ID=2`这一行。`ID`是主键,引擎直接用树搜索找到这一行。如果`ID=2`这一行所在的数据页本来就在内存中,就直接返回给执行器；否则,需要先从磁盘读入内存,然后再返回。

- 执行器拿到引擎给的行数据,把这个值加上`1`,比如原来是`N`,现在就是`N+1`,得到新的一行数据,再调用引擎接口写入这行新数据。

- 引擎将这行新数据更新到内存中,同时将这个更新操作记录到`redo log`里面,此时`redo log`处于`prepare`状态。然后告知执行器执行完成了,随时可以提交事务。

- 执行器生成这个操作的`binlog`,并把`binlog`写入磁盘。

- 执行器调用引擎的提交事务接口,引擎把刚刚写入的`redo log`改成提交（`commit`）状态,更新完成。
![image](images/update.png)
其中浅色框表示是在`InnoDB`内部执行的,深色框表示是在执行器中执行的。
将`redo log`的写入拆成了两个步骤:`prepare`和`commit`,这就是"两阶段提交"。

## 两阶段提交
两阶段提交的作用是为了让两份日志之间的逻辑一致。由于`redo log`和`binlog`是两个独立的逻辑,如果不用两阶段提交,要么就是先写完`redo log`再写`binlog`,或者采用反过来的顺序,这样会出现一些问题
- **先写`redo log`后写`binlog`**。   
    假设在`redo log`写完,binlog 还没有写完的时候,`MySQL`进程异常重启。由于`redo log`写完之后,系统即使崩溃,仍然能够把数据恢复回来,所以恢复后这一行`c`的值是`1`。但是由于`binlog`没写完就`crash`了,这时候`binlog`里面就没有记录这个语句。因此,之后备份日志的时候存起来的 `binlog `里面就没有这条语句,如果需要用这个`binlog`来恢复临时库的话,由于这个语句的`binlog`丢失,这个临时库就会少了这一次更新,恢复出来的这一行`c`的值就是`0`,与原库的值不同。
- **先写`binlog`后写`redolog`**。   
    如果在`binlog`写完之后`crash`,由于`redo log`还没写,崩溃恢复以后这个事务无效,所以这一行`c`的值是`0`。但是`binlog`里面已经记录了`“把 c 从 0 改成 1”`这个日志。所以,在之后用`binlog`来恢复的时候就多了一个事务出来,恢复出来的这一行`c`的值就是`1`,与原库的值不同。
可以看到,如果不使用`“两阶段提交”`,那么数据库的状态就有可能和用它的日志恢复出来的库的状态不一致。

当需要扩容的时候,也就是需要再多搭建一些备库来增加系统的读能力的时候,现在常见的做法也是用全量备份加上应用`binlog`来实现的,这个`“不一致”`就会导致你的线上出现主从数据库不一致的情况。   

简单说,`redo log`和`binlog`都可以用于表示事务的提交状态,而两阶段提交就是让这两个状态保持逻辑上的一致。


## 个人总结
- `MySql`中一条更新语句的执行过程和查询语句的执行过程差不多,也是要经过连接器、分析器、优化器、执行器等功能模块,最后到达存储引擎。查询流程不一样的是,更新流程还涉及两个重要的日志模块,即物理日志`redo log`和逻辑日志`binlog`。

- `redo log`用于保证`crash-safe`能力。`innodb_flush_log_at_trx_commit`这个参数设置成`1`的时候,表示每次事务的`redo log`都直接持久化到磁盘。这个参数建议设置成`1`,这样可以保证`MySQL`异常重启之后数据不丢失。

- `sync_binlog`这个参数设置成`1`的时候,表示每次事务的`binlog`都持久化到磁盘。这个参数也建议设置成`1`,这样可以保证`MySQL`异常重启之后`binlog`不丢失。

- `binlog`作用:
    - 恢复数据库（全量备份 + 备份时间点后的`binglog`)
    - 扩容搭建备库（全量备份 + 备份时间点后的`binglog`)
    - 同步数据




**[⬆ 返回顶部](#目录)**