#include "gtest/gtest.h"

#include <string>
#include <vector>

#include "BuiltinFunctionType.h"
#include "LexicalParser.h"
#include "Token.h"

namespace ArithmeticalParserTests
{
	TEST(LexicalParserTests, EmptyInput)
	{
		auto tokens = arithmetic_parser::GetTokens("");

		ASSERT_EQ(tokens.size(), 0);
	}

	TEST(LexicalParserTests, One)
	{
		std::string s("1");
		auto tokens = arithmetic_parser::GetTokens(s);

		ASSERT_EQ(tokens.size(), 1);
		auto token = tokens[0];

		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::Number);
		ASSERT_EQ(token->number, 1);
	}

	TEST(LexicalParserTests, MinusOne)
	{
		auto tokens = arithmetic_parser::GetTokens("-1");

		ASSERT_EQ(tokens.size(), 2);

		auto token = tokens[0];
		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::BuiltinFunction);
		ASSERT_EQ(token->builtin_function_type, arithmetic_parser::BuiltinFunctionType::Subtraction);

		token = tokens[1];
		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::Number);
		ASSERT_EQ(token->number, 1);
	}

	TEST(LexicalParserTests, PlusMinusOne)
	{
		auto tokens = arithmetic_parser::GetTokens("+-1");

		ASSERT_EQ(tokens.size(), 3);

		auto token = tokens[0];
		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::BuiltinFunction);
		ASSERT_EQ(token->builtin_function_type, arithmetic_parser::BuiltinFunctionType::Addition);

		token = tokens[1];
		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::BuiltinFunction);
		ASSERT_EQ(token->builtin_function_type, arithmetic_parser::BuiltinFunctionType::Subtraction);

		token = tokens[2];
		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::Number);
		ASSERT_EQ(token->number, 1);
	}

	TEST(LexicalParserTests, OnePlusOne)
	{
		std::string strings[] = {
			std::string("1+1"),
			std::string("1 +1"),
			std::string("1+ 1"),
			std::string("  1   +    1    ")
		};

		for (const auto& input : strings)
		{
			auto tokens = arithmetic_parser::GetTokens(input);

			ASSERT_EQ(tokens.size(), 3);

			auto token = tokens[0];
			ASSERT_EQ(token->number, 1);
			ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::Number);

			token = tokens[1];
			ASSERT_EQ(token->builtin_function_type, arithmetic_parser::BuiltinFunctionType::Addition);
			ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::BuiltinFunction);

			token = tokens[2];
			ASSERT_EQ(token->number, 1);
			ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::Number);
		}
	}

	TEST(LexicalParserTests, TwoMultThreePlusFour)
	{
		auto tokens = arithmetic_parser::GetTokens("2*3 + 4");

		ASSERT_EQ(tokens.size(), 5);

		auto token = tokens[0];
		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::Number);
		ASSERT_EQ(token->number, 2);

		token = tokens[1];
		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::BuiltinFunction);
		ASSERT_EQ(token->builtin_function_type, arithmetic_parser::BuiltinFunctionType::Multiplication);		

		token = tokens[2];
		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::Number);
		ASSERT_EQ(token->number, 3);		

		token = tokens[3];
		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::BuiltinFunction);
		ASSERT_EQ(token->builtin_function_type, arithmetic_parser::BuiltinFunctionType::Addition);		

		token = tokens[4];
		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::Number);
		ASSERT_EQ(token->number, 4);		
	}

	TEST(LexicalParserTests, AllBasicOperations)
	{
		auto tokens = arithmetic_parser::GetTokens("-1.1 + 1 - 2 + 3*-4 + 1.0/4.5");

		ASSERT_EQ(tokens.size(), 15);


	}

	TEST(LexicalParserTests, RoundBrackets_Test)
	{
		auto tokens = arithmetic_parser::GetTokens("(1+1)");

		ASSERT_EQ(tokens.size(), 5);

		auto token = tokens[0];
		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::Parentheses);
		ASSERT_TRUE(token->IsOpeningRoundBracket());

		token = tokens[4];
		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::Parentheses);
		ASSERT_TRUE(token->IsClosingRoundBracket());
	}

	TEST(LexicalParserTests, Power_Test)
	{
		auto tokens = arithmetic_parser::GetTokens("2^3");

		ASSERT_EQ(tokens.size(), 3);

		auto token = tokens[1];
		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::BuiltinFunction);
		ASSERT_EQ(token->builtin_function_type, arithmetic_parser::BuiltinFunctionType::Power);

		token = tokens[2];
		ASSERT_TRUE(token->IsNumber());
		ASSERT_DOUBLE_EQ(token->number, 3);		
	}

	TEST(LexicalParserTests, Absolute_Test)
	{
		auto tokens = arithmetic_parser::GetTokens("|-1|");

		ASSERT_EQ(tokens.size(), 4);

		auto token = tokens[0];
		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::Parentheses);
		ASSERT_EQ(token->parenthesis_type, arithmetic_parser::ParenthesisType::Straight);
		ASSERT_EQ(token->parenthesis_side, arithmetic_parser::ParenthesisSide::None);

		token = tokens[2];
		ASSERT_TRUE(token->IsNumber());
		ASSERT_DOUBLE_EQ(token->number, 1);

		token = tokens[3];
		ASSERT_EQ(token->token_type, arithmetic_parser::TokenType::Parentheses);
		ASSERT_EQ(token->parenthesis_type, arithmetic_parser::ParenthesisType::Straight);
		ASSERT_EQ(token->parenthesis_side, arithmetic_parser::ParenthesisSide::None);
	}
}