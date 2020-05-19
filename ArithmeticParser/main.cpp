#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "main.h"
#include "Node.h"
#include "ErrorCode.h"
#include "SyntacticParser.h"
#include "ArgumentsParsing.h"
#include "Utils.h"

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

namespace arithmetic_parser
{
	ErrorCode Process(const int argc, char* argv[])
	{
		std::map<CmdOption, OptionInput> option_inputs{};

		ParseArguments(argc, argv, option_inputs);

		if (option_inputs.empty())
		{
			std::cout << "Empty input! You have to enter the expression to calculate.";
			return ErrorCode::UNDEFINED_ERROR;
		}

		OptionInput option_input;

		if (FindOption(option_inputs, CmdOption::Version, option_input))
		{
			ShowVersion();
			return ErrorCode::SUCCESS;
		}

		if (FindOption(option_inputs, CmdOption::Help, option_input))
		{
			ShowHelp();
			return  ErrorCode::SUCCESS;
		}

		std::string input;

		if (FindOption(option_inputs, CmdOption::File, option_input))
		{
			auto load_path = option_input.arguments[0];

			if (!LoadExpression(load_path, input))
			{
				return ErrorCode::UNDEFINED_ERROR;
			}
		}
		else
		{

		}

		std::shared_ptr<Node> node;

		try
		{
			SyntacticParser syntactic_parser(input);
			node = syntactic_parser.ParseFunction();
		}
		catch (const std::exception& e)
		{
			std::cout << "There was an error during the expression parsing:" << std::endl;
			std::cout << e.what() << std::endl;
			return ErrorCode::LEXICAL_ERROR;
		}

		double result;

		try
		{
			result = node->Calculate();
			std::cout << "Result = " << result << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "There was an error during the expression calculating:" << std::endl;
			std::cout << e.what() << std::endl;
			return ErrorCode::SYNTACTIC_ERROR;
		}

		if (FindOption(option_inputs, CmdOption::Save, option_input))
		{
			const auto save_path = option_input.arguments[0];
			SaveResult(save_path, result);
		}

		if (FindOption(option_inputs, CmdOption::Clipboard, option_input))
		{
			CopyToTheClipboard(result);
		}

		return ErrorCode::SUCCESS;
	}

}