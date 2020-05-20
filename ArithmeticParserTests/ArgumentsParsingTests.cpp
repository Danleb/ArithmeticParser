#include "pch.h"
#include "gtest/gtest.h"

#include <string>
#include <vector>

#include "ArgumentsParsing.h"
#include "ArithmeticParserApi.h"
#include "CmdOption.h"

namespace ArithmeticalParserTests
{
	using OptionsMap = std::map<arithmetic_parser::CmdOption, arithmetic_parser::OptionInput>;

	TEST(ArgumentsParsingTests, ShortVersionTest)
	{
		int argc = 2;
		char* argv[] = { "unused_argument", "-v" };

		OptionsMap option_inputs;

		arithmetic_parser::ParseArguments(2, argv, option_inputs);

		ASSERT_EQ(1, option_inputs.size());
		auto version_search = option_inputs.find(arithmetic_parser::CmdOption::Version);
		ASSERT_TRUE(version_search != option_inputs.end());
	}

	TEST(ArgumentsParsingTests, FullVersionTest)
	{
		int argc = 2;
		char* argv[] = { "unused_argument", "--version" };

		OptionsMap option_inputs;

		arithmetic_parser::ParseArguments(2, argv, option_inputs);

		ASSERT_EQ(1, option_inputs.size());
		auto version_search = option_inputs.find(arithmetic_parser::CmdOption::Version);
		ASSERT_TRUE(version_search != option_inputs.end());
	}

	TEST(ArgumentsParsingTests, ShortHelpTest)
	{
		int argc = 2;
		char* argv[] = { "unused_argument", "-h" };

		OptionsMap option_inputs;

		arithmetic_parser::ParseArguments(2, argv, option_inputs);

		ASSERT_EQ(1, option_inputs.size());
		auto version_search = option_inputs.find(arithmetic_parser::CmdOption::Help);
		ASSERT_TRUE(version_search != option_inputs.end());
	}

	TEST(ArgumentsParsingTests, FullHelpTest)
	{
		int argc = 2;
		char* argv[] = { "unused_argument", "--help" };

		OptionsMap option_inputs;

		arithmetic_parser::ParseArguments(2, argv, option_inputs);

		ASSERT_EQ(1, option_inputs.size());
		auto version_search = option_inputs.find(arithmetic_parser::CmdOption::Help);
		ASSERT_TRUE(version_search != option_inputs.end());
	}

	TEST(ArgumentsParsingTests, ShortClipboardTest)
	{
		int argc = 2;
		char* argv[] = { "unused_argument", "-c" };

		OptionsMap option_inputs;

		arithmetic_parser::ParseArguments(argc, argv, option_inputs);

		ASSERT_EQ(1, option_inputs.size());
		auto clipboard_search = option_inputs.find(arithmetic_parser::CmdOption::Clipboard);
		ASSERT_TRUE(clipboard_search != option_inputs.end());
	}

	TEST(ArgumentsParsingTests, ClipboardAndCmdSpacedTest)
	{
		int argc = 6;
		char* argv[] = { "unused_argument", "-c", "1+1", "+", "1+", "1" };

		OptionsMap option_inputs;

		arithmetic_parser::ParseArguments(argc, argv, option_inputs);

		ASSERT_EQ(option_inputs.size(), 2);

		auto clipboard_search = option_inputs.find(arithmetic_parser::CmdOption::Clipboard);
		ASSERT_TRUE(clipboard_search != option_inputs.end());

		auto expr_search = option_inputs.find(arithmetic_parser::CmdOption::Expression);
		ASSERT_TRUE(expr_search != option_inputs.end());
		auto argument = expr_search->second.arguments[0];
		ASSERT_EQ(argument, "1+1 + 1+ 1");
	}
}