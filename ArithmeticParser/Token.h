#pragma once

#include <string>
#include <utility>

#include "ParenthesisSide.h"
#include "ParenthesisType.h"
#include "ConstantType.h"
#include "TokenType.h"
#include "BuiltinFunctionType.h"

namespace arithmetic_parser
{
	struct Token
	{
		TokenType tokenType;
		BuiltinFunctionType builtin_function_type;
		double number;
		std::string variableName;

		ParenthesisType parenthesis_type;
		ParenthesisSide parenthesis_side;

		int tokenStart;
		int tokenLength;

		Token() = default;
		Token(Token const&) = default;
		Token& operator=(Token const&) = default;

		ConstantType constant_type;

		Token(TokenType token_type) :
			tokenType(token_type)
		{

		}

		Token(ParenthesisType parenthesisType, ParenthesisSide parenthesisSide) :
			parenthesis_type(parenthesisType),
			parenthesis_side(parenthesisSide)
		{

		}

		Token(double number) :
			tokenType(TokenType::Number),
			builtin_function_type(BuiltinFunctionType::None),
			number(number),
			variableName("")
		{

		}

		Token(BuiltinFunctionType builtinFunctionType) :
			tokenType(TokenType::BuiltinFunction),
			builtin_function_type(builtinFunctionType),
			number(0),
			variableName("")
		{

		}

		Token(ConstantType constantType) :
			tokenType(TokenType::Constant),
			constant_type(constantType)
		{

		}

		Token(std::string variableName) :
			tokenType(TokenType::Variable),
			builtin_function_type(BuiltinFunctionType::None),
			number(0),
			variableName(std::move(variableName))
		{

		}

		bool IsOpenedRoundBracket();
		bool IsClosingRoundBracket();
	};
}