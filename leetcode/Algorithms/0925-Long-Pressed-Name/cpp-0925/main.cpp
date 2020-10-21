#include <iostream>

using namespace std;


class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int index = 0;
        int nLen = name.length();
        int tLen = typed.length();
        for (int i = 0; i < tLen; ++i)
            if (index < nLen && name[index] == typed[i]) { // 两个字符串存在一对匹配的字符
                ++index;
            }
            else if (!i || typed[i] != typed[i - 1]) { // type[i] == type[i - 1]说明存在一次长按键入
                return false;
            }
        return index == nLen;
    }
};

int main(int argc, char const *argv[])
{
    string name = "alex";
    string typed = "aaleex";
    cout << Solution().isLongPressedName(name,typed) << endl;
    return 0;
}


