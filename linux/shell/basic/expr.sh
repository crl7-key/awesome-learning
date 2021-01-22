#!/bin/bash

#运算符


#  $((运算式)) 或 $[运算式]
#   expr m + n 注意 expr 运算符间要有空格
#   expr m - n
#   expr \*，/，% 分别代表乘，除，取余

# 第1种方式 $(()) 
echo $(((2+3)*4)) # output : 20

# 第2种方式 $[]，推荐 
echo $[(2+3)*4]  

# 使用 expr 
TEMP=`expr 2 + 3` 
echo `expr $TEMP \* 4`