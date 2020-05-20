#pragma once
#ifndef BUILTIN_FUNCTION_TYPE_H
#define BUILTIN_FUNCTION_TYPE_H

namespace arithmetic_parser
{
	enum class BuiltinFunctionType
	{
		None = 0,
		Addition,
		Subtraction,
		Multiplication,
		Division,

		SignPlus,
		SignMinus,

		Power,
		Absolute,		

		Sinus,
		Cosine,
		Tangent,
		Cotangent,
		Arcsine,
		Arccosine,
		Arctangent,
		Arccotangent,

		NaturalLogarithm,
		DecimalLogarithm,
		LogarithmArbitraryBasis
	};
}

#endif // !BUILTIN_FUNCTION_TYPE_H