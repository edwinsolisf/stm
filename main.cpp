#include <iostream>

#include "stm/math.h"
#include "stm/vector2.h"

int main()
{
	stm::vec2f num1 = { 1.0f, 1.0f };
	stm::vec2f num2(1.0f, 1.0f);
	stm::vector<long long, 6> vec = { 1, 2, 3, 4, 5, 6 };

	std::cout << "Hello world!\n";
	std::cin.get();
	return 0;
}