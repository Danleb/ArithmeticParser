#pragma once

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