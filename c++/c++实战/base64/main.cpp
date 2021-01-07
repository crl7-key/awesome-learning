#include <iostream>
#include "base64.h"
#include <cstring>



int main(int argc, const char** argv) 
{
    std::string str = "heal the world, make it a better place";

    std::string s64 = base64_encode((const unsigned char *)(str.c_str()),std::strlen(str.c_str()));
    std::cout << "Data after encoding  is ： [ " << s64 <<  " ], len is : " << std::strlen(s64.c_str()) << std::endl;
    
    std::cout << "The decoding data is : [ " << base64_decode(s64) << " ]"<< std::endl;
    return 0;
}
