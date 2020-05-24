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
	TEST(SyntacticParserBracketsTests, Bracket_OnePlusOne_Bracket_Test)
	{
		arithmetic_parser::SyntacticParser parser("(1+1)");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 2);
	}

	TEST(SyntacticParserBracketsTests, SeveralNestedBrackets_Test)
	{
		arithmetic_parser::SyntacticParser parser("((((1+1))))");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 2);
	}

	TEST(SyntacticParserBracketsTests, _2_BracketsMultiplied_Test)
	{
		arithmetic_parser::SyntacticParser parser("((1+1)*(1+1))");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 4);
	}

	TEST(SyntacticParserBracketsTests, _DoubleBeforeBrackets_WithoutMultSymbol_Test)
	{
		arithmetic_parser::SyntacticParser parser("2(3+4)");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 14);
	}

	TEST(SyntacticParserBracketsTests, _DoubleAfterBrackets_WithoutMultSymbol_Test)
	{
		arithmetic_parser::SyntacticParser parser("(3+4)2");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 14);
	}

	TEST(SyntacticParserBracketsTests, _2_BracketsMultipliedWithoutMultSymbol_Test)
	{
		arithmetic_parser::SyntacticParser parser("(1+1)(1+1)");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 4);
	}

	TEST(SyntacticParserBracketsTests, _4_Brackets_Test)
	{
		arithmetic_parser::SyntacticParser parser("((1+2*4)(1+1)*(1+1))");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 36);
	}

	TEST(SyntacticParserBracketsTests, DividingBrackets_Test)
	{
		arithmetic_parser::SyntacticParser parser("((1+2*4)/1 + (1+1)/(1+1))");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 10);
	}

	TEST(SyntacticParserBracketsTests, Brackets_Minus_Brackets_Test)
	{
		arithmetic_parser::SyntacticParser parser("(2+3)-(-10+20)");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, -5);
	}
}