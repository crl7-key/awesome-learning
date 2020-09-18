#ifndef INC_TEST_H_
#define INC_TEST_H_
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;
static const auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();
template<typename T>
T* generateRandomArray(int n,int rangL,int rangR)
{
    assert(rangL <= rangR);
    //在堆区申请空间
    T *arr = new T[n];

    srand(time(NULL));
    for(int i = 0;i<n;i++)
        arr[i] = rand()%(rangR - rangL +1) + rangL;
    return arr;
}

void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

string boolToString(bool input) {
    return input ? "True" : "False";
}

#endif
