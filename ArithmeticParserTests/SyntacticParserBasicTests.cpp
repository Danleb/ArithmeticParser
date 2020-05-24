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
	TEST(SyntacticParserTests, ZeroTest)
	{
		arithmetic_parser::SyntacticParser parser("0");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 0);
	}

	TEST(SyntacticParserTests, OnePlusOneTest)
	{
		arithmetic_parser::SyntacticParser parser("1+1");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 2);
	}

	TEST(SyntacticParserTests, _1234_Plus_4567_Test)
	{
		arithmetic_parser::SyntacticParser parser("1234+4567");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, (1234 + 4567));
	}

	TEST(SyntacticParserTests, _1234_Minus_4567_Test)
	{
		arithmetic_parser::SyntacticParser parser("1234-4567");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, (1234 - 4567));
	}

	TEST(SyntacticParserTests, FractionalSumTest)
	{
		arithmetic_parser::SyntacticParser parser(".1+0.1");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 0.2);
	}

	TEST(SyntacticParserTests, SignOperatorTest)
	{
		arithmetic_parser::SyntacticParser parser("+-+-.1+-+-.1");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 0.2);
	}

	TEST(SyntacticParserTests, ZerosFirstTest)
	{
		arithmetic_parser::SyntacticParser parser("0999+000001");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 1000);
	}

	TEST(SyntacticParserTests, AlternatingPlusMinusTest)
	{
		arithmetic_parser::SyntacticParser parser("1-2+3");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 2);
	}

	TEST(SyntacticParserTests, AlternatingPlusMinusTest2)
	{
		arithmetic_parser::SyntacticParser parser("1+1-4+4");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 2);
	}

	TEST(SyntacticParserTests, MinusPlusLongExpressionTest)
	{
		arithmetic_parser::SyntacticParser parser(".1+1-2+4-33+0.3-.4+0999");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 969);
	}

	TEST(SyntacticParserTests, _2x3_Test)
	{
		arithmetic_parser::SyntacticParser parser("2*3");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 6);
	}

	TEST(SyntacticParserTests, _1x2x3x4_Test)
	{
		arithmetic_parser::SyntacticParser parser("1*2*3*4");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 24);
	}

	TEST(SyntacticParserTests, _2_Divide_10_Test)
	{
		arithmetic_parser::SyntacticParser parser("2/10");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, (2. / 10.));
	}

	TEST(SyntacticParserTests, PlusMinusAndMult_Test)
	{
		arithmetic_parser::SyntacticParser parser("1+10*10-8*2*2");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, (1 + 10 * 10 - 8 * 2 * 2));
	}

	TEST(SyntacticParserTests, PlusMinusAndDiv_Test)
	{
		arithmetic_parser::SyntacticParser parser("1+10*10+4/5-8*2*2");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, (1 + 10 * 10 + 4. / 5. - 8 * 2 * 2));
	}

	TEST(SyntacticParserTests, TwoPowerThree_Test)
	{
		arithmetic_parser::SyntacticParser parser("2^3");
		auto value = parser.ParseExpression()->Calculate();
		ASSERT_DOUBLE_EQ(value, pow(2, 3));
	}
}