#include "pch.h"

#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "LexicalParser.h"
#include "Token.h"

namespace ArithmeticalParserTests
{
	TEST(LexicalParserTests, EmptyInput)
	{
		std::string s("");
		std::vector<arithmetic_parser::Token> tokens = arithmetic_parser::GetTokens(s);

		ASSERT_EQ(tokens.size(), 0);		
	}

	TEST(LexicalParserTests, One)
	{
		std::string s("1");
		std::vector<arithmetic_parser::Token> tokens = arithmetic_parser::GetTokens(s);

		ASSERT_EQ(tokens.size(), 1);
		auto token = tokens[0];
		ASSERT_EQ(token.number, 1);
		ASSERT_EQ(token.tokenType, arithmetic_parser::TokenType::Number);
	}

	TEST(LexicalParserTests, MinusOne)
	{
		std::string s("-1");
		std::vector<arithmetic_parser::Token> tokens = arithmetic_parser::GetTokens(s);

		ASSERT_EQ(tokens.size(), 1);
		auto token = tokens[0];
		ASSERT_EQ(token.number, 1);
		ASSERT_EQ(token.tokenType, arithmetic_parser::TokenType::Number);
	}

	TEST(LexicalParserTests, OnePlusOne)
	{
		std::string strings[] = {
			std::string("1+1"),
			std::string("1 +1"),
			std::string("1+ 1"),
			std::string("  1   +    1    ")
		};

		for (const auto &input : strings) 
		{
			std::vector<arithmetic_parser::Token> tokens = arithmetic_parser::GetTokens(input);

			ASSERT_EQ(tokens.size(), 3);
			
			auto token = tokens[0];
			ASSERT_EQ(token.number, 1);
			ASSERT_EQ(token.tokenType, arithmetic_parser::TokenType::Number);
			
			token = tokens[1];
			ASSERT_EQ(token.operatorType, arithmetic_parser::OperatorType::Addition);
			ASSERT_EQ(token.tokenType, arithmetic_parser::TokenType::Operator);
			
			token = tokens[2];
			ASSERT_EQ(token.number, 1);
			ASSERT_EQ(token.tokenType, arithmetic_parser::TokenType::Number);
		}
	}

	TEST(LexicalParserTests, TwoMultThreePlusFour)
	{
		const std::string input("2*3 + 4");

		auto tokens = arithmetic_parser::GetTokens(input);

		ASSERT_EQ(tokens.size(), 5);

		auto token = tokens[0];
		ASSERT_EQ(token.number, 2);
		ASSERT_EQ(token.tokenType, arithmetic_parser::TokenType::Number);

		token = tokens[1];
		ASSERT_EQ(token.operatorType, arithmetic_parser::OperatorType::Multiplication);
		ASSERT_EQ(token.tokenType, arithmetic_parser::TokenType::Operator);

		token = tokens[2];
		ASSERT_EQ(token.number, 3);
		ASSERT_EQ(token.tokenType, arithmetic_parser::TokenType::Number);

		token = tokens[3];
		ASSERT_EQ(token.operatorType, arithmetic_parser::OperatorType::Addition);
		ASSERT_EQ(token.tokenType, arithmetic_parser::TokenType::Operator);

		token = tokens[4];
		ASSERT_EQ(token.number, 4);
		ASSERT_EQ(token.tokenType, arithmetic_parser::TokenType::Number);
	}
}