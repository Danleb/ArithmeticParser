#include <iostream>

#include "ArithmeticParserApi.h"

int main(const int argc, char* argv[]) noexcept
{
	try
	{
		return static_cast<int>(arithmetic_parser::Process(argc, argv));
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}