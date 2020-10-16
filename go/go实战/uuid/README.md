# uuid


## 什么是uuid?
`uuid`是`Universally Unique Identifier`的缩写,即通用唯一识别码。

`uuid`的目的是让分布式系统中的所有元素,都能有唯一的辨识资讯,而不需要透过中央控制端来做辨识资讯的指定。如此一来，每个人都可以建立不与其它人冲突的`uuid`。


## C++中生成`uuid`：
```cpp
#pragma comment(lib, "rpcrt4.lib")
#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    UUID uuid;
    UuidCreate(&uuid);
    char *str;
    UuidToStringA(&uuid, (RPC_CSTR*)&str);
    cout<<str<<endl;
    RpcStringFreeA((RPC_CSTR*)&str);
    return 0;
}
```

## go生成uuid：

目前,golang中的`uuid`还没有纳入标准库,我们使用github上的开源库：
```
go get github.com/google/uuid
```

## Example
```go
package main

import (
	"fmt"

	"github.com/google/uuid"
)

//RandomID RandomID
func RandomID() string {
	return uuid.New().String()
}

// FromString FromString
func FromString(s string) (uuid.UUID, error) {
	return uuid.Parse(s)
}

func main() {

	uuid := RandomID()
	fmt.Println("uuid is : ", uuid)
	// 解析
	u2, err := FromString("3d57ae27-6cc4-40c7-b18f-e087b77daded")

	if err != nil {
		fmt.Printf("Something gone wrong: %s", err)
		return
	}
	fmt.Printf("Successfully parsed: %s", u2)
}

```
