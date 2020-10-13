#include <iostream>    // std::cout
#include <algorithm>   // std::clamp std::min std::max

template<class T>
const T& clamp(const T& value, const T& minValue, const T& maxValue) {
	return std::min(maxValue, std::max(value, minValue));
}

int main(void)
{
	for (int i = 0; i < 20; i++) {
		std::cout << clamp(i, 0, 10) << std::endl;
	}

	system("pause");
	return 0;
}
