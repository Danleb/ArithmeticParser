#pragma once
#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

namespace arithmetic_parser
{
	enum class TokenType
	{
		None = 0,
		Number,
		Variable,
		BuiltinFunction,
		Parentheses,
		Comma,
		Constant
	};
}

#endif // !TOKEN_TYPE_H