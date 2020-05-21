#pragma once

namespace arithmetic_parser
{
	enum class ErrorCode : int
	{
		SUCCESS = 0,
		UNDEFINED_ERROR = 1,
		LEXICAL_ERROR = 2,
		SYNTACTIC_ERROR = 3,
		SINGLE_CLOSING_PARENTHESIS = 4,
		SINGLE_OPENING_PARENTHESIS = 5,
		SINGLE_TOKEN_UNPARSED = 6,
	};
}