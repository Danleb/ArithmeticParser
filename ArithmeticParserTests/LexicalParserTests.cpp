#include<string>
#include<vector>

#include"pch.h"
#include"gtest/gtest.h"

#include"LexicalParser.h"
#include"Token.h"

namespace ArithmeticalParserTests
{
	TEST(LexicalParserTests, EmptyInput)
	{
		std::string s("");
		std::vector<ArithmeticParser::Token> tokens = ArithmeticParser::GetTokens(s);

		ASSERT_EQ(tokens.size(), 0);		
	}

	TEST(LexicalParserTests, One)
	{
		std::string s("1");
		std::vector<ArithmeticParser::Token> tokens = ArithmeticParser::GetTokens(s);

		ASSERT_EQ(tokens.size(), 1);
		auto token = tokens[0];
		ASSERT_EQ(token.number, 1);
		ASSERT_EQ(token.tokenType, ArithmeticParser::TokenType::Number);
	}

	TEST(LexicalParserTests, OnePlus)
	{
		std::string strings[] = {
			std::string("1+1"),
			std::string("1 +1"),
			std::string("1+ 1"),
			std::string("  1   +    1    ")
		};

		for (const auto &input : strings) 
		{
			std::vector<ArithmeticParser::Token> tokens = ArithmeticParser::GetTokens(input);

			ASSERT_EQ(tokens.size(), 3);
			
			auto token = tokens[0];
			ASSERT_EQ(token.number, 1);
			ASSERT_EQ(token.tokenType, ArithmeticParser::TokenType::Number);
			
			token = tokens[1];
			ASSERT_EQ(token.operatorType, ArithmeticParser::OperatorType::Addition);
			ASSERT_EQ(token.tokenType, ArithmeticParser::TokenType::Operator);
			
			token = tokens[2];
			ASSERT_EQ(token.number, 1);
			ASSERT_EQ(token.tokenType, ArithmeticParser::TokenType::Number);
		}
	}
}