#include "pch.h"
#include "gtest/gtest.h"

#include <string>
#include <vector>

#include "ArgumentsParsing.h"
#include "CmdOption.h"
#include "Node.h"
#include "SyntacticParser.h"

namespace ArithmeticalParserTests
{
	constexpr double Epsilon = 1e-9;

	TEST(SyntacticParserTests, ZeroTest)
	{
		arithmetic_parser::SyntacticParser parser("0");
		auto node = parser.ParseFunction();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 0);
	}

	TEST(SyntacticParserTests, OnePlusOneTest)
	{
		arithmetic_parser::SyntacticParser parser("1+1");
		auto node = parser.ParseFunction();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 2);
	}

	TEST(SyntacticParserTests, _1234_Plus_4567)
	{
		arithmetic_parser::SyntacticParser parser("1234+4567");
		auto node = parser.ParseFunction();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, (1234 + 4567));
	}

	TEST(SyntacticParserTests, _1234_Minus_4567)
	{
		arithmetic_parser::SyntacticParser parser("1234-4567");
		auto node = parser.ParseFunction();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, (1234 - 4567));
	}

	TEST(SyntacticParserTests, FractionalSumTest)
	{
		arithmetic_parser::SyntacticParser parser(".1+0.1");
		auto node = parser.ParseFunction();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 0.2);
	}

	TEST(SyntacticParserTests, SignOperatorTest)
	{
		arithmetic_parser::SyntacticParser parser("+-+-.1+-+-.1");
		auto node = parser.ParseFunction();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 0.2);
	}

	TEST(SyntacticParserTests, ZerosFirstTest)
	{
		arithmetic_parser::SyntacticParser parser("0999+000001");
		auto node = parser.ParseFunction();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 1000);
	}

	TEST(SyntacticParserTests, AlternatingPlusMinusTest)
	{
		arithmetic_parser::SyntacticParser parser("1-2+3");
		auto node = parser.ParseFunction();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 2);
	}

	TEST(SyntacticParserTests, AlternatingPlusMinusTest2)
	{
		arithmetic_parser::SyntacticParser parser("1+1-4+4");
		auto node = parser.ParseFunction();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 2);
	}

	TEST(SyntacticParserTests, MinusPlusLongExpressionTest)
	{
		arithmetic_parser::SyntacticParser parser(".1+1-2+4-33+0.3-.4+0999");
		auto node = parser.ParseFunction();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 969);
	}

	TEST(SyntacticParserTests, _2x2_Test)
	{
		arithmetic_parser::SyntacticParser parser("2*2");
		auto node = parser.ParseFunction();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 4);
	}

	TEST(SyntacticParserTests, _1x2x3x4_Test)
	{
		arithmetic_parser::SyntacticParser parser("1*2*3*4");
		auto node = parser.ParseFunction();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 24);
	}
}