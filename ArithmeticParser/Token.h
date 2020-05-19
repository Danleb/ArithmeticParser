#pragma once
#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <utility>

#include "ParenthesisSide.h"
#include "ParenthesisType.h"
#include "ConstantType.h"
#include "TokenType.h"
#include "BuiltinFunctionType.h"

namespace arithmetic_parser
{
	class Token
	{
	public:
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
			tokenType(TokenType::Constant)
		{

		}

		Token(std::string variableName) :
			tokenType(TokenType::Variable),
			builtin_function_type(BuiltinFunctionType::None),
			number(0),
			variableName(std::move(variableName))
		{

		}
	};
}

#endif // !TOKEN_H