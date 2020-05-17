#pragma once
#ifndef PARENTHESIS_TYPE_H
#define PARENTHESIS_TYPE_H

namespace arithmetic_parser
{
	enum class ParenthesisType
	{
		None = 0,
		Round = 1,
		Square = 2,
		Curly = 3
	};
}

#endif // !PARENTHESIS_TYPE_H