#include "gtest/gtest.h"

#include <string>
#include <vector>

#include "ConstantType.h"
#include "LexicalParser.h"

namespace LexicalParserTests
{
	TEST(ConstantsTests, PI_Test)
	{
		auto tokens = arithmetic_parser::GetTokens("PI");

		ASSERT_EQ(tokens.size(), 1);
		auto token = tokens[0];

		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::Constant);
		ASSERT_EQ(token->constant_type, arithmetic_parser::ConstantType::PI);
	}

	TEST(ConstantsTests, Exponent_Test)
	{
		auto tokens = arithmetic_parser::GetTokens("e");

		ASSERT_EQ(tokens.size(), 1);
		auto token = tokens[0];

		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::Constant);
		ASSERT_EQ(token->constant_type, arithmetic_parser::ConstantType::Exponent);
	}
}