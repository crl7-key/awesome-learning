#!/bin/bash
#using the backtick character  会把反引号里面当作一条命令来执行

testing=`date`  #  反引号,执行里面的命令
echo "The date and time are:$testing"

testing=$(date) # 等价于反引号
echo "The date and time are:$testing"