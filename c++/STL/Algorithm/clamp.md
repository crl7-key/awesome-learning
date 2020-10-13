# clamp

## 头文件
```cpp
#include <algorithm>
```

## 函数原型:

```cpp
template<class T>
constexpr const T& clamp( const T& v, const T& lo, const T& hi )
{
    assert( !(hi < lo) );
    return (v < lo) ? lo : (hi < v) ? hi : v;
}

// 函数重载,使用自定义的函数方法comp
template<class T, class Compare>
constexpr const T& clamp( const T& v, const T& lo, const T& hi, Compare comp );
```

## 作用
  将数字限制在两个数字的特定范围内的方法,如果Value大于minValue且小于maxValue,它将返回对该数字的引用。
  如果Value小于minValue,则将返回minValue.同样,如果Value大于maxValue,则将返回maxValue。
 ```cpp
template<class T>
constexpr const T& clamp( const T& v, const T& lo, const T& hi )
{
    assert( !(hi < lo) );
    return (v < lo) ? lo : (hi < v) ? hi : v;
}
 ```
 
   第二个原型相当于函数重载,最后一个参数是使用自定义的函数方法comp
```cpp
template<class T, class Compare>
constexpr const T& clamp( const T& v, const T& lo, const T& hi, Compare comp )
{
    assert( !comp(hi, lo) );
    return comp(v, lo) ? lo : comp(hi, v) ? hi : v;
}
```

  ## Example
  ```cpp
#include <iostream>     //  std::cout
#include <algorithm>    //  std::clamp

template<class T>
const T& clamp(const T& value, const T& minValue, const T& maxValue) {
	return std::min(maxValue, std::max(value, minValue));
}

int main(void)
{
	for (int i = 0; i < 20; i++)
	{
		std::cout << clamp(i, 0, 10) << std::endl;
	}

	system("pause");
	return 0;
}
  
  ```
  
