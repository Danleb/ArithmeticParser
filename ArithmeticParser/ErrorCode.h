#pragma once
#ifndef ERROR_CODE_H
#define ERROR_CODE_H

namespace ArithmeticParser
{
	enum class ErrorCode
	{
		SUCCESS = 0,
		UNDEFINED_ERROR = 1,
		LEXICAL_ERROR = 2,
		SYNTACTIC_ERROR = 3
	};
}

#endif // !ERROR_CODES_H