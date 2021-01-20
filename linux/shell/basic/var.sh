#Shell 变量分为系统变量和自定义变量。系统变量有$HOME、$PWD、$USER等，显示当前 Shell 中所有变量：set 。
#变量名可以由字母、数字、下划线组成，不能以数字开头。

#!/bin/bash

# 定义变量：变量名=变量值，等号两侧不能有空格，变量名一般习惯用大写。
#删除变量：unset 变量名 。
#声明静态变量：readonly 变量名，静态变量不能unset。
#使用变量：$变量名

Days=10
Guest="Katie"
echo "$Guest logged in $Days days age"
Guest="Katie2"

Days=5
echo "$Guest logged in $Days days age"

