#include<iostream>
#include<string>
#include<memory>

#include"Node.h"
#include"Utils.h"
#include"SyntacticParser.h"

int main()
{
	std::string input;
	std::getline(std::cin, input);

	std::unique_ptr<ArithmeticParser::Node> node;

	try
	{
		node = ArithmeticParser::ParseFunction(input);
	}
	catch (const std::exception & e)
	{
		std::cout << "There was an error during the expression parsing:" << std::endl;
		std::cout << e.what() << std::endl;
		return 1;
	}

	try
	{
		double result = node->Calculate();
		std::cout << "Result = " << result << std::endl;
	}
	catch (const std::exception & e)
	{
		std::cout << "There was an error during the expression calculating:" << std::endl;
		std::cout << e.what() << std::endl;
		return 2;
	}

	return 0;
}