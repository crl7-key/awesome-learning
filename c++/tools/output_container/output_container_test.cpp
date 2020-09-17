#include <iostream>
#include <map>
#include <vector>
#include "output_container.h"

using namespace std;

int main()
{
    map<int,int> m {
        {1,1},{2,4},{3,9}};

    cout << m << endl;

    vector<vector<int>> vec {
        {1,1},{2,4},{3,9}};

    cout << vec << endl;
    return 0;
}
