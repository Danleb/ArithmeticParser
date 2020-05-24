#include "pch.h"
#include "gtest/gtest.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <vector>
#include <corecrt_math_defines.h>

#include "ArgumentsParsing.h"
#include "CmdOption.h"
#include "Node.h"
#include "SyntacticParser.h"

namespace ArithmeticalParserTests::SyntacticParser
{
	TEST(SyntacticConstantTests, PI_Test)
	{
		arithmetic_parser::SyntacticParser parser("PI");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, M_PI);
	}

	TEST(SyntacticConstantTests, Exponent_Test)
	{
		arithmetic_parser::SyntacticParser parser("e");
		auto node = parser.ParseExpression();
		auto value = node->Calculate();
		ASSERT_DOUBLE_EQ(value, M_E);
	}
}