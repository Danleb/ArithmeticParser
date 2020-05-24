#include "pch.h"
#include "gtest/gtest.h"

#include <string>
#include <vector>

#include "SyntacticParser.h"
#include "LexicalParser.h"
#include "Token.h"

namespace ArithmeticalParserTests::SyntacticParserTests
{
	TEST(BuiltinFunctionsTests, SinusTest)
	{
		auto node = arithmetic_parser::SyntacticParser("sin(PI)").ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 0);
	}

	TEST(LexicalParserTests, CosineTest)
	{
		auto node = arithmetic_parser::SyntacticParser("cos(PI/2)").ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, 0);
	}
}