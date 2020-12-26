#include "gtest/gtest.h"

#include <string>
#include <vector>

#include "ArgumentsParsing.h"
#include "CmdOption.h"

namespace ArithmeticalParserTests
{
	using OptionsMap = std::map<arithmetic_parser::CmdOption, arithmetic_parser::OptionInput>;

	TEST(ArgumentsParsingInvalidDataTests, EmptyInput)
	{
		int argc = 1;
		char* argv[] = { "unused_argument" };

		OptionsMap options_inputs;

		arithmetic_parser::ParseArguments(argc, argv, options_inputs);

		ASSERT_EQ(options_inputs.size(), 0);
	}

	TEST(ArgumentsParsingInvalidDataTests, ShortVersionBad)
	{
		int argc = 2;
		char* argv[] = { "unused_argument", "-version" };

		OptionsMap option_inputs;

		arithmetic_parser::ParseArguments(argc, argv, option_inputs);

		ASSERT_EQ(option_inputs.size(), 1);
		ASSERT_TRUE(option_inputs.find(arithmetic_parser::CmdOption::Expression) != option_inputs.end());
		auto input = option_inputs[arithmetic_parser::CmdOption::Expression];
		ASSERT_EQ(input.arguments.size(), 1);
		ASSERT_EQ(input.arguments[0], argv[1]);
	}
}