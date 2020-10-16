# equal
  

## 头文件
```cpp
#include <algorithm>  
```

## 函数原型:

```cpp
template< class InputIt1, class InputIt2 >
constexpr bool equal( InputIt1 first1, InputIt1 last1,
                      InputIt2 first2 );

// 函数重载
template< class InputIt1, class InputIt2 >
constexpr bool equal( InputIt1 first1, InputIt1 last1,
                      InputIt2 first2, InputIt2 last2 );
                      

// 函数重载
template< class InputIt1, class InputIt2, class BinaryPredicate >
constexpr bool equal( InputIt1 first1, InputIt1 last1,
                      InputIt2 first2, BinaryPredicate p );


// 函数重载
template< class InputIt1, class InputIt2, class BinaryPredicate >
constexpr bool equal( InputIt1 first1, InputIt1 last1,
                      InputIt2 first2, InputIt2 last2,
                      BinaryPredicate p );

```

## 作用
 将给定范围内的向量元素与先前定义范围内的另一个向量元素进行比较。
 
 ```cpp
template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, 
           InputIt2 first2)
{
    for (; first1 != last1; ++first1, ++first2) {
        if (!(*first1 == *first2)) {
            return false;
        }
    }
    return true;
}

// 函数重载,自定义比较方法p 
template<class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, 
           InputIt2 first2, BinaryPredicate p)
{
    for (; first1 != last1; ++first1, ++first2) {
        if (!p(*first1, *first2)) {
            return false;
        }
    }
    return true;
}
 ```
 
  

  ## Example
  
 ```cpp
bool myFoo(int elem1, int elem2) {
    return  elem1 * 2 == elem2;
}

int main()
{
    
    std::vector<int> v1 {3, 5, 3, 1, 2, 3};
    std::vector<int> v2 {1, 2 ,3, 4, 5, 6};
    std::vector<int> v3 {3, 5, 3, 1, 2, 3};
    std::vector<int> v4 {6, 10, 6, 2, 4, 6};

    // Compare two equal vectors
    if(std::equal(v1.begin(),v1.end(),v2.begin())){
        std::cout << "Vectors are equa!";
    }
    else {
        std::cout << "Vectors are not equal";
    }
    std::cout << "\n";

    // Compare two unequal vectors
    if(std::equal(v1.begin(),v1.end(),v3.begin())) {
        std::cout << "Vectors are equa!";
    }
    else {
        std::cout << "Vectors are not equal";
    }

    std::cout << "\n";

    if(std::equal(v1.begin(),v1.end(),v4.begin(),myFoo)) {
        std::cout << "the vectors v1 and v2 are equal under twice.";
    }
    else {
        std::cout << "the vectors v1 and v2 are not equal under twice.";
    }
    return 0;
}
 ```
