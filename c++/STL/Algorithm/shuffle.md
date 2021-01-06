# shuffle

## 头文件
```cpp
#include  <algorithm>
```

## 函数原型:

```cpp
template< class RandomIt, class URBG >
void shuffle( RandomIt first, RandomIt last, URBG&& g );                                
```


## 作用
将 [`first`, `last`) 的元素次序随机重排


## 函数实现
```c++
template<class RandomIt, class URBG>
void shuffle(RandomIt first, RandomIt last, URBG&& g)
{
    typedef typename std::iterator_traits<RandomIt>::difference_type diff_t;
    typedef std::uniform_int_distribution<diff_t> distr_t;
    typedef typename distr_t::param_type param_t;
 
    distr_t D;
    diff_t n = last - first;
    for (diff_t i = n-1; i > 0; --i) {
        using std::swap;
        swap(first[i], first[D(g, param_t(0, i))]);
    }
}
```

## Example
  
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <chrono>
#include <random>

int main()
{
    // Creating array of size 5
    std::array<int,5> random {1,2,3,4,5}; // 1,2,3,4,5

    // Obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    // Rearranges the elements in the range [first,last) randomly
    shuffle (random.begin(), random.end(), std::default_random_engine(seed));

    std::cout << "Shuffle:";

    // Print the content in array random
    for (int& x: random) std::cout << ' ' << x;
    std::cout << '\n';
    
    return 0;
}

```
**[See Example](snippets/shuffle.cpp)**    

**[Run Code](https://rextester.com/EYLG33276)**