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