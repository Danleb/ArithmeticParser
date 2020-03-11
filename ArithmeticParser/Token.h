#ifndef TOKEN_H
#define TOKEN_H

#include"TokenType.h"
#include"OperatorType.h"

namespace ArithmeticParser
{
	class Token
	{
	public:
		TokenType tokenType;
		OperatorType operatorType;
		double Number;

		Token(TokenType tokenType, OperatorType operatorType) :
			tokenType(tokenType),
			operatorType(operatorType)
		{

		}

	};
}

#endif // !TOKEN_H