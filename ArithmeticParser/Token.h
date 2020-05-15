#pragma once
#ifndef TOKEN_H
#define TOKEN_H

#include<string>

#include"TokenType.h"
#include"OperatorType.h"

namespace ArithmeticParser
{
	class Token
	{
	public:
		TokenType tokenType;
		OperatorType operatorType;
		double number;
		std::string variableName;

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
			variableName(variableName)
		{

		}
	};
}

#endif // !TOKEN_H