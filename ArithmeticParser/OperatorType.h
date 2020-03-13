#pragma once
#ifndef OPERATOR_TYPE_H
#define OPERATOR_TYPE_H

namespace ArithmeticParser
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