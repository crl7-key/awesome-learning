# mismatch

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class InputIt1, class InputIt2 >
constexpr std::pair<InputIt1,InputIt2>
              mismatch( InputIt1 first1, InputIt1 last1,
                        InputIt2 first2 );
// 函数重载,使用自定义的BinaryPredicate函数 p
template< class InputIt1, class InputIt2, class BinaryPredicate >
constexpr std::pair<InputIt1,InputIt2>
              mismatch( InputIt1 first1, InputIt1 last1,
                        InputIt2 first2,
                        BinaryPredicate p );

// 函数重载
template< class InputIt1, class InputIt2 >
constexpr std::pair<InputIt1,InputIt2>
              mismatch( InputIt1 first1, InputIt1 last1,
                        InputIt2 first2, InputIt2 last2 );

// 函数重载,使用自定义的BinaryPredicate函数 p
template< class InputIt1, class InputIt2, class BinaryPredicate >
constexpr std::pair<InputIt1,InputIt2>
              mismatch( InputIt1 first1, InputIt1 last1,
                        InputIt2 first2, InputIt2 last2,
                        BinaryPredicate p );

```

## 作用
用来平行比较两个序列，指出两者之间的第一个不匹配点。  
`mismatch( start_iter1, end_iter1, start_iter2 ) `
- 此函数返回第一个不匹配对指针，第一个元素指向第一个容器的第一个不匹配元素的位置，第二个元素指向第二个容器的第一个不匹配元素的位置。如果未找到不匹配项，则第一个元素指向第一个容器的最后一个元素之后的位置，第二个元素指向第二个容器中的相应位置。  

`mismatch( start_iter1, end_iter1, start_iter2, comparator) `
-  该功能几乎与上述版本相似，但是它不仅提供相等性不匹配的功能，还可以通过用户定义的比较器功能查找其他用户定义的和所需的不匹配的功能作为第`4`个参数发送，并返回布尔值`true`或`false`。



```cpp
template<class InputIt1, class InputIt2>
std::pair<InputIt1, InputIt2>
    mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2)
{
    while (first1 != last1 && *first1 == *first2) {
        ++first1, ++first2;
    }
    return std::make_pair(first1, first2);
}

// 函数重载，使用自定义的BinaryPredicate函数 p
template<class InputIt1, class InputIt2, class BinaryPredicate>
std::pair<InputIt1, InputIt2>
    mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
{
    while (first1 != last1 && p(*first1, *first2)) {
        ++first1, ++first2;
    }
    return std::make_pair(first1, first2);
}

// 函数重载
template<class InputIt1, class InputIt2>
std::pair<InputIt1, InputIt2>
    mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
{
    while (first1 != last1 && first2 != last2 && *first1 == *first2) {
        ++first1, ++first2;
    }
    return std::make_pair(first1, first2);
}



template<class InputIt1, class InputIt2, class BinaryPredicate>
std::pair<InputIt1, InputIt2>
    mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, BinaryPredicate p)
{
    while (first1 != last1 && first2 != last2 && p(*first1, *first2)) {
        ++first1, ++first2;
    }
    return std::make_pair(first1, first2);
}
```

## Example
  
 ```cpp
#include <iostream>     
#include <algorithm>    
#include <vector>       

bool check(int i,int j){
    return ((i+10)==j);
}

int main () {
    
    std::vector<int> v1{10, 20, 30, 40, 50, 70, 80, 90};
    std::vector<int> v2{10, 20, 30, 40, 50, 60, 70, 80};
    std::vector<int> v3{20, 30, 40, 50, 70, 80, 90};
     
    // PAIR P TO STORE THE PAIR RETURNED BY MISMATCH
    std::pair<std::vector<int>::iterator,std::vector<int>::iterator> p;

    // MISMATCH FUNCTION CALL 1: returns the first element where two arrays differ
    p = std::mismatch (v1.begin(), v1.end(), v2.begin());
    std::cout << "Mismatching elements case 1: " << *p.first << " and " << *p.second << '\n'; // output: Mismatching elements case 1: 70 and 60
    
    // MISMATCH FUNCTION CALL 2: returns the first element where two arrays differ as per predicate 
    p = std::mismatch (v1.begin(), v1.end(), v3.begin(), check);
    std::cout << "Mismatching elements case 2: " << *p.first << " and " << *p.second << '\n'; // output: Mismatching elements case 2: 50 and 70
    
    return 0;
}
 ```

**[Run Code](https://rextester.com/WBBV54781)**