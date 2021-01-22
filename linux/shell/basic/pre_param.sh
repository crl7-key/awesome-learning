#!/bin/bash

# $$ ：当前进程的 PID 进程号。
echo 当前的进程号=$$

sh echo.sh &

# $! ：后台运行的最后一个进程的 PID 进程号。
echo 最后一个进程的进程号=$!

# $? ：最后一次执行的命令的返回状态，0为执行正确，非0执行失败。
echo 最后执行的命令结果=$? 