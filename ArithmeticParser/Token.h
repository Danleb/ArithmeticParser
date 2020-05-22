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

		int tokenStart = -1;
		int tokenLength = -1;

		Token() = default;
		Token(Token const&) = default;
		Token& operator=(Token const&) = default;

		ConstantType constant_type;

		Token(TokenType token_type);
		Token(ParenthesisType parenthesisType, ParenthesisSide parenthesisSide);
		Token(double number);
		Token(BuiltinFunctionType builtinFunctionType);
		Token(ConstantType constantType);
		Token(std::string variableName);

		bool IsValueSymbol();
		bool IsNumber();
		bool IsConstant();
		bool IsVariable();

		bool IsOpenedRoundBracket();
		bool IsClosingRoundBracket();
	};
}