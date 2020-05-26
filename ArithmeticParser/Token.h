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
		TokenType token_type;
		BuiltinFunctionType builtin_function_type;
		double number;
		std::string variable_name;

		ParenthesisType parenthesis_type;
		ParenthesisSide parenthesis_side;

		int tokenStart = -1;
		int tokenLength = -1;

		Token() = default;
		Token(const Token&) = default;
		Token& operator=(const Token&) = default;

		ConstantType constant_type;

		Token(TokenType token_type);
		Token(ParenthesisType parenthesisType, ParenthesisSide parenthesisSide);
		Token(double number);
		Token(BuiltinFunctionType builtinFunctionType);
		Token(ConstantType constantType);
		Token(std::string variableName);

		bool IsComma();

		bool IsValueSymbol();
		bool IsNumber();
		bool IsConstant();
		bool IsVariable();

		bool IsOpeningBracket();
		bool IsClosingBracket();

		bool IsOpeningStraightBracket();
		bool IsClosingStraightBracket();

		bool IsOpeningRoundBracket();
		bool IsClosingRoundBracket();
	};
}