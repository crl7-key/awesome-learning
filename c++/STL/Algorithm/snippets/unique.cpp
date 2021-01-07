#include <iostream>
#include <algorithm>
#include <vector>


int main()
{
    std::vector<int> vec = {1,1,3,3,5,5,5,1,2,2,8,9,9,9,0,8};
		
    std::vector<int>::iterator it;
    it = std::unique(vec.begin(),vec.end());
		
    vec.resize(std::distance(vec.begin(),it));
		
    // output : 1 3 5 1 2 8 9 0 8
    for(it = vec.begin();it != vec.end();++it) {
        std::cout<<" "<<*it;
    }
    return 0;
}