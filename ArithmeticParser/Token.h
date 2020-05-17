#pragma once
#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <utility>

#include "TokenType.h"
#include "OperatorType.h"
#include "BuiltinFunction.h"

namespace arithmetic_parser
{
	class Token
	{
	public:
		TokenType tokenType;
		OperatorType operatorType;
		BuiltinFunction builtin_function;
		double number;
		std::string variableName;

		int tokenStart;
		int tokenLength;

		Token() = default;
		Token(Token const&) = default;
		Token& operator=(Token const&) = default;

		Token(OperatorType operatorType) :
			tokenType(TokenType::Operator),
			operatorType(operatorType),
			number(0),
			variableName("")
		{

		}

		Token(double number) :
			tokenType(TokenType::Number),
			operatorType(OperatorType::None),
			number(number),
			variableName("")
		{

		}

		Token(std::string variableName) :
			tokenType(TokenType::Variable),
			operatorType(OperatorType::None),
			number(0),
			variableName(std::move(variableName))
		{

		}
	};
}

#endif // !TOKEN_H