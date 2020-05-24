#include "pch.h"
#include "gtest/gtest.h"

#include <string>
#include <vector>

#include "ArgumentsParsing.h"
#include "CmdOption.h"
#include "Node.h"
#include "SyntacticParser.h"

namespace ArithmeticalParserTests::SyntacticParser
{
	TEST(PowerTests, Two_Power_Three__Test)
	{
		arithmetic_parser::SyntacticParser parser("2^3");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 8);
	}

	TEST(PowerTests, Two_Power_Brackets__Test)
	{
		arithmetic_parser::SyntacticParser parser("2^(1--2)");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 8);
	}

	TEST(PowerTests, Brackets_Power_Brackets__Test)
	{
		arithmetic_parser::SyntacticParser parser("(12-10)^(30/10)");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 8);
	}
}