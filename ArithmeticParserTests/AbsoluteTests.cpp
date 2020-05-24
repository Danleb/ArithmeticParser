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
	TEST(AbsoluteTests, Abs_MinusOne_Test)
	{
		arithmetic_parser::SyntacticParser parser("|-1|");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 1);
	}

	TEST(AbsoluteTests, Two_ExplicitMult_Modulus_Test)
	{
		arithmetic_parser::SyntacticParser parser("2*|-1|");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 2);
	}

	TEST(AbsoluteTests, Two_ImplicitMult_Modulus_Test)
	{
		arithmetic_parser::SyntacticParser parser("2|-1|");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 2);
	}

	TEST(AbsoluteTests, Abs_MinusOne_Mult_Two_Test)
	{
		arithmetic_parser::SyntacticParser parser("|-1|2");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 2);
	}

	TEST(AbsoluteTests, Modulus_ExplicitMult_Modulus_Test)
	{
		arithmetic_parser::SyntacticParser parser("|-2|*|-3|");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 6);
	}

	TEST(AbsoluteTests, Modulus_ImplicitMult_Modulus_Test)
	{
		arithmetic_parser::SyntacticParser parser("|-2||-3|");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 6);
	}

	TEST(AbsoluteTests, Brackets_ExplicitMult_Modulus_Test)
	{
		arithmetic_parser::SyntacticParser parser("(1+1)*|-3|");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 6);
	}

	TEST(AbsoluteTests, Brackets_ImplicitMult_Modulus_Test)
	{
		arithmetic_parser::SyntacticParser parser("(1+1)|-3|");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 6);
	}

	TEST(AbsoluteTests, Modulus_ExplicitMult_Brackets_Test)
	{
		arithmetic_parser::SyntacticParser parser("|-3|(1+1)");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 6);
	}

	TEST(AbsoluteTests, Modulus_ImplicitMult_Brackets_Test)
	{
		arithmetic_parser::SyntacticParser parser("|-3|(1+1)");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 6);
	}

	TEST(AbsoluteTests, ModulusSum_Test)
	{
		arithmetic_parser::SyntacticParser parser("|-1|-5|-2|");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, -9);
	}

	TEST(AbsoluteTests, NestedModulus_Test)
	{
		arithmetic_parser::SyntacticParser parser("|||-6|||");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 6);
	}

	TEST(AbsoluteTests, NestedModulusSum_Test)
	{
		arithmetic_parser::SyntacticParser parser("|||-6|+|-10|||");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 16);
	}

	TEST(AbsoluteTests, ComplexModulus_Test)
	{
		arithmetic_parser::SyntacticParser parser("| |-6-|-5|| + ||3|*-10*|2|| |");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 16);
	}
}