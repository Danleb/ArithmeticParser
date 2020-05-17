#include "pch.h"

#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "ArgumentsParsing.h"

namespace ArithmeticalParserTests
{
	TEST(ArgumentsParsingTests, EmptyInput)
	{

	}

	TEST(ArgumentsParsingTests, OnlyVersion)
	{
		int argc = 2;
		char* argv[] = { "unused_argument", "-v" };

		std::map<arithmetic_parser::CmdOption, arithmetic_parser::OptionInput> option_inputs;

		ParseArguments(2, argv, option_inputs);


	}
}