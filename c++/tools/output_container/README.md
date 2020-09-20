# 一个小工具，可以直接使用输出容器内容:tada:

在你的代码中包含这个头文件，示例代码如下：
```
#include <iostream>
#include <map>
#include <vector>
#include "output_container.h"

using namespace std;

int main()
{
  map<int, int> mp{
    {1, 1}, {2, 4}, {3, 9}};
  cout << mp << endl;
  vector<vector<int>> vv{
    {1, 1}, {2, 4}, {3, 9}};
  cout << vv << endl;
}
```

将会得到下面的输出
> { 1 -> 1, 2 -> 4, 3 -> 9 }  
> { { 1, 1 }, { 2, 4 }, { 3, 9 } }



