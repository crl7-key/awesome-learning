#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <algorithm>    // std::equal


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
