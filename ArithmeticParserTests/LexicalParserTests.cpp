#include<string>
#include<vector>

#include"pch.h"
#include"gtest/gtest.h"

#include"LexicalParser.h"
#include"Token.h"

namespace ArithmeticalParserTests
{
	TEST(LexicalParserTests, One)
	{
		std::string s("1");
		std::vector<ArithmeticParser::Token> tokens = ArithmeticParser::GetTokens(s);

		ASSERT_EQ(tokens.size(), 1);
		auto token = tokens[0];
		ASSERT_EQ(token.number, 1);
		ASSERT_EQ(token.tokenType, ArithmeticParser::TokenType::Number);
	}
}