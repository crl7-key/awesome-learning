#!/bin/bash 
#     #!   告诉系统这个脚本需要什么解释器来执行
echo 'hello the first shell!'

# 运行
# 方法1 
#sh echo.sh 

# 方法2
#chmod u+x echo.sh 
#./echo.sh

# 文件扩展名 .sh 不是强制要求的。
# 方法1 直接运行解释器，echo.sh 作为 Shell 解释器的参数。此时 Shell 脚本就不需要指定解释器信息，第一行可以去掉。
# 方法2 echo.sh 作为可执行程序运行，Shell 脚本第一行一定要指定解释器。