#include<iostream>
#include<string>
#include<memory>

#include"main.h"
#include"Node.h"
#include"Utils.h"
#include"ErrorCode.h"
#include"SyntacticParser.h"

int main(int argc, char** argv)
{
	(int)ArithmeticParser::Process(argc, argv);
}

ArithmeticParser::ErrorCode ArithmeticParser::Process(int argc, char** argv)
{
	if (argc == 1)
	{
		std::cout << "Empty input! You have to enter the expression to calculate.";
		return ArithmeticParser::ErrorCode::UNDEFINED_ERROR;
	}

	std::string input;
	
	for (size_t i = 1; i < argc; i++)
	{
		input.append(argv[i]);
	}

	std::unique_ptr<ArithmeticParser::Node> node;

	try
	{
		node = ArithmeticParser::ParseFunction(input);
	}
	catch (const std::exception & e)
	{
		std::cout << "There was an error during the expression parsing:" << std::endl;
		std::cout << e.what() << std::endl;
		return ArithmeticParser::ErrorCode::LEXICAL_ERROR;
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
		return ArithmeticParser::ErrorCode::SYNTACTIC_ERROR;
	}

	return ArithmeticParser::ErrorCode::SUCCESS;
}