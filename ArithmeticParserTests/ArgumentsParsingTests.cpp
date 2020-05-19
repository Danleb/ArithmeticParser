#include "pch.h"

#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "ArgumentsParsing.h"
#include "CmdOption.h"

namespace ArithmeticalParserTests
{
	using OptionsMap = std::map<arithmetic_parser::CmdOption, arithmetic_parser::OptionInput>;

	TEST(ArgumentsParsingTests, EmptyInput)
	{
		int argc = 1;
		char* argv[] = { "unused_argument" };

		OptionsMap options_inputs;

		arithmetic_parser::ParseArguments(argc, argv, options_inputs);

		ASSERT_EQ(0, options_inputs.size());
	}

	TEST(ArgumentsParsingTests, OnlyVersion)
	{
		int argc = 2;
		char* argv[] = { "unused_argument", "-v" };

		OptionsMap option_inputs;

		arithmetic_parser::ParseArguments(2, argv, option_inputs);

		ASSERT_EQ(1, option_inputs.size());
		auto version_search = option_inputs.find(arithmetic_parser::CmdOption::Version);
		ASSERT_TRUE(version_search != option_inputs.end());
	}
}