#include "pch.h"
#include "gtest/gtest.h"

#include <string>
#include <vector>

#include "BuiltinFunctionType.h"
#include "LexicalParser.h"
#include "Token.h"

namespace ArithmeticalParserTests
{
	TEST(LexicalParserTests, SinusTest)
	{
		auto tokens = arithmetic_parser::GetTokens("sin(PI)");
		ASSERT_EQ(tokens.size(), 4);
	}

	TEST(LexicalParserTests, CosineTest)
	{
		auto tokens = arithmetic_parser::GetTokens("cos(PI/2)");
		ASSERT_EQ(tokens.size(), 6);
	}
}