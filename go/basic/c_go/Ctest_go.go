package main

/*
#include <stdio.h>
#include <stdlib.h>
void c_print(char *str) {
    printf("%s\n", str);
}
*/
import "C" //import “C” 必须单起一行，并且紧跟在注释行之后
import "unsafe"

func main() {
	s := "hello world"
	cs := C.CString(s)               //字符串映射
	C.c_print(cs)                    //调用C函数
	defer C.free(unsafe.Pointer(cs)) //释放内存
}
