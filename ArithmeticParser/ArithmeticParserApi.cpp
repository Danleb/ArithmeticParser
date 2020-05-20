#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "ArgumentsParsing.h"
#include "ArithmeticParserApi.h"
#include "ErrorCode.h"
#include "Node.h"
#include "SyntacticParser.h"
#include "Utils.h"

namespace arithmetic_parser
{
	ErrorCode Process(const int argc, char* argv[])
	{
		std::map<CmdOption, OptionInput> option_inputs;
		ParseArguments(argc, argv, option_inputs);
		return Process(option_inputs);
	}

	ErrorCode Process(const std::map<CmdOption, OptionInput>& option_inputs)
	{
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

		if (!GetInput(option_inputs, input))
		{
			//std::cerr << "!!!";
			return ErrorCode::UNDEFINED_ERROR;
		}

		double result;

		Process(input, result);

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

	__declspec(dllexport) ErrorCode Process(const std::string& input, double& result)
	{
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

		return ErrorCode::SUCCESS;
	}
}