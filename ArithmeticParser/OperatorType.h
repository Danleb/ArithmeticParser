#pragma once
#ifndef OPERATOR_TYPE_H
#define OPERATOR_TYPE_H

namespace arithmetic_parser
{
	enum class OperatorType
	{
		None = 0,
		Addition,
		Subtraction,
		Multiplication,
		Division
	};
}

#endif // !OPERATOR_TYPE_H