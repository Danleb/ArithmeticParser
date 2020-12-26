#pragma once

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