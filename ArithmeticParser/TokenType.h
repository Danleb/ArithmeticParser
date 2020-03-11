#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

enum TokenType
{
	None = 0,
	Number = 1,
	Operator = 2,
	Variable = 3,
	BuiltinFunction = 4
};

#endif // !TOKEN_TYPE_H